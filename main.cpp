#include <iostream>
#include "AVL.h"
#include <string>
#include <regex>
#include <queue>

using namespace std;


int main(){
    AVLTree h;

    string numCommands;
    getline(cin, numCommands);

    for (int i = 0; i < stoi(numCommands); i++){
        string line;
        getline(cin, line);

        istringstream in(line);

        string command;
        in >> command;

        string name;
        string ufid;
        string node;

        if(command == "insert"){
            char quote;
            in >> quote;  // Read the opening quotation mark
            getline(in, name, '"');  // Read the name until the closing quotation mark

            in >> ufid;
            if(ufid.length() < 8 || ufid.length() > 8){
                cout<<"unsuccessful"<<endl;
            }
            else if(!regex_match(name, std::regex("^[A-Za-z ]+$"))){
                cout<<"unsuccessful"<<endl;
            }
            else{

                h.root = h.AVLTree::Insert(name, ufid);
                cout<<"successful"<<endl;
            }
        }

        else if(command == "remove"){
            in >> ufid;
            if(ufid.length() < 8 || ufid.length() > 8){
                cout<<"unsuccessful"<<endl;
            }
            else{
                h.root = remove(h.root, ufid);
                cout<<endl<<"successful"<<endl;
                //here
            }
        }
        else if(command == "search"){
            char quote;
            in >> quote;  // Read the opening quotation mark
            getline(in, name, '"');  // Read the name until the closing quotation mark
            ufid = quote+name;
            if(regex_match(ufid, std::regex("^[1-9][0-9]{7}$")) && ((name.length() + 1) == 8)){
                string name = searchufid(h.root, ufid);
                cout<<name<<endl;
            }
            else if(!regex_match(name, std::regex("^[A-Za-z ]+$"))){
                cout<<"unsuccessful"<<endl;
            }
            else if(regex_match(name, std::regex("^[A-Za-z ]+$"))){
                vector<string> ufidList = searchUfidsByName(h.root, name);

                if (ufidList.empty()) {
                    cout << "unsuccessful" << endl;
                } else {
                    for (const string& ufid : ufidList) {
                        cout << ufid << endl;
                    }
                }
            }
            else{
                cout<<"unsuccessful";
            }
        }
        else if(command == "printInorder"){
            bool first = true;
            inorder(h.root, first);
        }
        else if(command == "printPreorder"){
            bool first = true;
            preorder(h.root, first);
        }
        else if(command == "printPostorder"){
            bool first = true;
            postorder(h.root, first);
        }
        else if(command == "printLevelCount"){
            int levels = LevelCount(h.root);  // Assuming 'root' is the root of your AVL tree
            cout << levels << endl;
        }
        else if(command == "removeInorder"){
            string node;
            in >> node;
            int N = stoi(node);
            int count = 0;
            h.root = removeInorder(h.root, N, count);
        }
        else{
            cout<< "unsuccessful";
        }

    }
    return 0;
    }

