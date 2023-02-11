#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "nta_key.hpp"
#include "nta_basics.hpp"
#include "nta_parser.hpp"
using namespace std;

#define DEFAULT_MAP_FILENAME "./test/ntakey.cfg"

int current_layer = 0;

int SplitString(string s, vector<int> &v)
{
	v.clear();
	string temp = "";
	for (unsigned int i = 0; i < s.length(); ++i)
	{

		if (s[i] == ' ')
		{
			try
			{
				v.push_back(stoi(temp));
			}
			catch (invalid_argument const &)
			{
				nta_report(1, "Input formatted incorrectly, aborting execution");
				v.clear();
				return 1;
			}
			temp = "";
		}
		else
		{
			temp.push_back(s[i]);
		}
	}
	try
	{
		v.push_back(stoi(temp));
	}
	catch (invalid_argument const &)
	{
		nta_report(1, "Input formatted incorrectly, aborting execution");
		v.clear();
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{

	nta_keyserver_start();

	string nta_keymap_file = DEFAULT_MAP_FILENAME;

	nta_report_determine_levels(argc, argv, nta_keymap_file);

	vector<int> ex;
	vector<int> alpha_int = {};
	vector<string> alpha_str = {};
	ntakey masterkey(0);
	string userinput = "";

	nta_read_config_to_key(nta_keymap_file, masterkey);

	while (getline(cin, userinput))
	{
		printf("NTA @> ");
		try
		{
			stoi(userinput);
			if (!SplitString(userinput, ex))
			{
				ex.insert(ex.begin(), current_layer);
				userinput.clear();
				int temp_layer = current_layer;

				if (!ex.empty())
					masterkey.perform_recursively(ex, ex, temp_layer, 0);

				if (masterkey.has_child(temp_layer))
					current_layer = temp_layer;
				else
					nta_report(NTAREP_ERROR, "Layer switching failed: layer " + to_string(temp_layer) + " does not exist.");
			}
		}
		catch (invalid_argument const &)
		{
			if (userinput == "list")
			{
				masterkey.list_recursively();
				printf("\n");
			}
			else if (userinput == "quit" || userinput == "exit" || userinput == "abort")
			{
				nta_report(NTAREP_INFO, "Quit by command");
				break;
			}
		}
	}
	nta_keyserver_end();
}
