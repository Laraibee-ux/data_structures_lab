#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string song;
    Node* next;

    Node(string name) {
        song = name;
        next = NULL;
    }
};

class Playlist {
private:
    Node* head;
    Node* tail;
    int count;

public:
    Playlist() {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    void addSong(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;          // circular, no NULL at the end
        }
        count++;
    }

    // Display all songs once
    void displayAll() {
        cout << "Playlist:" << endl;
        Node* temp = head;
        do {
            cout << temp->song << endl;
            temp = temp->next;
        } while (temp != head);
    }

    // Play playlist for given number of rounds
    void play(int rounds) {
        Node* temp = head;
        for (int r = 1; r <= rounds; r++) {
            cout << "--- Round " << r << " ---" << endl;
            for (int i = 0; i < count; i++) {
                cout << "Playing: " << temp->song << endl;
                temp = temp->next;      // after last song, goes to first automatically
            }
        }
    }
};

int main() {
    Playlist playlist;

    playlist.addSong("Song 1 - Tum Hi Ho");
    playlist.addSong("Song 2 - Kun Faya Kun");
    playlist.addSong("Song 3 - Pasoori");
    playlist.addSong("Song 4 - Dil Dil Pakistan");
    playlist.addSong("Song 5 - Afreen Afreen");

    playlist.displayAll();
    cout << endl;
    playlist.play(2);

    return 0;
}
