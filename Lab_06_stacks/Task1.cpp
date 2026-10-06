#include <iostream>
using namespace std;

int main() {
    int n;
    long long fact = 1;

    cout << "Enter a number: ";
    cin >> n;

    if (n < 0) {
        cout << "Factorial negative number ka nahi hota." << endl;
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        fact *= i;
    }

    cout << "Factorial of " << n << " = " << fact << endl;
    return 0;
}
