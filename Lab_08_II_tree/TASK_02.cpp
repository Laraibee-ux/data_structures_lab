#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Node {
public:
    string name;
    Node *left, *right;
    Node(string n) : name(n), left(NULL), right(NULL) {}
};

void bfs(Node* root) {
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        cout << cur->name << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    cout << endl;
}

int main() {
    Node* root = new Node("Store");
    root->left = new Node("Electronics");
    root->right = new Node("Clothing");
    root->left->left = new Node("Mobiles");
    root->left->right = new Node("Laptops");
    root->right->left = new Node("Men");
    root->right->right = new Node("Women");
    root->left->left->left = new Node("Accessories");
    bfs(root);
    return 0;
}
