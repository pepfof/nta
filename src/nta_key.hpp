#ifndef NTAKEY_H_ /* Include guard */
#define NTAKEY_H_

#include <string>
#include <vector>
#include <stdio.h>
#include "nta_basics.hpp"

using namespace std;

int nta_expand(string input_string, string &output_string, vector<int> keylist);

class ntakey
{
public:
    int own_id;
    signed char own_function;
    string own_action;
    vector<ntakey> children_vector;
    bool no_execute;
    int report_level;

    ntakey(int new_id = 0,string new_action = "", int new_function = 0);

    void set_report_levels(int new_report_levels, bool recursive);

    void set_no_execute(bool new_no_execute, bool recursive);

    int has_child(int child_id);

    ntakey &get_child(int child_id);

    ntakey &add_child(int child_id, const string child_action, signed char child_function);

    void add_child_recursively(vector<int> id_vec, vector<string> action_vec, vector<signed char> function_vec);

    void list_recursively(int depth);

    void execute(vector<int> keylist, int &layer);

    void execute_recursively(vector<int> modifiable_keylist, vector<int> original_keylist, int &layer, int depth);
};

#endif