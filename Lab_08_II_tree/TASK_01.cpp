#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node *left, *right;
    Node(string n) : name(n), left(NULL), right(NULL) {}
};

string nm(Node* n) { return n ? n->name : "None"; }

void display(Node* r) {
    if (!r) return;
    cout << r->name << " -> Left: " << nm(r->left) << ", Right: " << nm(r->right) << endl;
    display(r->left);
    display(r->right);
}

int main() {
    Node* hod = new Node("Dr. Ahmed (HOD)");
    hod->left = new Node("Dr. Sara (Coordinator)");
    hod->right = new Node("Mr. Bilal (Coordinator)");
    hod->left->left = new Node("Ms. Ayesha (Faculty)");
    hod->left->right = new Node("Mr. Usman (Faculty)");
    hod->right->left = new Node("Ms. Hina (Faculty)");
    hod->right->right = new Node("Mr. Faisal (Faculty)");
    display(hod);
    return 0;
}
