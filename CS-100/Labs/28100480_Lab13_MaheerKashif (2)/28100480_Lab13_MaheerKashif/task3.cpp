#include <iostream>
using namespace std;

void displaySeating(int seats[3][5])
{
    cout << "Current Seating Arrangement: " << endl;
    for (int i=0; i < 3; i++)
    {
        cout << "Row " << i << " : ";
        for (int j= 0; j < 5; j++)
        {
            cout << *(*(seats + i) + j) << " ";
        }
        cout << endl;
    }
}

bool bookSeat(int seats[3][5], int row, int column)
{
    if (*(*(seats + row) + column) == 1)
    {
        cout << "Seat at row " << row << ", column " << column << " is already booked. Please choose another seat." << endl;
        return false;
    }
    else
    {
        *(*(seats + row) + column) = 1;
        cout << "Seat at row " << row << ", column " << column << " booked successfully!" << endl; 
        return true;
    }
}

int main()
{
    int seats[3][5];
    for (int i = 0; i < 3; i++)
    {
        for(int j=0; j <5; j++)
        {
            *(*(seats + i) + j) = 0;
        }
    }
    
    int row =0;
    int column = 0;
    displaySeating(seats);
    cout << endl;
    cout << "Enter row to book a seat (or enter -1 to stop): ";
    cin >> row;
    cout << "Enter col number (or enter -1 to stop): ";
    cin >> column;
    cout << endl;
    while (row != -1 && column != -1)
    {   
        bool check = bookSeat(seats, row, column);
        if (check == false)
        {
            cout << "Please try again with a different seat" << endl;
        }
        cout << endl;
        displaySeating(seats);
        cout << "Enter row to book a seat (or enter -1 to stop): ";
        cin >> row;
        cout << "Enter col number (or enter -1 to stop): ";
        cin >> column;
        cout << endl;
    }
    cout << endl;
    cout << "Final Seating Arrangement:" << endl;
    displaySeating(seats);
    return 0;
}