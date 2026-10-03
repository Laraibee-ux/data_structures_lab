#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string image;
    Node* prev;
    Node* next;

    Node(string name) {
        image = name;
        prev = NULL;
        next = NULL;
    }
};

class ImageGallery {
private:
    Node* head;
    Node* tail;

public:
    ImageGallery() {
        head = NULL;
        tail = NULL;
    }

    void addImage(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // First -> Last using next
    void displayForward() {
        cout << "Gallery (First -> Last):" << endl;
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->image << endl;
            temp = temp->next;
        }
    }

    // Last -> First using prev
    void displayBackward() {
        cout << "Gallery (Last -> First):" << endl;
        Node* temp = tail;
        while (temp != NULL) {
            cout << temp->image << endl;
            temp = temp->prev;
        }
    }

    // Show movement in both directions using prev and next
    void demonstrateNavigation() {
        cout << "Navigation Demo:" << endl;
        Node* current = head->next->next;   // go to 3rd image
        cout << "Current image : " << current->image << endl;

        current = current->next;            // move forward
        cout << "Moved NEXT    : " << current->image << endl;

        current = current->prev;            // move back
        cout << "Moved PREV    : " << current->image << endl;

        current = current->prev;            // move back again
        cout << "Moved PREV    : " << current->image << endl;
    }
};

int main() {
    ImageGallery gallery;

    gallery.addImage("sunset.jpg");
    gallery.addImage("mountain.png");
    gallery.addImage("beach.jpg");
    gallery.addImage("city.png");
    gallery.addImage("forest.jpg");

    gallery.displayForward();
    cout << endl;
    gallery.displayBackward();
    cout << endl;
    gallery.demonstrateNavigation();

    return 0;
}
