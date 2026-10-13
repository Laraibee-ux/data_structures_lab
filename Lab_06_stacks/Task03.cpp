// Lab 06 - Task 3: Hospital Patient Emergency Requests (Linked List Stack)
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
        if (isEmpty()) { cout << "(No requests)\n"; return; }
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
    LinkedStack requests;

    requests.push("P101");
    requests.push("P102");
    requests.push("P103");
    requests.push("P104");

    cout << "Emergency requests (TOP to bottom):\n";
    requests.display();

    cout << "\nHandling latest request (POP)...\n";
    cout << "Handled: " << requests.pop() << endl;

    cout << "\nNew TOP request: " << requests.peek() << endl;

    cout << "\nRemaining requests:\n";
    requests.display();

    return 0;
}
