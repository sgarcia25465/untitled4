#pragma once
#include <string>
#include <vector>
using namespace std;

struct Node{
    string name;
    string ufid;
    int height;
    Node* left;
    Node* right;
    Node(const std::string& name, const std::string& ufid) : name(name), ufid(ufid), left(nullptr), right(nullptr){}
};
class AVLTree{
private:
    Node* InsertHelper(Node* root, string name, string ufid);
public:
    Node* root;
    Node* Insert(string name, string ufid){
        this -> root = InsertHelper(this->root, name, ufid);
        return this-> root;
    }
    AVLTree() : root() {}
};
void inorder(Node* root, bool &first);
void preorder(Node* root, bool &first);
void postorder(Node* root, bool &first);
int LevelCount(Node* head);
string searchufid(Node* head, string ufid);
void searchName(Node* head, const string& name, vector<string>& ufidList);
vector<string> searchUfidsByName(Node* head, const string& name);
Node* remove(Node* root, string ufid);
Node* removeInorder(Node* root, int N, int &count);