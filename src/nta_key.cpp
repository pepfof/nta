#include "nta_key.hpp"

int extract_tag(string &_s, string tag, vector<pair<size_t, unsigned int>> &output)
{
    size_t tagpos;
    unsigned int tagval;
    while ((tagpos = _s.find(tag)) != string::npos)
    {
        _s.erase(tagpos, tag.length());
        int nfound = sscanf(_s.substr(tagpos).c_str(), "%d ", &tagval);
        if (nfound != 1)
        {
            return 1;
        }
        _s.erase(tagpos, to_string(tagval).length());
        output.push_back(make_pair(tagpos, tagval));
        nta_report(NTAREP_EXPAND, _s + ", " + tag + " at " + to_string(tagpos) + ": " + to_string(tagval));
    }
    return 0;
}

int nta_expand(string input_string, string &output_string, vector<int> keylist)
{
    if (!input_string.empty())
    {

        output_string = input_string;
        int got_layer = -1;
        string temp_output_string = output_string;

        nta_report(NTAREP_EXPAND, "Expanding: " + temp_output_string);

        vector<pair<size_t, unsigned int>> key_tags;

        if (extract_tag(temp_output_string, "NTA#", key_tags))
        {
            nta_report(NTAREP_EXPAND, "Invalid integer in NTA#, passing nothing");
        }
        else
        {
            size_t pos_offset = 0;
            size_t i = 0;
            while (i < key_tags.size())
            {
                if (key_tags[i].second < keylist.size())
                {
                    temp_output_string.insert(key_tags[i].first + pos_offset, to_string(keylist[key_tags[i].second]));
                    pos_offset += to_string(keylist[key_tags[i].second]).length();
                }
                i++;
            }
        }

        nta_report(NTAREP_EXPAND, "After NTA# pass: " + temp_output_string);

        if (!extract_tag(temp_output_string, "NTA~", key_tags))
        {
            nta_report(NTAREP_EXPAND, "Invalid integer in NTA~, not switching layer");
        }
        else
        {
            got_layer = key_tags.back().second;
        }

        nta_report(NTAREP_EXPAND, "After NTA~ pass: " + temp_output_string);
        output_string = temp_output_string;

        return got_layer;
    }
    return -1;
};

ntakey::ntakey(int new_id, string new_action, int new_function)
{
    own_id = new_id;
    own_action = new_action;
    own_function = new_function;
    no_execute = 0;
}

void ntakey::set_report_levels(int new_report_levels, bool recursive)
{
    report_level = new_report_levels;
    {
        unsigned int i = 0;
        while (i < children_vector.size())
        {
            children_vector[i].set_report_levels(new_report_levels, recursive);
            i++;
        }
    }
}

void ntakey::set_no_execute(bool new_no_execute, bool recursive)
{
    no_execute = new_no_execute;
    if (recursive)
    {
        unsigned int i = 0;
        while (i < children_vector.size())
        {
            children_vector[i].set_no_execute(new_no_execute, recursive);
            i++;
        }
    }
}

int ntakey::has_child(int child_id)
{
    unsigned int i = 0;
    while (i < children_vector.size())
    {
        if (child_id == children_vector.at(i).own_id)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

ntakey &ntakey::get_child(int child_id)
{
    unsigned int i = 0;
    while (i < children_vector.size())
    {
        if (child_id == children_vector.at(i).own_id)
        {
            return children_vector.at(i);
        }
        i++;
    }
    return *this;
}

ntakey &ntakey::add_child(int child_id, const string child_action, signed char child_function)
{
    if (has_child(child_id))
    {
        return get_child(child_id);
    } // If child with specified id already exists, return it and abort.
      // Else:

    ntakey newkey(child_id, child_action, child_function);
    // Create temporary key, write child_id to it's id, child_action to it's action.

    children_vector.push_back(newkey);
    return children_vector.back();
    // Add key to child_key vector, return it.
}

void ntakey::add_child_recursively(vector<int> id_vec, vector<string> action_vec, vector<signed char> function_vec)
{

    ntakey &child_added = add_child(id_vec[0], action_vec[0], function_vec[0]);

    id_vec.erase(id_vec.begin());
    action_vec.erase(action_vec.begin());
    function_vec.erase(function_vec.begin());

    if (!id_vec.empty())
        child_added.add_child_recursively(id_vec, action_vec, function_vec);
}

void ntakey::list_recursively(int depth)
{
    string temp;
    if (depth > 1)
    {
        printf("%s", temp.insert(0, (depth - 2) * 2, ' ').c_str());
        printf("%c", own_function == -1 ? '.' : own_function + 'A');
        printf("%d: %s\n", own_id, own_action.c_str());
    }
    else if (depth == 1)
    {
        printf("\nLAYER %d: %s\n", own_id, own_action.c_str());
    }

    unsigned int i = 0;
    while (i < children_vector.size())
    {
        children_vector[i].list_recursively(depth + 1);
        i++;
    }
}

void ntakey::execute(vector<int> keylist, int &layer)
{
    string expanded_action;
    int new_layer = nta_expand(own_action, expanded_action, keylist);
    nta_report(NTAREP_INFO, "Executing this: " + expanded_action);
    if (!no_execute)
        system(expanded_action.c_str());
    else
    {
        printf("%s\n", expanded_action.c_str());
    }
    if (new_layer != -1)
    {
        nta_report(NTAREP_INFO, "Switching to layer " + to_string(new_layer));
        layer = new_layer;
        nta_report(NTAREP_WARN, "New layer equal to current layer.");
    }
}

void ntakey::execute_recursively(vector<int> modifiable_keylist, vector<int> original_keylist, int &layer, int depth)
{
    execute(original_keylist, layer);
    if (!modifiable_keylist.empty())
    {
        if (has_child(modifiable_keylist[0]))
        {
            ntakey found_child = get_child(modifiable_keylist[0]);
            nta_report(NTAREP_DEBUG, "Found child " + to_string(modifiable_keylist[0]) + " in parent " + to_string(own_id) + " - executing it");
            modifiable_keylist.erase(modifiable_keylist.begin());
            found_child.execute_recursively(modifiable_keylist, original_keylist, layer, depth + 1);
        }
        else
        {
            nta_report(NTAREP_DEBUG, "Child " + to_string(modifiable_keylist[0]) + " in parent " + to_string(own_id) + " not found");
            if (depth == 0)
                nta_report(NTAREP_ERROR, "Your map file is likely broken - looks like it does not contain a layer 0.");
        }
    }
};