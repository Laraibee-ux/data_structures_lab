// Lab 09 - Task 4: Hospital Medicine Expiry Management (Min Heap)
#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

class MedicineNode {
public:
    string name;
    int medicineID;
    int expiry;            // YYYYMMDD
    MedicineNode *left, *right;
    MedicineNode(string n, int id, int e)
        : name(n), medicineID(id), expiry(e), left(nullptr), right(nullptr) {}
};

string formatDate(int d) {   // 20271015 -> 2027-03-15
    string s = to_string(d);
    return s.substr(0, 4) + "-" + s.substr(4, 2) + "-" + s.substr(6, 2);
}

class MinHeap {
private:
    MedicineNode *root;
    int count;

    vector<MedicineNode*> getPath(int pos) {
        vector<MedicineNode*> path;
        int highest = 1;
        while (highest * 2 <= pos) highest *= 2;
        MedicineNode *cur = root;
        path.push_back(cur);
        for (int bit = highest / 2; bit >= 1; bit /= 2) {
            cur = (pos & bit) ? cur->right : cur->left;
            path.push_back(cur);
        }
        return path;
    }

    void swapData(MedicineNode *a, MedicineNode *b) {
        swap(a->name, b->name);
        swap(a->medicineID, b->medicineID);
        swap(a->expiry, b->expiry);
    }

    void heapifyUp() {
        vector<MedicineNode*> path = getPath(count);
        for (int i = path.size() - 1; i > 0; i--) {
            if (path[i]->expiry < path[i - 1]->expiry) {
                cout << "   Heapify Up: swap " << path[i]->name << " (" << formatDate(path[i]->expiry)
                     << ") with parent " << path[i - 1]->name << " (" << formatDate(path[i - 1]->expiry) << ")\n";
                swapData(path[i], path[i - 1]);
            } else break;
        }
    }

    void heapifyDown() {
        MedicineNode *cur = root;
        while (cur && cur->left) {
            MedicineNode *small = cur->left;
            if (cur->right && cur->right->expiry < small->expiry) small = cur->right;
            if (small->expiry < cur->expiry) {
                cout << "   Heapify Down: swap " << cur->name << " (" << formatDate(cur->expiry)
                     << ") with child " << small->name << " (" << formatDate(small->expiry) << ")\n";
                swapData(cur, small);
                cur = small;
            } else break;
        }
    }

    void destroy(MedicineNode *n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    MinHeap() : root(nullptr), count(0) {}
    ~MinHeap() { destroy(root); }

    void insert(string name, int id, int expiry) {
        MedicineNode *node = new MedicineNode(name, id, expiry);
        count++;
        if (count == 1) root = node;
        else {
            MedicineNode *parent = getPath(count / 2).back();
            if (count % 2 == 0) parent->left = node;
            else parent->right = node;
        }
        cout << "Inserted: " << name << " | ID " << id << " | Expiry " << formatDate(expiry) << endl;
        heapifyUp();
    }

    void showNearestExpiry() {
        if (!root) { cout << "No medicines in stock!\n"; return; }
        cout << "Nearest expiry: " << root->name << " | ID " << root->medicineID
             << " | Expiry " << formatDate(root->expiry) << endl;
    }

    void deleteNearestExpiry() {
        if (!root) { cout << "No medicines in stock!\n"; return; }
        cout << "\nDeleting medicine with nearest expiry: " << root->name << " | ID "
             << root->medicineID << " | Expiry " << formatDate(root->expiry) << endl;
        if (count == 1) { delete root; root = nullptr; count = 0; return; }
        vector<MedicineNode*> path = getPath(count);
        MedicineNode *last = path.back();
        MedicineNode *parent = path[path.size() - 2];
        swapData(root, last);
        if (parent->right == last) parent->right = nullptr;
        else parent->left = nullptr;
        delete last;
        count--;
        heapifyDown();
    }

    void levelOrder() {
        if (!root) { cout << "No medicines in stock!\n"; return; }
        queue<MedicineNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            cout << "Level " << level++ << ": ";
            while (sz--) {
                MedicineNode *n = q.front(); q.pop();
                cout << "[" << n->name << ", ID " << n->medicineID << ", " << formatDate(n->expiry) << "]  ";
                if (n->left) q.push(n->left);
                if (n->right) q.push(n->right);
            }
            cout << endl;
        }
    }
};

int main() {
    MinHeap store;
    cout << "===== Medicine Expiry Management (Min Heap) =====\n\n--- Inserting Medicines ---\n";
    store.insert("Paracetamol", 401, 20271015);
    store.insert("Amoxicillin", 402, 20270520);
    store.insert("Ibuprofen", 403, 20280610);
    store.insert("Cetirizine", 404, 20270105);
    store.insert("Aspirin", 405, 20270210);
    store.insert("Omeprazole", 406, 20271230);
    store.insert("Insulin", 407, 20270115);

    cout << "\n--- Min Heap (Level Order Traversal) ---\n";
    store.levelOrder();

    cout << "\n--- Medicine To Check First ---\n";
    store.showNearestExpiry();

    store.deleteNearestExpiry();

    cout << "\n--- Updated Heap after Deletion (Level Order Traversal) ---\n";
    store.levelOrder();

    cout << "\n--- Next Nearest Expiry ---\n";
    store.showNearestExpiry();
    return 0;
}
