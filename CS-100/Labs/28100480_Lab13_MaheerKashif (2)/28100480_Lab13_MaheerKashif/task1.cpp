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

    cout << "The 3x3 matrix is: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j= 0; j < 3; j++)
        {
            cout << *(*(matrix + i) + j) << " ";
        }
        cout << endl;
    }
    int total;
    for (int i = 0; i < 3; i++ )
    {
        total =0;
        for (int j= 0; j < 3; j++)
        {
            total += *(*(matrix +i) +j);
        }
        cout << "Sum of row " << i + 1 << " is: " << total << endl; 
    }
    return 0;
}