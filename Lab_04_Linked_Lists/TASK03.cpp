#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string productId;
    Node* next;

    Node(string id) {
        productId = id;
        next = NULL;
    }
};

class ShoppingCart {
private:
    Node* head;

public:
    ShoppingCart() {
        head = NULL;
    }

    // Add a product to the cart
    void addProduct(string id) {
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

    // Display all products in the cart
    void display() {
        Node* temp = head;
        if (temp == NULL) {
            cout << "Cart is empty." << endl;
            return;
        }
        while (temp != NULL) {
            cout << temp->productId;
            if (temp->next != NULL) {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    // Remove a product using its Product ID
    void removeProduct(string id) {
        if (head == NULL) {
            cout << "Cart is empty." << endl;
            return;
        }

        // If the product is the first node
        if (head->productId == id) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Search for the product in the rest of the list
        Node* current = head;
        while (current->next != NULL && current->next->productId != id) {
            current = current->next;
        }

        if (current->next == NULL) {
            cout << "Product " << id << " not found in cart." << endl;
        } else {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }
};

int main() {
    ShoppingCart cart;

    cart.addProduct("P101");
    cart.addProduct("P205");
    cart.addProduct("P310");
    cart.addProduct("P415");

    cout << "Shopping Cart:" << endl;
    cart.display();
    cout << endl;

    string id;
    cout << "Remove Product: ";
    cin >> id;
    cart.removeProduct(id);
    cout << endl;

    cout << "Updated Cart:" << endl;
    cart.display();

    return 0;
}
