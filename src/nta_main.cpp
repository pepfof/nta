#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
#include <thread>
#include "nta_key.h"
#include "nta_basics.h"
using namespace std;

int current_level = 0;

int nta_execute(char* command){
    //
}

void SplitString(string s, vector<int>& v) {

    v.clear();
    string temp = "";
    for (int i = 0; i < s.length(); ++i) {

        if (s[i] == ' ') {
            try{
            v.push_back(stoi(temp));
            }
            catch(const invalid_argument) {
                nta_report(1,"Input formatted incorrectly, aborting execution");
                v.clear();
                return;
            }
            temp = "";
        }
        else {
            temp.push_back(s[i]);
        }

    }
    try{
        v.push_back(stoi(temp));
    }
    catch(const invalid_argument) {
        return;
    }

}

void PrintVector(vector<int> v) {
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << endl;
    cout << "\n";
}


int main(int argc, char *argv[])
{
    nta_report_determine_levels(argc, argv);
    vector<int> v = { 2, 7, 5, 16, 8 };
    vector<int> ex;
    vector<int> va = { 0, 1 };
    vector<string> ab = { "echo 'this is level NTA#0'","NTA~NTA#2", "caja &", "hi dads lol", "bam" };
    vector<string> a = { "echo 'this is level NTA#0'","NTA~NTA#2", "caja &", "hi dads lol", "bam" };
    ntakey testkey(0, "");

    testkey.add_child_recursively(v, ab);
    testkey.add_child_recursively(va, a);

    string userinput = "1 2 3 4";

    while(1){
        printf("NTA @> ");
        getline(cin, userinput);
        SplitString(userinput, ex);
        ex.insert(ex.begin(), current_level);
        userinput.clear();
        int temp_level = current_level;
        if(!ex.empty()) testkey.execute_recursively(ex, ex, temp_level);
        if(testkey.has_child(temp_level)) current_level = temp_level;
        else if(temp_level!=current_level) 
            nta_report(0,"Layer "+ to_string(temp_level) + " is not defined, reverting to level " + to_string(current_level));
    }
}