#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string website;
    Node* prev;
    Node* next;

    Node(string site) {
        website = site;
        prev = NULL;
        next = NULL;
    }
};

class BrowserHistory {
private:
    Node* head;
    Node* tail;

public:
    BrowserHistory() {
        head = NULL;
        tail = NULL;
    }

    // Add a website at the end
    void visit(string site) {
        Node* newNode = new Node(site);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // First visited -> Last visited
    void displayForward() {
        cout << "History (First -> Last):" << endl;
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->website << endl;
            temp = temp->next;
        }
    }

    // Last visited -> First visited
    void displayBackward() {
        cout << "History (Last -> First):" << endl;
        Node* temp = tail;
        while (temp != NULL) {
            cout << temp->website << endl;
            temp = temp->prev;
        }
    }
};

int main() {
    BrowserHistory history;

    history.visit("google.com");
    history.visit("youtube.com");
    history.visit("github.com");
    history.visit("stackoverflow.com");
    history.visit("wikipedia.org");

    history.displayForward();
    cout << endl;
    history.displayBackward();

    return 0;
}
