#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node *left, *right;
    Node(string n) : name(n), left(NULL), right(NULL) {}
};

void inorder(Node* r) {
    if (!r) return;
    inorder(r->left);
    cout << r->name << " ";
    inorder(r->right);
}

void preorder(Node* r) {
    if (!r) return;
    cout << r->name << " ";
    preorder(r->left);
    preorder(r->right);
}

void postorder(Node* r) {
    if (!r) return;
    postorder(r->left);
    postorder(r->right);
    cout << r->name << " ";
}

int main() {
    Node* root = new Node("C:");
    root->left = new Node("Users");
    root->right = new Node("ProgramFiles");
    root->left->left = new Node("Documents");
    root->left->right = new Node("Downloads");
    root->right->left = new Node("Python");
    root->right->right = new Node("Games");
    cout << "Inorder: ";   inorder(root);   cout << endl;
    cout << "Preorder: ";  preorder(root);  cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;
    return 0;
}
