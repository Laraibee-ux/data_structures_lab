// Lab 09 - Task 3: Online Shopping Order Sorting (Heap Sort)
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

class OrderNode {
public:
    int orderID;
    string customer;
    double amount;
    OrderNode *left, *right;
    OrderNode(int id, string c, double a)
        : orderID(id), customer(c), amount(a), left(nullptr), right(nullptr) {}
};

class OrderHeap {
private:
    OrderNode *root;
    int count;

    vector<OrderNode*> getPath(int pos) {
        vector<OrderNode*> path;
        int highest = 1;
        while (highest * 2 <= pos) highest *= 2;
        OrderNode *cur = root;
        path.push_back(cur);
        for (int bit = highest / 2; bit >= 1; bit /= 2) {
            cur = (pos & bit) ? cur->right : cur->left;
            path.push_back(cur);
        }
        return path;
    }

    void swapData(OrderNode *a, OrderNode *b) {
        swap(a->orderID, b->orderID);
        swap(a->customer, b->customer);
        swap(a->amount, b->amount);
    }

    void heapifyUp() {
        vector<OrderNode*> path = getPath(count);
        for (int i = path.size() - 1; i > 0; i--) {
            if (path[i]->amount > path[i - 1]->amount) {
                cout << "   Heapify Up: swap " << path[i]->amount << " with parent "
                     << path[i - 1]->amount << endl;
                swapData(path[i], path[i - 1]);
            } else break;
        }
    }

    void heapifyDown() {
        OrderNode *cur = root;
        while (cur && cur->left) {
            OrderNode *big = cur->left;
            if (cur->right && cur->right->amount > big->amount) big = cur->right;
            if (big->amount > cur->amount) {
                swapData(cur, big);
                cur = big;
            } else break;
        }
    }

    void destroy(OrderNode *n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

public:
    OrderHeap() : root(nullptr), count(0) {}
    ~OrderHeap() { destroy(root); }

    int size() { return count; }

    void insert(int id, string customer, double amount) {
        OrderNode *node = new OrderNode(id, customer, amount);
        count++;
        if (count == 1) root = node;
        else {
            OrderNode *parent = getPath(count / 2).back();
            if (count % 2 == 0) parent->left = node;
            else parent->right = node;
        }
        cout << "Inserted: Order " << id << " | " << customer << " | Rs. " << amount << endl;
        heapifyUp();
    }

    // Removes the root (largest amount) and returns its data
    OrderNode extractMax() {
        OrderNode result(root->orderID, root->customer, root->amount);
        if (count == 1) { delete root; root = nullptr; count = 0; return result; }
        vector<OrderNode*> path = getPath(count);
        OrderNode *last = path.back();
        OrderNode *parent = path[path.size() - 2];
        swapData(root, last);
        if (parent->right == last) parent->right = nullptr;
        else parent->left = nullptr;
        delete last;
        count--;
        heapifyDown();
        return result;
    }

    void levelOrder() {
        if (!root) { cout << "Heap is empty!\n"; return; }
        queue<OrderNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            cout << "Level " << level++ << ": ";
            while (sz--) {
                OrderNode *n = q.front(); q.pop();
                cout << "[Order " << n->orderID << ", Rs. " << n->amount << "]  ";
                if (n->left) q.push(n->left);
                if (n->right) q.push(n->right);
            }
            cout << endl;
        }
    }
};

int main() {
    OrderHeap heap;
    cout << fixed << setprecision(2);
    cout << "===== Online Orders - Heap Sort =====\n\n--- Inserting Orders into Max Heap ---\n";
    heap.insert(301, "Ali", 4500.00);
    heap.insert(302, "Sara", 1200.50);
    heap.insert(303, "Ahmed", 8900.00);
    heap.insert(304, "Fatima", 2300.75);
    heap.insert(305, "Hassan", 15000.00);
    heap.insert(306, "Ayesha", 670.25);
    heap.insert(307, "Usman", 3200.00);

    cout << "\n--- Max Heap (Level Order Traversal) ---\n";
    heap.levelOrder();

    // Heap Sort: repeated root deletion. Each deleted root is the current maximum,
    // so values are stored from the END of the array towards the front.
    int n = heap.size();
    vector<double> sortedAmounts(n);
    vector<OrderNode> sortedOrders(n, OrderNode(0, "", 0));
    for (int i = n - 1; i >= 0; i--) {
        OrderNode top = heap.extractMax();
        sortedAmounts[i] = top.amount;
        sortedOrders[i] = top;
    }

    cout << "\n--- Order Amounts in Ascending Order (Smallest to Largest) ---\n";
    for (int i = 0; i < n; i++) cout << "Rs. " << sortedAmounts[i] << (i < n - 1 ? "  <  " : "\n");

    cout << "\n--- Sorted Sales Report ---\n";
    cout << left << setw(6) << "No." << setw(12) << "Order ID" << setw(14) << "Customer"
         << "Amount (Rs.)\n";
    for (int i = 0; i < n; i++)
        cout << left << setw(6) << i + 1 << setw(12) << sortedOrders[i].orderID
             << setw(14) << sortedOrders[i].customer << sortedOrders[i].amount << endl;
    return 0;
}
