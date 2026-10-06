#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int id;
    float gpa;

public:
    // Constructor
    Student(string n, int i, float g) {
        name = n;
        id = i;
        gpa = g;
    }

    void display() {
        cout << "Name: " << name << endl;
        cout << "ID  : " << id << endl;
        cout << "GPA : " << gpa << endl;
    }
};

int main() {
    Student s1("Ali", 101, 3.5);
    Student s2("Sara", 102, 3.8);

    cout << "--- Student 1 ---" << endl;
    s1.display();

    cout << "\n--- Student 2 ---" << endl;
    s2.display();

    return 0;
}
