#ifndef NTAKEY_HPP_ /* Include guard */
#define NTAKEY_HPP_

#include <string>
#include <vector>
#include <stdio.h>
#include "nta_basics.hpp"
#include "nta_execute.hpp"
#include "nta_expand.hpp"

using namespace std;

class ntakey
{
public:
    int own_id;
    signed char own_function;
    string own_action;
    unsigned int own_depth;
    vector<ntakey> children_vector;
    bool no_execute;
    int report_level;

    ntakey(int new_id = 0,string new_action = "", signed char new_function = -1, unsigned int own_depth = 0);

    void set_report_levels(int new_report_levels, bool recursive);

    void set_no_execute(bool new_no_execute, bool recursive);

    int has_child(int child_id);

    ntakey &get_child(int child_id);

    ntakey &add_child(int child_id, const string child_action, signed char child_function);

    void add_child_recursively(vector<int> id_vec, vector<string> action_vec, vector<signed char> function_vec);

    void list_recursively();

    void perform(vector<int> keylist, int &layer);

    void perform_recursively(vector<int> modifiable_keylist, vector<int> original_keylist, int &layer, int depth);
};

#endif