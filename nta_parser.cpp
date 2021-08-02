#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;



class ntakey{
    public:
        ntakey *parent_key;
        int own_recursion_level;
        int own_id = 666;
        string own_action;
        string child_action;
        vector<ntakey> child_key;
        
        int has_child(int child_id, int *child_vector_id){
            int i = 0;
            while(i<child_key.size()){
                if(child_id==child_key.at(i).own_id) {
                    *child_vector_id=i;
                    return 1;
                }
                i++;
            }
            *child_vector_id=0;
            return 0;
        }

        void execute(){
            printf("command");
        }
        
        void execute_recursive(vector<int> &numbers_arr)
        {   
            printf("command");
            
            int child_vector_id;
            if(has_child(numbers_arr[0], &child_vector_id)){

                numbers_arr.erase(numbers_arr.begin());

                if(numbers_arr.empty()){
                    child_key.at(child_vector_id).execute();
                }

                else{
                    child_key.at(child_vector_id).execute_recursive(numbers_arr);
                }
            }
        }
};



void SplitString(string s, vector<int> &v){
	
	string temp = "";
	for(int i=0;i<s.length();++i){
		
		if(s[i]==' '){
			v.push_back(stoi(temp));
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}
		
	}
	v.push_back(stoi(temp));
	
}

void PrintVector(vector<int> v){
	for(int i=0;i<v.size();++i)
		cout<<v[i]<<endl;
	cout<<"\n";
}

int main()
{
    vector<int> massiv;
    vector<ntakey> ntkmassiv;
    string massiv_string;
    getline(cin, massiv_string);
    SplitString(massiv_string, massiv);
}
