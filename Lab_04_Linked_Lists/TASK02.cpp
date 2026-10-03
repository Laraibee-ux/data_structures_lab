#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string patientId;
    Node* next;

    Node(string id) {
        patientId = id;
        next = NULL;
    }
};

class PatientQueue {
private:
    Node* head;

public:
    PatientQueue() {
        head = NULL;
    }

    // Add a new patient at the end of the list
    void addPatient(string id) {
        Node* newNode = new Node(id);
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

    // Display all patients waiting
    void display() {
        Node* temp = head;
        if (temp == NULL) {
            cout << "No patients waiting." << endl;
            return;
        }
        while (temp != NULL) {
            cout << temp->patientId;
            if (temp->next != NULL) {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    // Remove the first patient (doctor attends the patient)
    void servePatient() {
        if (head == NULL) {
            cout << "No patients to serve." << endl;
            return;
        }
        Node* temp = head;
        cout << "Patient " << temp->patientId << " is being served." << endl;
        head = head->next;
        delete temp;
    }
};

int main() {
    PatientQueue queue;

    queue.addPatient("P101");
    queue.addPatient("P102");
    queue.addPatient("P103");
    queue.addPatient("P104");

    cout << "Waiting Patients:" << endl;
    queue.display();
    cout << endl;

    queue.servePatient();
    cout << endl;

    cout << "Updated Queue:" << endl;
    queue.display();

    return 0;
}
