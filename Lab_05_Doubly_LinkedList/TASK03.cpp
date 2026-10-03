#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string player;
    Node* next;

    Node(string name) {
        player = name;
        next = NULL;
    }
};

class Game {
private:
    Node* head;
    Node* tail;

public:
    Game() {
        head = NULL;
        tail = NULL;
    }

    void addPlayer(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
            tail->next = head;          // points to itself
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;          // last node connects back to first
        }
    }

    // Each player's turn once
    void displayTurns() {
        cout << "Player Turns:" << endl;
        Node* temp = head;
        int turn = 1;
        do {
            cout << "Turn " << turn << ": " << temp->player << endl;
            temp = temp->next;
            turn++;
        } while (temp != head);
    }

    // Show that after the last player, turn returns to the first
    void showCircular() {
        cout << "After last player (" << tail->player
             << "), next turn goes to: " << tail->next->player << endl;
    }
};

int main() {
    Game game;

    game.addPlayer("Ali");
    game.addPlayer("Sara");
    game.addPlayer("Ahmed");
    game.addPlayer("Fatima");
    game.addPlayer("Hassan");

    game.displayTurns();
    cout << endl;
    game.showCircular();

    return 0;
}
