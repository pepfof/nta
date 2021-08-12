#ifndef NTAKEY_H_   /* Include guard */
#define NTAKEY_H_

#include <string>
#include <vector>
#include <stdio.h>
#include "nta_basics.h"


using namespace std;

int nta_expand(string input_string, string& output_string, vector<int> keylist){
    if(!input_string.empty()){

    output_string=input_string;
    int got_level = -1;
    string temp_output_string = output_string;

    nta_report(3,"Expanding: " + temp_output_string);

    while(temp_output_string.rfind("NTA#")!=string::npos)
    {
        int pos = temp_output_string.rfind("NTA#");
        temp_output_string.erase(pos, 4);
        try{
        int got_key = stoi(temp_output_string.substr(pos, string::npos));
        string to_delete = to_string(got_key);
        temp_output_string.erase(pos, to_delete.length());
        if(got_key<keylist.size()) temp_output_string.insert(pos, to_string(keylist[got_key]));
        }
        catch(const invalid_argument) {
            nta_report(3,"No integer in NTA#, passing nothing");
        }
        }

    nta_report(3,"After NTA# pass: " + temp_output_string);

    if(temp_output_string.rfind("NTA~")!=string::npos){
        int pos = temp_output_string.rfind("NTA~");
        temp_output_string.erase(pos, 4);
        try{
        got_level = stoi(temp_output_string.substr(pos, string::npos));
        string to_delete = to_string(got_level);
        temp_output_string.erase(pos, to_delete.length());
        nta_report(3,"Found layer to switch to: " + to_string(got_level));
        }
        catch(const invalid_argument) {
            nta_report(3,"No integer in NTA~, not changing layer");
            got_level = -1;
        }
    }

    nta_report(3,"After NTA~ pass: " + temp_output_string);
    output_string=temp_output_string;

    return got_level;}
    return -1;
};

class ntakey {
public:
    int own_id;
    string own_action;
    vector<ntakey> child_key;

    ntakey(int new_id = 0, string new_action = "") {
        own_id = new_id;
        own_action = new_action;
    }

    int has_child(int child_id) {
        int i = 0;
        while (i < child_key.size()) {
            if (child_id == child_key.at(i).own_id) {
                return 1;
            }
            i++;
        }
        return 0;
    }

    ntakey& get_child(int child_id) {
        int i = 0;
        while (i < child_key.size()) {
            if (child_id == child_key.at(i).own_id) {
                return child_key.at(i);
            }
            i++;
        }
        return *this;
    }

    ntakey& add_child(int child_id, const string& child_action) {
        if (has_child(child_id)) {
            return get_child(child_id);
        } // If child with specified id already exists, return it and abort.
          // Else: 

        ntakey newkey(child_id, child_action);
        // Create temporary key, write child_id to it's id, child_action to it's action.

        child_key.push_back(newkey);
        return child_key.back();
        // Add key to child_key vector, return it.
    }

    void add_child_recursively(vector<int> numbers_arr, vector<string> actions_arr) {

        ntakey& child_added = add_child(numbers_arr[0], actions_arr[0]);

        numbers_arr.erase(numbers_arr.begin());
        actions_arr.erase(actions_arr.begin());

        if (!numbers_arr.empty())  child_added.add_child_recursively(numbers_arr, actions_arr);
    }

    void list_recursively(int level, int vanity){
        string temp;
        if(level == 2) {
        printf("%d: %s\n", own_id, own_action.c_str());
        }
        else if(level>1){
            printf("%s",temp.insert(0, (level-2)*2, ' ').c_str());
            printf("%d: %s\n", own_id, own_action.c_str());}
        else if(level==1){
            printf("\nLAYER %d: %s\n", own_id, own_action.c_str());
        }
        int i = 0;
        while (i < child_key.size()) {
            child_key[i].list_recursively(level+1, (i!=child_key.size()-1)+1);
            i++;
            }
    }

    void execute(vector<int> keylist, int &level)
    {
        string expanded_action;
        int new_level = nta_expand(own_action, expanded_action, keylist);
        if(!expanded_action.empty()) nta_report(5, "----- Command output begin -----");
        system(expanded_action.c_str());
        if(!expanded_action.empty()) nta_report(5, "-----  Command output end  -----\n");
        if(new_level!=-1) {
            nta_report(2,"Switching to layer " + to_string(new_level));
            level = new_level;
        }
    }

    void execute_recursively(vector<int> modifiable_keylist, vector<int> original_keylist, int &level)
    {        
        execute(original_keylist, level);

        if(!modifiable_keylist.empty())
        {
            if (has_child(modifiable_keylist[0]))
            {
                ntakey found_child = get_child(modifiable_keylist[0]);
                nta_report(4,"Found child " + to_string(modifiable_keylist[0]) + " in parent " + to_string(own_id)+ " - executing it");
                modifiable_keylist.erase(modifiable_keylist.begin());
                found_child.execute_recursively(modifiable_keylist,original_keylist, level);
            }
            else{
                nta_report(4,"Child " + to_string(modifiable_keylist[0]) + " in parent " + to_string(own_id)+ " not found");
            }
        }
    }
};

#endif 