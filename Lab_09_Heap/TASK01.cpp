// Lab 09 - Task 1: University Student Merit Ranking (Max Heap)
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

class StudentNode {
public:
    string name;
    int rollNo;
    float marks;
    StudentNode *left, *right;
    StudentNode(string n, int r, float m)
        : name(n), rollNo(r), marks(m), left(nullptr), right(nullptr) {}
};

class MaxHeap {
private:
    StudentNode *root;
    int count;

    // Returns the path (root -> node) of the node at position 'pos' (1-indexed, level order)
    vector<StudentNode*> getPath(int pos) {
        vector<StudentNode*> path;
        int highest = 1;
        while (highest * 2 <= pos) highest *= 2;
        StudentNode *cur = root;
        path.push_back(cur);
        for (int bit = highest / 2; bit >= 1; bit /= 2) {
            cur = (pos & bit) ? cur->right : cur->left;
            path.push_back(cur);
        }
        return path;
    }

    void swapData(StudentNode *a, StudentNode *b) {
        swap(a->name, b->name);
        swap(a->rollNo, b->rollNo);
        swap(a->marks, b->marks);
    }

    void heapifyUp() {
        vector<StudentNode*> path = getPath(count);
        for (int i = path.size() - 1; i > 0; i--) {
            if (path[i]->marks > path[i - 1]->marks) {
                cout << "   Heapify Up: swap " << path[i]->name << " (" << path[i]->marks
                     << ") with parent " << path[i - 1]->name << " (" << path[i - 1]->marks << ")\n";
                swapData(path[i], path[i - 1]);
            } else break;
        }
    }

    void heapifyDown() {
        StudentNode *cur = root;
        while (cur && cur->left) {
            StudentNode *big = cur->left;
            if (cur->right && cur->right->marks > big->marks) big = cur->right;
            if (big->marks > cur->marks) {
                cout << "   Heapify Down: swap " << cur->name << " (" << cur->marks
                     << ") with child " << big->name << " (" << big->marks << ")\n";
                swapData(cur, big);
                cur = big;
            } else break;
        }
    }

    void destroy(StudentNode *n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    MaxHeap() : root(nullptr), count(0) {}
    ~MaxHeap() { destroy(root); }

    void insert(string name, int roll, float marks) {
        StudentNode *node = new StudentNode(name, roll, marks);
        count++;
        if (count == 1) root = node;
        else {
            StudentNode *parent = getPath(count / 2).back();
            if (count % 2 == 0) parent->left = node;
            else parent->right = node;
        }
        cout << "Inserted: " << name << " | Roll " << roll << " | Marks " << marks << endl;
        heapifyUp();
    }

    void deleteRoot() {
        if (!root) { cout << "Heap is empty!\n"; return; }
        cout << "\nDeleting student with highest marks: " << root->name
             << " | Roll " << root->rollNo << " | Marks " << root->marks << endl;
        if (count == 1) { delete root; root = nullptr; count = 0; return; }
        vector<StudentNode*> path = getPath(count);
        StudentNode *last = path.back();
        StudentNode *parent = path[path.size() - 2];
        swapData(root, last);                       // move last node data to root
        if (parent->right == last) parent->right = nullptr;
        else parent->left = nullptr;
        delete last;                                // remove old root data
        count--;
        heapifyDown();
    }

    void levelOrder() {
        if (!root) { cout << "Heap is empty!\n"; return; }
        queue<StudentNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            cout << "Level " << level++ << ": ";
            while (sz--) {
                StudentNode *n = q.front(); q.pop();
                cout << "[" << n->name << ", Roll " << n->rollNo << ", " << n->marks << "]  ";
                if (n->left) q.push(n->left);
                if (n->right) q.push(n->right);
            }
            cout << endl;
        }
    }
};

int main() {
    MaxHeap merit;
    cout << fixed << setprecision(1);
    cout << "===== Student Merit Ranking (Max Heap) =====\n\n--- Insertions ---\n";
    merit.insert("Ali", 101, 78.5);
    merit.insert("Sara", 102, 91.0);
    merit.insert("Ahmed", 103, 85.0);
    merit.insert("Fatima", 104, 67.5);
    merit.insert("Hassan", 105, 95.5);
    merit.insert("Ayesha", 106, 88.0);
    merit.insert("Usman", 107, 72.0);

    cout << "\n--- Heap (Level Order Traversal) ---\n";
    merit.levelOrder();

    merit.deleteRoot();

    cout << "\n--- Updated Heap after Deletion (Level Order Traversal) ---\n";
    merit.levelOrder();
    return 0;
}
