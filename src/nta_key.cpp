#include "nta_key.hpp"

int nta_expand(string input_string, string &output_string, vector<int> keylist)
{
    if (!input_string.empty())
    {

        output_string = input_string;
        int got_layer = -1;
        string temp_output_string = output_string;

        nta_report(3, "Expanding: " + temp_output_string);

        while (temp_output_string.rfind("NTA#") != string::npos)
        {
            int pos = temp_output_string.rfind("NTA#");
            temp_output_string.erase(pos, 4);
            try
            {
                unsigned int got_key = stoi(temp_output_string.substr(pos, string::npos));
                string to_delete = to_string(got_key);
                temp_output_string.erase(pos, to_delete.length());
                if (got_key < keylist.size())
                    temp_output_string.insert(pos, to_string(keylist[got_key]));
            }
            catch (const int invalid_argument)
            {
                nta_report(3, "Invalid integer in NTA#, passing nothing");
            }
        }

        nta_report(3, "After NTA# pass: " + temp_output_string);

        if (temp_output_string.rfind("NTA~") != string::npos)
        {
            int pos = temp_output_string.rfind("NTA~");
            temp_output_string.erase(pos, 4);
            try
            {
                got_layer = stoi(temp_output_string.substr(pos, string::npos));
                string to_delete = to_string(got_layer);
                temp_output_string.erase(pos, to_delete.length());
                nta_report(3, "Layer to switch to: " + to_string(got_layer));
            }
            catch (const int invalid_argument)
            {
                nta_report(1, "Layer switching failed: no layer number provided");
                got_layer = -1;
            }
        }

        nta_report(3, "After NTA~ pass: " + temp_output_string);
        output_string = temp_output_string;

        return got_layer;
    }
    return -1;
};

ntakey::ntakey(int new_id, string new_action)
{
    own_id = new_id;
    own_action = new_action;
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

ntakey &ntakey::add_child(int child_id, const string &child_action)
{
    if (has_child(child_id))
    {
        return get_child(child_id);
    } // If child with specified id already exists, return it and abort.
      // Else:

    ntakey newkey(child_id, child_action);
    // Create temporary key, write child_id to it's id, child_action to it's action.

    children_vector.push_back(newkey);
    return children_vector.back();
    // Add key to child_key vector, return it.
}

void ntakey::add_child_recursively(vector<int> numbers_arr, vector<string> actions_arr)
{

    ntakey &child_added = add_child(numbers_arr[0], actions_arr[0]);

    numbers_arr.erase(numbers_arr.begin());
    actions_arr.erase(actions_arr.begin());

    if (!numbers_arr.empty())
        child_added.add_child_recursively(numbers_arr, actions_arr);
}

void ntakey::list_recursively(int depth)
{
    string temp;
    if (depth == 2)
    {
        printf("%d: %s\n", own_id, own_action.c_str());
    }
    else if (depth > 1)
    {
        printf("%s", temp.insert(0, (depth - 2) * 2, ' ').c_str());
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
    nta_report(4, "Executing this: " + expanded_action);
    if (!expanded_action.empty())
        nta_report(5, "----- Command output begin -----");
    if (!no_execute)
        system(expanded_action.c_str());
    else
    {
        printf("%s\n", expanded_action.c_str());
    }
    if (!expanded_action.empty())
        nta_report(5, "-----  Command output end  -----\n");
    if (new_layer != -1)
    {
        nta_report(2, "Switching to layer " + to_string(new_layer));
        layer = new_layer;
        nta_report(0, "New layer equal to current layer.");
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
            nta_report(4, "Found child " + to_string(modifiable_keylist[0]) + " in parent " + to_string(own_id) + " - executing it");
            modifiable_keylist.erase(modifiable_keylist.begin());
            found_child.execute_recursively(modifiable_keylist, original_keylist, layer, depth + 1);
        }
        else
        {
            nta_report(4, "Child " + to_string(modifiable_keylist[0]) + " in parent " + to_string(own_id) + " not found");
            if (depth == 0)
                nta_report(1, "Your map file is likely broken - looks like it does not contain a layer 0.");
        }
    }
};