#include <vector>
#include <string>
using namespace std;

class ntakey{
    public:
        ntakey *parent_key
        int own_id;
        string own_action;
        string child_action;
        int own_num_children = 0;
        vector<ntakey> child_key(0);
        
        int add_child(int add_child_id, string add_child_action){
            ntakey newkey;
            newkey.own_id = add_child_id;
            newkey.own_action = add_child_action;
            int i = 0;
            while(i<own_num_children){
                if(child_key.at(i).own_id==add_child_id) break;
                i++;
            }
            if(i==own_num_children){
                child_key.push_back(newkey);
                return 0;
            }
            else return 1;
        }

        
}
int main(){}