#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key, h;
    Node *left, *right;
    Node(int k) : key(k), h(1), left(NULL), right(NULL) {}
};

int height(Node* n) { return n ? n->h : 0; }
int balance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }
void update(Node* n) { n->h = 1 + max(height(n->left), height(n->right)); }

Node* rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    update(y);
    update(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    update(x);
    update(y);
    return y;
}

Node* insert(Node* n, int k) {
    if (!n) return new Node(k);
    if (k < n->key) n->left = insert(n->left, k);
    else if (k > n->key) n->right = insert(n->right, k);
    else return n;
    update(n);
    int b = balance(n);
    if (b > 1 && k < n->left->key) return rightRotate(n);
    if (b < -1 && k > n->right->key) return leftRotate(n);
    if (b > 1 && k > n->left->key) { n->left = leftRotate(n->left); return rightRotate(n); }
    if (b < -1 && k < n->right->key) { n->right = rightRotate(n->right); return leftRotate(n); }
    return n;
}

void inorder(Node* n) {
    if (!n) return;
    inorder(n->left);
    cout << n->key << "(h=" << n->h << ",bf=" << balance(n) << ") ";
    inorder(n->right);
}

void show(Node* n, int lvl) {
    if (!n) return;
    show(n->right, lvl + 1);
    for (int i = 0; i < lvl; i++) cout << "    ";
    cout << n->key << endl;
    show(n->left, lvl + 1);
}

int main() {
    Node* root = NULL;
    int tokens[] = {15, 25, 35, 45, 55, 65, 75};
    for (int i = 0; i < 7; i++) root = insert(root, tokens[i]);
    cout << "Inorder: ";
    inorder(root);
    cout << endl << "Tree:" << endl;
    show(root, 0);
    return 0;
}
