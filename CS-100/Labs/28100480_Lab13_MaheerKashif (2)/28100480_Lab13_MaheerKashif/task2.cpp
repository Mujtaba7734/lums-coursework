#include <iostream>
using namespace std;

int main()
{
    int matrix[3][3];
    cout << "Enter the elements of a 3x3 matrix" << endl;
    for (int i =0; i < 9; i++)
    {
        int value;
        cin >> *(*matrix +i);
    }

    cout << "Orignal Matrix: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j= 0; j < 3; j++)
        {
            cout << *(*(matrix + i) + j) << " ";
        }
        cout << endl;
    }
    cout << "Matrix after sorting columns in decending order" << endl;
    for (int i = 2; i > -1; i--)
    {
        for (int j= 0; j < 3; j++)
        {
            cout << *(*(matrix + i) + j) << " ";
        }
        cout << endl;
    }
    return 0;
}   