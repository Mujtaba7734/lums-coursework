#include <iostream>
using namespace std;

void addelements(int fixed_arr[], int &size)
{
    int num;
    cout << "Enter 7 elements for the array:" << endl;
    while (size < 7)
    {
        cin >> num;
        fixed_arr[size] = num;
        size ++;
    }
}

void display(int fixed_arr[], int size)
{
    cout << "UpdatedArray: ";
    for (int n =0; n < size; n++)
    {
       cout << fixed_arr[n] << " ";
    }
    cout << endl;
}

void deleteElement(int fixed_arr[], int &size, int element)
{
    int temp;
    int index;  
    bool check = false;
    for (int n = 0; n < size; n++ )
    {
        if (fixed_arr[n] == element)
        {
            check = true;
            index = n;
            break;
        }
        else
        {
            check = false;
        }
    }
    if (check == false)
    {
        cout << "Number " << element << " not found in the array" << endl; 
    }
    else
    {
        for (int i = index; i < size -1; i++ )
        {
            fixed_arr[i] = fixed_arr[i + 1];
        }
        size = size -1;
    }

}
int main()
{
    int size = 0;
    int fixed_arr[7];
    int choice = 1;
    addelements(fixed_arr, size);
    while (choice != 2)
    {
        cout << "Menu:" << endl;
        cout << "1. Delete an element from the array" << endl;
        cout << "2. Exit" << endl;
        cin >> choice;
        if (choice == 2)
        {
            cout << "Exiting the program" << endl;
            break;
        }
        else if (choice == 1)
        {
            int num;
            cout << "Enter the number you want to delete: " << endl;
            cin >> num;
            deleteElement(fixed_arr, size, num);
            display(fixed_arr, size);
        }
        else
        {
            cout << "Invalid choice. Please enter between 1 and 2" << endl;
        }
    }
}