// ============================================================
//  Lab 08 - Task 2 : Hospital and Emergency Inventory Management
//  Menu-driven BST application (patient record / supply IDs)
//  Height is counted in LEVELS (nodes on the longest root-to-leaf
//  path). An empty tree has height 0. (Height in edges = levels - 1.)
// ============================================================
#include <iostream>
#include <limits>
using namespace std;

class BST {
private:
    struct Node {
        int id;
        Node* left;
        Node* right;
        Node(int v) : id(v), left(nullptr), right(nullptr) {}
    };
    Node* root;

    // ---- helpers (recursive) ----
    Node* insertNode(Node* n, int v, bool& inserted) {
        if (!n) { inserted = true; return new Node(v); }
        if (v < n->id)      n->left  = insertNode(n->left,  v, inserted);
        else if (v > n->id) n->right = insertNode(n->right, v, inserted);
        else                inserted = false;            // duplicate: no change
        return n;
    }
    Node* findMin(Node* n) const {
        while (n && n->left) n = n->left;
        return n;
    }
    Node* deleteNode(Node* n, int v, bool& deleted) {
        if (!n) return nullptr;
        if (v < n->id)      n->left  = deleteNode(n->left,  v, deleted);
        else if (v > n->id) n->right = deleteNode(n->right, v, deleted);
        else {
            deleted = true;
            if (!n->left)  { Node* r = n->right; delete n; return r; }  // leaf / right child only
            if (!n->right) { Node* l = n->left;  delete n; return l; }  // left child only
            Node* succ = findMin(n->right);              // two children
            n->id = succ->id;                            // copy successor value
            bool tmp = false;
            n->right = deleteNode(n->right, succ->id, tmp);  // remove successor node
        }
        return n;
    }
    void inorder(Node* n) const   { if (!n) return; inorder(n->left);  cout << n->id << " "; inorder(n->right); }
    void preorder(Node* n) const  { if (!n) return; cout << n->id << " "; preorder(n->left);  preorder(n->right); }
    void postorder(Node* n) const { if (!n) return; postorder(n->left); postorder(n->right); cout << n->id << " "; }
    int  countNodes(Node* n) const { return n ? 1 + countNodes(n->left) + countNodes(n->right) : 0; }
    int  height(Node* n) const {
        if (!n) return 0;
        int l = height(n->left), r = height(n->right);
        return 1 + (l > r ? l : r);
    }
    void destroy(Node* n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }
    BST(const BST&) = delete;                            // prevent accidental shallow copy
    BST& operator=(const BST&) = delete;

    bool isEmpty() const { return root == nullptr; }

    bool insert(int v) { bool ok = false; root = insertNode(root, v, ok); return ok; }

    bool search(int v) const {
        Node* cur = root;
        while (cur) {
            if (v == cur->id) return true;
            cur = (v < cur->id) ? cur->left : cur->right;
        }
        return false;
    }
    bool remove(int v) { bool ok = false; root = deleteNode(root, v, ok); return ok; }

    void displayInorder()   const { inorder(root);   cout << "\n"; }
    void displayPreorder()  const { preorder(root);  cout << "\n"; }
    void displayPostorder() const { postorder(root); cout << "\n"; }
    int  getCount()  const { return countNodes(root); }
    int  getHeight() const { return height(root); }
};

// ---------------- input validation ----------------
int readInt(const char* prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        if (cin.eof()) return -1;
        cout << "Invalid input! Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void showMenu() {
    cout << "\n=========== HOSPITAL INVENTORY BST MENU ===========\n"
         << " 1. Insert an ID\n"
         << " 2. Search for an ID\n"
         << " 3. Delete an ID\n"
         << " 4. Display in-order traversal\n"
         << " 5. Display pre-order traversal\n"
         << " 6. Display post-order traversal\n"
         << " 7. Count total number of nodes\n"
         << " 8. Calculate height of the BST\n"
         << " 9. Exit\n"
         << "===================================================\n";
}

int main() {
    BST tree;
    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int id : initial) tree.insert(id);
    cout << "Initial IDs loaded: 55 35 75 25 45 65 85 40 50\n";

    int choice;
    do {
        showMenu();
        choice = readInt("Enter your choice (1-9): ");
        if (cin.eof()) break;
        switch (choice) {
        case 1: {
            int id = readInt("Enter ID to insert: ");
            if (tree.insert(id)) cout << "ID " << id << " inserted successfully.\n";
            else                 cout << "ID " << id << " already exists. Duplicate rejected; tree unchanged.\n";
            break;
        }
        case 2: {
            if (tree.isEmpty()) { cout << "Tree is empty. Nothing to search.\n"; break; }
            int id = readInt("Enter ID to search: ");
            cout << "ID " << id << (tree.search(id) ? " FOUND in the tree.\n" : " NOT FOUND in the tree.\n");
            break;
        }
        case 3: {
            if (tree.isEmpty()) { cout << "Tree is empty. Nothing to delete.\n"; break; }
            int id = readInt("Enter ID to delete: ");
            if (tree.remove(id)) {
                cout << "ID " << id << " deleted successfully.\n";
                cout << "Updated IDs (in-order): ";
                tree.displayInorder();
            } else cout << "ID " << id << " does not exist. Nothing deleted.\n";
            break;
        }
        case 4:
            if (tree.isEmpty()) cout << "Tree is empty.\n";
            else { cout << "In-order   : "; tree.displayInorder(); }
            break;
        case 5:
            if (tree.isEmpty()) cout << "Tree is empty.\n";
            else { cout << "Pre-order  : "; tree.displayPreorder(); }
            break;
        case 6:
            if (tree.isEmpty()) cout << "Tree is empty.\n";
            else { cout << "Post-order : "; tree.displayPostorder(); }
            break;
        case 7:
            cout << "Total number of nodes: " << tree.getCount() << "\n";
            break;
        case 8:
            cout << "Height of BST: " << tree.getHeight()
                 << " levels (" << (tree.isEmpty() ? 0 : tree.getHeight() - 1) << " edges)\n";
            break;
        case 9:
            cout << "Exiting program. All memory released by destructor. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please select a number between 1 and 9.\n";
        }
    } while (choice != 9);
    return 0;
}
