// Task 3: Hospital Emergency Department - Priority Queue using array
// Priority rule: SMALLER number = HIGHER urgency (1 is treated first).
// Patients with equal priority are treated in arrival order (FIFO).
#include <iostream>
#include <string>
using namespace std;

#define SIZE 10

struct Patient {
    string id;
    int priority;
};

class EmergencyQueue {
    Patient arr[SIZE];
    int n;
public:
    EmergencyQueue() { n = 0; }

    bool isEmpty() { return n == 0; }
    bool isFull()  { return n == SIZE; }

    // Insert keeping array sorted: highest urgency (lowest number) at index 0
    void enqueue(string id, int priority) {
        if (isFull()) {
            cout << "Queue is FULL! Cannot add patient " << id << ".\n";
            return;
        }
        int i = n - 1;
        while (i >= 0 && arr[i].priority > priority) {   // '>' keeps FIFO for equal priority
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = {id, priority};
        n++;
        cout << "Patient " << id << " added with priority " << priority << ".\n";
    }

    void treat() {
        if (isEmpty()) {
            cout << "Queue is EMPTY! No patients waiting.\n";
            return;
        }
        cout << "Treating patient " << arr[0].id << " (priority " << arr[0].priority << ").\n";
        for (int i = 1; i < n; i++) arr[i - 1] = arr[i];
        n--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No patients waiting.\n";
            return;
        }
        cout << "Waiting patients (highest urgency first):\n";
        for (int i = 0; i < n; i++)
            cout << "  " << arr[i].id << "  -> Priority " << arr[i].priority << "\n";
    }
};

int main() {
    EmergencyQueue q;
    int choice, priority;
    string id;
    do {
        cout << "\n--- Hospital Emergency Department ---\n"
             << "1. Add patient\n"
             << "2. Treat highest-priority patient\n"
             << "3. Display waiting patients\n"
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter patient ID: "; cin >> id;
                cout << "Enter priority (1 = highest): "; cin >> priority;
                q.enqueue(id, priority);
                break;
            case 2: q.treat(); break;
            case 3: q.display(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
    return 0;
}
