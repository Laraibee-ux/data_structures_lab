#include <iostream>
using namespace std;
int main()
{
    int marks[6][4] = {
        {80, 75, 90, 85},
        {60, 65, 70, 72},
        {95, 88, 92, 90},
        {55, 60, 58, 62},
        {70, 72, 75, 78},
        {85, 90, 88, 92}
    };
    string subjects[4] = {"English", "Mathematics", "Programming", "AI"};
    cout << "Marks Table:\n";
    cout << "Student\t";
    for (int j = 0; j < 4; j++)
        cout << subjects[j] << "\t";
    cout << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << "S" << (i + 1) << "\t";
        for (int j = 0; j < 4; j++)
            cout << marks[i][j] << "\t";
        cout << endl;
    }
    int total[6];
    float average[6];
    cout << "Total and Average Marks of Each Student:\n";
    for (int i = 0; i < 6; i++)
    {
        total[i] = 0;
        for (int j = 0; j < 4; j++)
            total[i] += marks[i][j];
        average[i] = total[i] / 4.0;
        cout << "S" << (i + 1) << " -> Total: " << total[i] << "\tAverage: " << average[i] << endl;
    }
    cout << "Highest Marks in Each Subject:\n";
    for (int j = 0; j < 4; j++)
    {
        int highest = marks[0][j];
        for (int i = 1; i < 6; i++)
            if (marks[i][j] > highest)
                highest = marks[i][j];
        cout << subjects[j] << ": " << highest << endl;
    }
    int maxIndex = 0;
    for (int i = 1; i < 6; i++)
        if (total[i] > total[maxIndex])
            maxIndex = i;
    cout << "Student with Highest Total Marks: S" << (maxIndex + 1) << " with " << total[maxIndex] << " marks" << endl;
    return 0;
}
