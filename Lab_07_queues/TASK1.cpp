// Task 1: Bank Customer Service System - Simple (Linear) Queue using array
#include <iostream>
using namespace std;

#define SIZE 5

class BankQueue {
    int arr[SIZE];
    int front, rear;
public:
    BankQueue() { front = -1; rear = -1; }

    bool isEmpty() { return front == -1 || front > rear; }
    bool isFull()  { return rear == SIZE - 1; }

    void enqueue(int token) {
        if (isFull()) {
            cout << "Overflow! Queue is full. Token " << token << " cannot be added.\n";
            return;
        }
        if (front == -1) front = 0;
        arr[++rear] = token;
        cout << "Customer " << token << " added to the queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Underflow! No customers waiting.\n";
            return;
        }
        cout << "Serving customer " << arr[front] << ".\n";
        front++;
    }

    int count() { return isEmpty() ? 0 : rear - front + 1; }

    void display() {
        if (isEmpty()) {
            cout << "No customers waiting.\n";
            return;
        }
        cout << "Waiting customers (front -> rear): ";
        for (int i = front; i <= rear; i++) cout << arr[i] << " ";
        cout << "\n";
    }
};

int main() {
    BankQueue q;
    int choice, token;
    do {
        cout << "\n--- Bank Customer Service System ---\n"
             << "1. Enqueue (customer arrives)\n"
             << "2. Dequeue (serve next customer)\n"
             << "3. Display waiting customers\n"
             << "4. Number of waiting customers\n"
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Enter token number: "; cin >> token; q.enqueue(token); break;
            case 2: q.dequeue(); break;
            case 3: q.display(); break;
            case 4: cout << "Number of waiting customers: " << q.count() << "\n"; break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
    return 0;
}
