#ifndef NTAPARSE_H_   /* Include guard */
#define NTAPARSE_H_

#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "nta_basics.h"

using namespace std;

int find_space(const string& s, int position = 0)
{
	for (int i = position; i < s.size(); ++i)
	{
		if (s[i] != ' ')
		{
			return i;
		}
	}
	return string::npos;
}

int count_spaces(const string& s)
{
	int counter = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == ' ')
		{
			counter += 1;
		}
		else
		{
			if (counter % 4 != 0)
			{
				nta_report(6, "Inconsistent use of spaces in config file!\nIndentations must be done using 4 spaces per level\nAborting.");
				abort();
			}
			return counter;
		}
	}
	return 0;
}



void nta_read_config_to_key(const string file, ntakey& key)
{
	ifstream fin(file);
	
	vector<int> a = {};
	vector<string> b = {};
	bool ignore = 0;
	int last_spaces = 0;

	while (fin)
	{
		string line = "";
		getline(fin, line);
		int extra_space = find_space(line);
		int spaces = count_spaces(line);
		int number = 0;
		string str = "";

		if (ignore)
		{
			if (spaces > last_spaces)
			{
				continue;
			}
		}

		for (int i = 0; i <= (last_spaces - spaces); i += 4)
		{
			if (!(a.empty() or b.empty()))
			{
				a.pop_back();
				b.pop_back();
			}
		}

		auto first_space = line.find(' ', extra_space);
		auto omega_space = find_space(line, extra_space + 1);
		if (first_space != string::npos)
		{
			try
			{
				number = stoi(line.substr(0, first_space));
			}
			catch (const invalid_argument) {
				nta_report(6, "Key values formatted incorrectly, skipping this line: " + line);
				ignore = true;
			}
		}
		else
		{
			try {
				number = stoi(line);
			}
			catch (const invalid_argument) {
				nta_report(6, "Key values formatted incorrectly, skipping this line: " + line);
				ignore = true;
			}
		}
		if (omega_space != string::npos)
		{
			str = line.substr(omega_space);
		}
		else
		{
			str = "";
		}
		last_spaces = spaces;
		a.push_back(number);
		b.push_back(str);

		key.add_child_recursively(a,b);
	}
}

#endif