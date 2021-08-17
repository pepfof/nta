#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "nta_key.h"
#include "nta_basics.h"
#include "nta_parser.h"
using namespace std;

int current_level = 0;

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
				ex.insert(ex.begin(), current_level);
				userinput.clear();
				int temp_level = current_level;
				if (!ex.empty()) masterkey.execute_recursively(ex, ex, temp_level);
				if (masterkey.has_child(temp_level)) current_level = temp_level;
				else if (temp_level != current_level)
					nta_report(0, "Layer " + to_string(temp_level) + " is not defined, reverting to level " + to_string(current_level));
			}
		}
		catch (const invalid_argument) {
			if (userinput == "list") {
				masterkey.list_recursively(0, 0);
				printf("\n");
			}
			else if (userinput == "quit") {
				nta_report(2, "Quit by user");
				exit(0);
			}
		}
	}
}