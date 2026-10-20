// Task 2: Network Data Packet Management - Circular Queue using array and modulo
#include <iostream>
using namespace std;

#define SIZE 5

class PacketQueue {
    int arr[SIZE];
    int front, rear, count;
public:
    PacketQueue() { front = 0; rear = -1; count = 0; }

    bool isEmpty() { return count == 0; }
    bool isFull()  { return count == SIZE; }

    void enqueue(int id) {
        if (isFull()) {
            cout << "Queue is FULL! Packet " << id << " dropped.\n";
            return;
        }
        rear = (rear + 1) % SIZE;
        arr[rear] = id;
        count++;
        cout << "Packet " << id << " stored at index " << rear << ".\n";
    }

    void transmit() {
        if (isEmpty()) {
            cout << "Queue is EMPTY! No packet to transmit.\n";
            return;
        }
        cout << "Transmitting packet " << arr[front] << " (index " << front << " is now free).\n";
        front = (front + 1) % SIZE;
        count--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No packets waiting.\n";
            return;
        }
        cout << "Packets waiting (front -> rear): ";
        for (int i = 0, idx = front; i < count; i++, idx = (idx + 1) % SIZE)
            cout << arr[idx] << "(idx " << idx << ") ";
        cout << "\n";
    }
};

int main() {
    PacketQueue q;
    int choice, id;
    do {
        cout << "\n--- Network Packet Buffer (Circular Queue) ---\n"
             << "1. Insert packet\n"
             << "2. Transmit oldest packet\n"
             << "3. Display waiting packets\n"
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Enter packet ID: "; cin >> id; q.enqueue(id); break;
            case 2: q.transmit(); break;
            case 3: q.display(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
    return 0;
}
