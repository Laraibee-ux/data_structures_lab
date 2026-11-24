// Lab 09 - Task 2: Hospital Emergency Management System (Max Heap)
#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

class PatientNode {
public:
    string name;
    int patientID;
    int priority;          // higher number = more critical
    PatientNode *left, *right;
    PatientNode(string n, int id, int p)
        : name(n), patientID(id), priority(p), left(nullptr), right(nullptr) {}
};

class EmergencyHeap {
private:
    PatientNode *root;
    int count;

    vector<PatientNode*> getPath(int pos) {
        vector<PatientNode*> path;
        int highest = 1;
        while (highest * 2 <= pos) highest *= 2;
        PatientNode *cur = root;
        path.push_back(cur);
        for (int bit = highest / 2; bit >= 1; bit /= 2) {
            cur = (pos & bit) ? cur->right : cur->left;
            path.push_back(cur);
        }
        return path;
    }

    void swapData(PatientNode *a, PatientNode *b) {
        swap(a->name, b->name);
        swap(a->patientID, b->patientID);
        swap(a->priority, b->priority);
    }

    void heapifyUp() {
        vector<PatientNode*> path = getPath(count);
        for (int i = path.size() - 1; i > 0; i--) {
            if (path[i]->priority > path[i - 1]->priority) {
                cout << "   Heapify Up: swap " << path[i]->name << " (P" << path[i]->priority
                     << ") with parent " << path[i - 1]->name << " (P" << path[i - 1]->priority << ")\n";
                swapData(path[i], path[i - 1]);
            } else break;
        }
    }

    void heapifyDown() {
        PatientNode *cur = root;
        while (cur && cur->left) {
            PatientNode *big = cur->left;
            if (cur->right && cur->right->priority > big->priority) big = cur->right;
            if (big->priority > cur->priority) {
                cout << "   Heapify Down: swap " << cur->name << " (P" << cur->priority
                     << ") with child " << big->name << " (P" << big->priority << ")\n";
                swapData(cur, big);
                cur = big;
            } else break;
        }
    }

    void destroy(PatientNode *n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    EmergencyHeap() : root(nullptr), count(0) {}
    ~EmergencyHeap() { destroy(root); }

    void insert(string name, int id, int priority) {
        PatientNode *node = new PatientNode(name, id, priority);
        count++;
        if (count == 1) root = node;
        else {
            PatientNode *parent = getPath(count / 2).back();
            if (count % 2 == 0) parent->left = node;
            else parent->right = node;
        }
        cout << "Admitted: " << name << " | ID " << id << " | Priority " << priority << endl;
        heapifyUp();
    }

    void showHighestPriority() {
        if (!root) { cout << "No patients waiting!\n"; return; }
        cout << "Highest priority patient: " << root->name << " | ID " << root->patientID
             << " | Priority " << root->priority << endl;
    }

    void treatPatient() {
        if (!root) { cout << "No patients waiting!\n"; return; }
        cout << "\nTreating patient: " << root->name << " | ID " << root->patientID
             << " | Priority " << root->priority << "  -> removed from heap\n";
        if (count == 1) { delete root; root = nullptr; count = 0; return; }
        vector<PatientNode*> path = getPath(count);
        PatientNode *last = path.back();
        PatientNode *parent = path[path.size() - 2];
        swapData(root, last);
        if (parent->right == last) parent->right = nullptr;
        else parent->left = nullptr;
        delete last;
        count--;
        heapifyDown();
    }

    void levelOrder() {
        if (!root) { cout << "No patients waiting!\n"; return; }
        queue<PatientNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            cout << "Level " << level++ << ": ";
            while (sz--) {
                PatientNode *n = q.front(); q.pop();
                cout << "[" << n->name << ", ID " << n->patientID << ", P" << n->priority << "]  ";
                if (n->left) q.push(n->left);
                if (n->right) q.push(n->right);
            }
            cout << endl;
        }
    }
};

int main() {
    EmergencyHeap er;
    cout << "===== Hospital Emergency Management (Max Heap) =====\n\n--- Admitting Patients ---\n";
    er.insert("Bilal", 201, 4);
    er.insert("Zainab", 202, 9);
    er.insert("Imran", 203, 6);
    er.insert("Hina", 204, 3);
    er.insert("Kamran", 205, 10);
    er.insert("Noor", 206, 7);
    er.insert("Tariq", 207, 5);

    cout << "\n--- All Patients (Level Order Traversal) ---\n";
    er.levelOrder();

    cout << "\n--- Most Critical Patient ---\n";
    er.showHighestPriority();

    er.treatPatient();

    cout << "\n--- Heap after Treatment (Level Order Traversal) ---\n";
    er.levelOrder();

    cout << "\n--- Next Patient Who Needs Treatment ---\n";
    er.showHighestPriority();
    return 0;
}
