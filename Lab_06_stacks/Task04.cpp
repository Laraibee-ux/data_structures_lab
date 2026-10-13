// Lab 06 - Task 4: Restaurant Order Processing (Linked List Stack)
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;
    Node(const string& val) : data(val), next(nullptr) {}
};

class LinkedStack {
private:
    Node* top;
public:
    LinkedStack() : top(nullptr) {}
    ~LinkedStack() {
        while (!isEmpty()) pop();
    }

    bool isEmpty() const { return top == nullptr; }

    void push(const string& id) {
        Node* newNode = new Node(id);
        newNode->next = top;
        top = newNode;
    }
    string pop() {
        if (isEmpty()) { cout << "Stack Underflow!\n"; return ""; }
        Node* temp = top;
        string val = temp->data;
        top = top->next;
        delete temp;
        return val;
    }
    string peek() const {
        if (isEmpty()) return "";
        return top->data;
    }
    void display() const {
        if (isEmpty()) { cout << "(No orders)\n"; return; }
        Node* curr = top;
        while (curr != nullptr) {
            cout << curr->data;
            if (curr == top) cout << "   <-- TOP";
            cout << endl;
            curr = curr->next;
        }
    }
};

int main() {
    LinkedStack orders;

    orders.push("ORD-101");
    orders.push("ORD-102");
    orders.push("ORD-103");
    orders.push("ORD-104");

    cout << "All orders (TOP to bottom):\n";
    orders.display();

    cout << "\nProcessing two orders (POP x2)...\n";
    cout << "Processed: " << orders.pop() << endl;
    cout << "Processed: " << orders.pop() << endl;

    cout << "\nCurrent TOP order: " << orders.peek() << endl;

    cout << "\nRemaining orders:\n";
    orders.display();

    cout << "\nIs the stack empty? " << (orders.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
