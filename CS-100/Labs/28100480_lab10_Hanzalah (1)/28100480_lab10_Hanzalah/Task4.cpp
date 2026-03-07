#include <iostream>
using namespace std;

int main()
{
    int size, sum;
    int highest = 0;
    int lowest = 365;
    cout << "Enter the size of the array to hold the birthdates: ";
    cin >> size;
    int birthdays[size];
    cout << "Enter 5 birthdates (from 1 to 365) :" << endl;

    for (int i = 0; i < size; i++)
    {
        cin >> birthdays[i];
    }

    for (int i = 0; i < size; i++)
    {
        if (birthdays[i] > highest)
        {
            highest = birthdays[i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (birthdays[i] < lowest)
        {
            lowest = birthdays[i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        sum += birthdays[i];
    }

    cout << "Maximum birthdate: " << highest << endl;
    cout << "Minimum birthdate: " << lowest << endl;
    cout << "Total sum of all birthdays: " << sum << endl;
    
    return 0;
}