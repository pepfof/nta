#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "nta_key.h"
#include "nta_basics.h"
#include "nta_parser.h"
using namespace std;

int current_layer = 0;

int SplitString(string s, vector<int>& v) {

	v.clear();
	string temp = "";
	for (int i = 0; i < s.length(); ++i) {

		if (s[i] == ' ') {
			try {
				v.push_back(stoi(temp));
			}
			catch (const invalid_argument) {
				nta_report(1, "Input formatted incorrectly, aborting execution");
				v.clear();
				return 1;
			}
			temp = "";
		}
		else {
			temp.push_back(s[i]);
		}

	}
	try {
		v.push_back(stoi(temp));
	}
	catch (const invalid_argument) {
		nta_report(1, "Input formatted incorrectly, aborting execution");
		v.clear();
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	nta_report_determine_levels(argc, argv);

	vector<int> ex;
	vector<int> alpha_int = {};
	vector<string> alpha_str = {};
	ntakey masterkey(0, "");
	int last_spaces = 0;
	bool ignore = false;
	string userinput = "";

	nta_read_config_to_key(nta_keymap_file,masterkey);

	while (1) {
		printf("NTA @> ");
		getline(cin, userinput);
		try {
			stoi(userinput);
			if (!SplitString(userinput, ex)) {
				ex.insert(ex.begin(), current_layer);
				userinput.clear();
				int temp_layer = current_layer;
				if (!ex.empty()) masterkey.execute_recursively(ex, ex, temp_layer, 0);
				if (masterkey.has_child(temp_layer)) current_layer = temp_layer;
				else if (temp_layer != current_layer)
					nta_report(1, "Layer switching failed: layer " + to_string(temp_layer) + " does not exist.");
			}
		}
		catch (const invalid_argument) {
			if (userinput == "list") {
				masterkey.list_recursively(0, 0);
				printf("\n");
			}
			else if (userinput == "quit" || userinput == "exit" || userinput == "abort") {
				nta_report(2, "Quit by command");
				exit(0);
			}
		}
	}
}
