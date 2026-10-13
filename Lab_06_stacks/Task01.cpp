// Lab 06 - Task 1: Browser Back History (Array Stack)
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

    void push(const string& page) {
        if (isFull()) { cout << "Stack Overflow!\n"; return; }
        arr[++top] = page;
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
        if (isEmpty()) { cout << "(No history)\n"; return; }
        for (int i = top; i >= 0; i--) {
            cout << arr[i];
            if (i == top) cout << "   <-- TOP";
            cout << endl;
        }
    }
};

int main() {
    ArrayStack history(10);

    history.push("Google");
    history.push("YouTube");
    history.push("Facebook");
    history.push("GitHub");

    cout << "Browsing history (TOP to bottom):\n";
    history.display();

    cout << "\nPressing Back button (POP)...\n";
    cout << "Removed page: " << history.pop() << endl;

    cout << "\nCurrent TOP page: " << history.peek() << endl;

    cout << "\nRemaining browsing history:\n";
    history.display();

    return 0;
}
