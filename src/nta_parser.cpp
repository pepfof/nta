#include "nta_parser.hpp"

size_t find_space(const string s, int position = 0)
{
	for (unsigned int i = position; i < s.size(); ++i)
	{
		if (s[i] != ' ')
		{
			return i;
		}
	}
	return string::npos;
}

int count_spaces(const string s)
{
	int counter = 0;
	for (unsigned int i = 0; i < s.size(); ++i)
	{
		if (s[i] == ' ')
		{
			counter += 1;
		}
		else
		{
			if (counter % 4 != 0)
			{
				nta_report(NTAREP_ERROR, "Incorrect use of spaces in config file!\nIndentations are 4 spaces per level\nAborting.");
				abort();
			}
			return counter;
		}
	}
	return 0;
}

void nta_read_config_to_key(const string file, ntakey &key)
{
	ifstream f_in(file);

	vector<int> tree_values = {};
	vector<string> tree_actions = {};
	vector<signed char> tree_functions = {};
	bool ignore = 0;
	int last_spaces = 0;
	unsigned int cur_line = 0;
	string line = "";

	while (getline(f_in, line))
	{
		cur_line++;
		int spaces = count_spaces(line);
		int got_id = 0;
		string got_act = "";
		signed char got_func = -1;

		// Space counting and levelling bullshit
		if (ignore)
		{
			if (spaces > last_spaces)
			{
				continue;
			}
			else
			{
				ignore = false;
			}
		}

		for (int i = 0; i <= (last_spaces - spaces); i += 4)
		{
			if (!(tree_values.empty() or tree_actions.empty() or tree_functions.empty()))
			{
				tree_values.pop_back();
				tree_actions.pop_back();
				tree_functions.pop_back();
			}
		}

		// get id from line
		size_t id_end_pos = 0;

		try
		{
			got_id = stoi(line, &id_end_pos);
			// nta_report(6, "Key id: " + to_string(got_id));
		}
		catch (invalid_argument const &)
		{
			nta_report(NTAREP_PARSE, "Key values formatted incorrectly, skipping this line: " + to_string(cur_line) + "\nAnd any of its children.");
			ignore = true;
			continue;
		}

		// id_end_pos += find_space(line, 0);
		// nta_report(6, "Function: " + to_string(line[id_end_pos]) + " (" + to_string(id_end_pos)+")");
		//  get func from line
		if (id_end_pos >= line.length() or isspace(line[id_end_pos]))
		{
			got_func = -1;
		}
		else if (isalpha(line[id_end_pos]))
		{
			got_func = line[id_end_pos] - (line[id_end_pos] >= 'A' ? 'A' : 'a');
			id_end_pos++;
		}
		else
		{
			nta_report(NTAREP_PARSE, "Unknown function: " + to_string(line[id_end_pos]) + " (" + to_string(id_end_pos) + "). Skipping this line: " + line + "\nAnd any of its children.");
			ignore = true;
			continue;
		}

		// nta_report(6, "Key func: " + to_string(got_func));

		// get act from line
		if (id_end_pos < line.length())
		{
			got_act = line.substr(id_end_pos + 1);
		}

		// push it baby
		last_spaces = spaces;
		tree_values.push_back(got_id);
		tree_actions.push_back(got_act);
		tree_functions.push_back(got_func);

		//nta_report(NTAREP_PARSE, string(tree_values.begin(), tree_values.end()));

		key.add_child_recursively(tree_values, tree_actions, tree_functions);
	}
}