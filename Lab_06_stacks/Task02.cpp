// Lab 06 - Task 2: Undo Operation in a Text Editor (Array Stack)
#include <iostream>
#include <string>
using namespace std;

class ArrayStack {
private:
    string* arr;
    int capacity;
    int top;
public:
    ArrayStack(int size = 10) {
        capacity = size;
        arr = new string[capacity];
        top = -1;
    }
    ~ArrayStack() { delete[] arr; }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == capacity - 1; }

    void push(const string& action) {
        if (isFull()) { cout << "Stack Overflow!\n"; return; }
        arr[++top] = action;
    }
    string pop() {
        if (isEmpty()) { cout << "Stack Underflow!\n"; return ""; }
        return arr[top--];
    }
    string peek() const {
        if (isEmpty()) return "";
        return arr[top];
    }
    void display() const {
        if (isEmpty()) { cout << "(No actions)\n"; return; }
        for (int i = top; i >= 0; i--) {
            cout << arr[i];
            if (i == top) cout << "   <-- TOP";
            cout << endl;
        }
    }
};

int main() {
    ArrayStack actions(10);

    actions.push("Type \"Hello\"");
    actions.push("Type \"World\"");
    actions.push("Add \"!\"");
    actions.push("Delete \"!\"");

    cout << "All actions (TOP to bottom):\n";
    actions.display();

    cout << "\nPerforming Undo (POP) twice...\n";
    cout << "Undone: " << actions.pop() << endl;
    cout << "Undone: " << actions.pop() << endl;

    cout << "\nCurrent TOP action: " << actions.peek() << endl;

    cout << "\nRemaining actions:\n";
    actions.display();

    return 0;
}
