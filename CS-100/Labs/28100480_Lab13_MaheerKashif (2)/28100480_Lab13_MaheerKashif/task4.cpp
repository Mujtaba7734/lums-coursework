#include <iostream>
using namespace std;

void populateMatrix(int matrix[4][4])
{
    for(int i =0; i < 4; i++)
    {
        cout << "Enter values for row " << i + 1 << endl;
        for (int j =0; j < 4; j++)
        {
            cin >> *(*(matrix + i) + j);
        }
    }
}

void displayMatrix(int matrix[4][4])
{
    for(int i =0; i < 4; i++)
    {
        for (int j =0; j < 4; j++)
        {
            cout << *(*(matrix + i) + j) << " | ";
        }
        cout << endl;
    }
}

void rotateMatrix90(int matrix[4][4])
{
    for (int i =0; i < 4; i++) // Transpose
    {
        for (int j= i + 1; j < 4; j++)
        {
            int temp = *(*(matrix + i) + j);
            *(*(matrix + i) + j) = *(*(matrix + j) + i);
            *(*(matrix + j) + i) = temp;
        }
    }
    for(int i = 0; i < 4; i++) //reverse
    {
        for(int j = 0; j < 2; j++) 
        {
            int temp = *(*(matrix + i) + j);
            *(*(matrix + i) + j) = *(*(matrix + i) + (3-j));
            *(*(matrix + i) + (4-1-j)) = temp;
        }
    }
}

int main()
{
    int matrix[4][4];
    populateMatrix(matrix);
    cout << "State of Matrix after taking input:" << endl; 
    displayMatrix(matrix);
    for (int i = 1; i < 5; i++)
    {
        cout << endl;
        cout << "State of 2D array after rotating by " << 90 * i << endl;
        rotateMatrix90(matrix);
        displayMatrix(matrix);
    }
}