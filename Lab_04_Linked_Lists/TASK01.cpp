#include <iostream>
using namespace std;

class Node {
public:
    int rollNo;
    Node* next;

    Node(int r) {
        rollNo = r;
        next = NULL;
    }
};

class StudentList {
private:
    Node* head;

public:
    StudentList() {
        head = NULL;
    }

    // Add a new student at the end of the list
    void addStudent(int rollNo) {
        Node* newNode = new Node(rollNo);
        if (head == NULL) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Display all registered students
    void display() {
        cout << "Registered Students:" << endl;
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->rollNo;
            if (temp->next != NULL) {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    // Search a student using Roll Number
    void search(int rollNo) {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->rollNo == rollNo) {
                cout << "Student Found" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Student Not Found" << endl;
    }
};

int main() {
    StudentList list;

    list.addStudent(101);
    list.addStudent(105);
    list.addStudent(108);
    list.addStudent(112);

    list.display();

    int rollNo;
    cout << "Enter Roll Number to Search: ";
    cin >> rollNo;
    list.search(rollNo);

    return 0;
}
