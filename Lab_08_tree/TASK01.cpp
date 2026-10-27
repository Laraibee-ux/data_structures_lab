// ============================================================
//  Lab 08 - Task 1 : University Staff Management System
//  Part A : General Binary Tree (Node class)
//  Part B : Binary Search Tree (BST class) for unique staff IDs
// ============================================================
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ---------------------------------------------------------
//  PART A : GENERAL BINARY TREE
// ---------------------------------------------------------
class Node {
public:
    string name;
    Node* left;
    Node* right;
    Node(const string& n) : name(n), left(nullptr), right(nullptr) {}
};

class StaffTree {
private:
    Node* root;

    void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
    void display(Node* n) const {
        if (!n) return;
        cout << "  " << n->name
             << "  |  Left: "  << (n->left  ? n->left->name  : "NULL")
             << "  |  Right: " << (n->right ? n->right->name : "NULL") << "\n";
        display(n->left);
        display(n->right);
    }
    void inorder(Node* n) const {
        if (!n) return;
        inorder(n->left);
        cout << n->name << " | ";
        inorder(n->right);
    }
public:
    StaffTree() : root(nullptr) {}
    ~StaffTree() { destroy(root); }

    // Manually connect 8 staff members (no ordering rule)
    void build() {
        root = new Node("Dr. Ahmed (VC)");
        root->left  = new Node("Dr. Sara (Dean)");
        root->right = new Node("Mr. Bilal (Registrar)");
        root->left->left   = new Node("Prof. Zain");
        root->left->right  = new Node("Ms. Hina");
        root->right->left  = new Node("Mr. Usman");
        root->right->right = new Node("Ms. Ayesha");
        root->left->left->left = new Node("Mr. Kamran");
    }
    void display() const { display(root); }
    void inorder()  const { inorder(root); cout << "\n"; }
};

// ---------------------------------------------------------
//  PART B : BINARY SEARCH TREE OF STAFF IDs
// ---------------------------------------------------------
class BST {
private:
    struct BNode {
        int id;
        BNode* left;
        BNode* right;
        BNode(int v) : id(v), left(nullptr), right(nullptr) {}
    };
    BNode* root;

    BNode* copyTree(BNode* n) const {            // deep copy
        if (!n) return nullptr;
        BNode* c = new BNode(n->id);
        c->left  = copyTree(n->left);
        c->right = copyTree(n->right);
        return c;
    }
    void destroy(BNode* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
    BNode* findMin(BNode* n) const {
        while (n && n->left) n = n->left;
        return n;
    }
    BNode* remove(BNode* n, int v, bool& found, string& type) {
        if (!n) return nullptr;
        if (v < n->id)      n->left  = remove(n->left,  v, found, type);
        else if (v > n->id) n->right = remove(n->right, v, found, type);
        else {
            found = true;
            if (!n->left && !n->right) {                 // Case 1: leaf
                type = "Leaf node (no children)";
                delete n;
                return nullptr;
            }
            if (!n->left || !n->right) {                 // Case 2: one child
                type = "Node with ONE child";
                BNode* child = n->left ? n->left : n->right;
                delete n;
                return child;
            }
            type = "Node with TWO children (replaced by in-order successor)";
            BNode* succ = findMin(n->right);             // Case 3: two children
            n->id = succ->id;
            bool f2 = false; string t2;
            n->right = remove(n->right, succ->id, f2, t2);
        }
        return n;
    }
    void inorder(BNode* n) const {
        if (!n) return;
        inorder(n->left);
        cout << n->id << " ";
        inorder(n->right);
    }
    void sideways(BNode* n, int depth) const {           // prints tree rotated 90 deg
        if (!n) return;
        sideways(n->right, depth + 1);
        cout << string(depth * 6, ' ') << n->id << "\n";
        sideways(n->left, depth + 1);
    }
public:
    BST() : root(nullptr) {}
    BST(const BST& o) : root(copyTree(o.root)) {}
    BST& operator=(const BST& o) {
        if (this != &o) { destroy(root); root = copyTree(o.root); }
        return *this;
    }
    ~BST() { destroy(root); }

    bool insert(int v) {                                 // false if duplicate
        if (!root) { root = new BNode(v); return true; }
        BNode* cur = root;
        while (true) {
            if (v == cur->id) return false;              // duplicate: tree unchanged
            if (v < cur->id) {
                if (!cur->left)  { cur->left  = new BNode(v); return true; }
                cur = cur->left;
            } else {
                if (!cur->right) { cur->right = new BNode(v); return true; }
                cur = cur->right;
            }
        }
    }
    bool search(int v, int& visits) const {
        visits = 0;
        BNode* cur = root;
        while (cur) {
            visits++;
            if (v == cur->id) return true;
            cur = (v < cur->id) ? cur->left : cur->right;
        }
        return false;
    }
    bool remove(int v, string& type) {
        bool found = false;
        root = remove(root, v, found, type);
        return found;
    }
    void inorder() const { inorder(root); cout << "\n"; }
    void show() const { sideways(root, 0); }
};

// ---------------------------------------------------------
//  Helpers
// ---------------------------------------------------------
int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cout << "  Invalid input. Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void doSearch(const BST& t, int v) {
    int visits;
    bool ok = t.search(v, visits);
    cout << "  Search " << v << " -> " << (ok ? "FOUND" : "NOT FOUND")
         << " | node visits = " << visits << "\n";
}

void testDeletion(const BST& original, int v, const string& label) {
    BST fresh(original);                                 // fresh copy of original BST
    cout << "\n  --- " << label << " : delete " << v << " ---\n";
    cout << "  Before (in-order): "; fresh.inorder();
    string type;
    if (fresh.remove(v, type)) {
        cout << "  Case detected    : " << type << "\n";
        cout << "  After  (in-order): "; fresh.inorder();
        cout << "  Tree structure (rotated, root at left):\n";
        fresh.show();
    } else cout << "  ID not found.\n";
}

int main() {
    cout << "=========== PART A: GENERAL BINARY TREE ===========\n";
    StaffTree staff;
    staff.build();
    cout << "Each staff member with Left / Right child:\n";
    staff.display();
    cout << "\nIn-order traversal of the general tree (NOT sorted):\n  ";
    staff.inorder();

    cout << "\n=========== PART B: BST OF STAFF IDs ===========\n";
    BST bst;
    int initial[] = {48, 28, 68, 18, 38, 58, 78};
    for (int id : initial) bst.insert(id);
    cout << "Initial IDs inserted: 48 28 68 18 38 58 78\n";
    cout << "In-order: "; bst.inorder();

    cout << "\nEnter THREE additional staff IDs (duplicates are rejected):\n";
    int accepted = 0;
    while (accepted < 3) {
        int id = readInt("  Enter staff ID #" + to_string(accepted + 1) + ": ");
        if (bst.insert(id)) { cout << "  Inserted " << id << ".\n"; accepted++; }
        else cout << "  Duplicate ID " << id << " rejected. Tree unchanged.\n";
    }
    cout << "\nBST after insertions (in-order): "; bst.inorder();
    cout << "Tree structure (rotated, root at left):\n"; bst.show();

    BST original(bst);                                   // keep original for fresh copies

    cout << "\n--- SEARCH TESTS (with node-visit count) ---\n";
    cout << "  [Existing ID]\n";            doSearch(original, 38);
    cout << "  [Missing ID]\n";             doSearch(original, 100);
    cout << "  [Smaller than all IDs]\n";   doSearch(original, 5);
    int s = readInt("  Enter an ID to search: ");
    doSearch(original, s);

    cout << "\n--- USER DELETION ---\n";
    int d = readInt("Enter a staff ID to delete: ");
    BST working(original);
    string type;
    if (working.remove(d, type)) {
        cout << "  Deleted " << d << " (" << type << ").\n";
    } else cout << "  ID " << d << " not found. Nothing deleted.\n";
    cout << "  Remaining IDs in ascending order: "; working.inorder();

    cout << "\n--- DELETION CASES (each on a FRESH copy of the original BST) ---";
    testDeletion(original, 38, "Case 1: LEAF node");
    testDeletion(original, 18, "Case 2: node with ONE child");
    testDeletion(original, 48, "Case 3: node with TWO children (root)");

    cout << "\n=========== WHY IN-ORDER DIFFERS ===========\n";
    cout << "A general binary tree has NO rule about where values are placed, so\n"
         << "Left-Root-Right visits them in whatever order they were linked, which\n"
         << "is usually not sorted. A valid BST guarantees every value in the left\n"
         << "subtree < node < every value in the right subtree, so in-order\n"
         << "(Left, Root, Right) always visits values in ascending order.\n";
    return 0;
}
