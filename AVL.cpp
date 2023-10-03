#include "AVL.h"
#include <iostream>
#include <string>
#include <queue>

using namespace std;

int Height(Node* node) {
    if (node == nullptr)
        return 0;

    return max(Height(node->left), Height(node->right)) + 1;
}
int BalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return Height(node->left) - Height(node->right);
}
Node* RotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(Height(y->left), Height(y->right)) + 1;
    x->height = max(Height(x->left), Height(x->right)) + 1;

    return x;
}
Node* RotateLeft(Node* x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(Height(x->left), Height(x->right)) + 1;
    y->height = max(Height(y->left), Height(y->right)) + 1;

    return y;
}
Node* AVLTree ::InsertHelper(Node *root, string name, string ufid) {
    if (root == nullptr) {
        Node* newNode = new Node(name, ufid);
        return newNode;
    }
    if (ufid < root->ufid) {
        root->left = InsertHelper(root->left, name, ufid);
    } else if (ufid > root->ufid) {
        root->right = InsertHelper(root->right, name, ufid);
    } else {
        return nullptr;
    }

    // TODO: Update height, balance factor, and perform rotations

    if (BalanceFactor(root) > 1) {
        if (ufid < root->left->ufid) {
            // Left-Left case
            return RotateRight(root);
        } else {
            // Left-Right case
            root->left = RotateLeft(root->left);
            return RotateRight(root);
        }
    } else if (BalanceFactor(root) < -1) {
        if (ufid > root->right->ufid) {
            // Right-Right case
            return RotateLeft(root);
        } else {
            // Right-Left case
            root->right = RotateRight(root->right);
            return RotateLeft(root);
        }
    }

    // Update height after rotations
    root->height = Height(root);

    return root;

}
void inorder(Node* root, bool &first) {
    if (root == nullptr)
        return;
    inorder(root->left, first);
    if(!first){
        cout<<", ";
    }
    cout<<root->name;
    first=false;
    inorder(root->right, first);
}
void preorder(Node* root, bool &first){
    if (root == nullptr)
        return;

    if (!first) {
        cout << ", ";
    }
    cout << root->name;
    first = false;

    preorder(root->left, first);
    preorder(root->right, first);
}
void postorder(Node* root, bool &first){
    if (root == nullptr)
        return;

    postorder(root->left, first);
    postorder(root->right, first);

    if (!first) {
        cout << ", ";
    }
    cout << root->name;
    first = false;
}
int LevelCount(Node* head) {
    if (head == nullptr)
        return 0;

    queue<Node*> q;
    q.push(head);

    int levelCount = 0;

    while (!q.empty()) {
        int levelSize = q.size();  // Number of nodes at the current level

        // Visit nodes at the current level
        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            if (current->left != nullptr)
                q.push(current->left);

            if (current->right != nullptr)
                q.push(current->right);
        }

        // Increment the level count after visiting all nodes at the current level
        levelCount++;
    }

    return levelCount;
}
string searchufid(Node* head, string ufid){
    if (head == nullptr) {
        return "unsuccessful";
    }
    if (head->ufid == ufid) {
        return head->name;
    }

    if (ufid < head->ufid) {
        return searchufid(head->left, ufid);
    } else {
        return searchufid(head->right, ufid);
    }
}
void searchName(Node* head, const string& name, vector<string>& ufidList) {
    if (head == nullptr)
        return;

    if (head->name == name) {
        ufidList.push_back(head->ufid);
    }

    searchName(head->left, name, ufidList);
    searchName(head->right, name, ufidList);
}
vector<string> searchUfidsByName(Node* head, const string& name) {
    vector<string> ufidList;
    searchName(head, name, ufidList);
    return ufidList;
}
Node* remove(Node* root, string ufid)
{
    // Base case
    if (root == NULL)
        return root;

    // Recursive calls for ancestors of
    // node to be deleted
    if (root->ufid > ufid) {
        root->left = remove(root->left, ufid);
        return root;
    }
    else if (root->ufid < ufid) {
        root->right = remove(root->right, ufid);
        return root;
    }

    // We reach here when root is the node
    // to be deleted.

    // If one of the children is empty
    if (root->left == NULL) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        Node* temp = root->left;
        delete root;
        return temp;
    }

        // If both children exist
    else {

        Node* succParent = root;

        // Find successor
        Node* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        // Copy Successor Data to root
        root->ufid = succ->ufid;
        root->name= succ->name;

        // Delete Successor and return root
        delete succ;
        return root;
    }
}
Node* removeInorder(Node* root, int N, int &count){

    if(root==nullptr){
        return nullptr;
    }
    root->left = removeInorder(root->left, N, count);
    count++;

    if(count == N+1){
        remove(root, root->ufid);
        cout<<"successful"<<endl;
        return nullptr;

    }

    root->right = removeInorder(root->right, N, count);
    return root;
}
