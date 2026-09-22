#include <iostream>
using namespace std;
int main()
{
    int parking[4][5] = {
        {1, 0, 1, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1}
    };
    cout << "Parking Layout (0 = Empty, 1 = Occupied):\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << parking[i][j] << "\t";
        cout << endl;
    }
    int occupied = 0, empty = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
            if (parking[i][j] == 1)
                occupied++;
            else
                empty++;
    cout << "Total Occupied Spaces: " << occupied << endl;
    cout << "Total Empty Spaces: " << empty << endl;
    int row, col;
    cout << "Enter row number (0-3): ";
    cin >> row;
    cout << "Enter column number (0-4): ";
    cin >> col;
    if (row >= 0 && row < 4 && col >= 0 && col < 5)
    {
        if (parking[row][col] == 0)
            cout << "Selected space is Available.\n";
        else
            cout << "Selected space is Occupied.\n";
    }
    else
    {
        cout << "Invalid row or column entered.\n";
    }
    int capacity = 4 * 5;
    cout << "Total Parking Capacity: " << capacity << endl;
    cout << "Current Occupancy: " << occupied << endl;
    return 0;
}
