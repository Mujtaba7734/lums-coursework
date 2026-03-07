#include <iostream>
using namespace std;

int main()
{
    int choice = 0;
    int totalSize = 1;
    int *arr = new int[totalSize];
    int size = 0;
    while (choice != 4)
    {
        cout << "Menu:"<< endl;
        cout << "1. Add a new score " << endl;
        cout << "2. Delete a score " << endl;
        cout << "3. Calculate and print the average score " << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: " ;
        cin >> choice;
        if (choice == 1)
        {
            if (size < totalSize)
            {
            cout << "Enter the score to add: ";
            cin >>*(arr + size);
            size++;
            }
            else
            {
                totalSize = totalSize * 2;
                int *newArr = new int[totalSize];
                for (int i =0; i < size; i++)
                {
                    *(newArr + i) = *(arr + i);
                }
                delete[] arr;
                arr = newArr;
                cout << "Enter the score to add: ";
                cin >> *(arr + size);
                size++;
                cout << "Increasing size by capacity = " << totalSize << endl;
            }
        }
        else if (choice == 2)
        {
            int index;
            cout << "Enter the index of the score to delete: ";
            cin >> index;
            if (index < size)
            {
                totalSize--;
                int *newarr = new int[totalSize];
                for (int i =0; i < index; i++)
                {
                    *(newarr + i) = *(arr + i);
                }
                for (int i = index + 1; i < size; i++)
                {
                    *(newarr + (i - 1 )) = *(arr + i);
                }
                delete[] arr;
                size--;
                arr = newarr;
                cout << "Size is now = " << size; 
            }
        }
        else if (choice == 3)
        {
            int total = 0;
            if (size == 0)
            {
                cout << "No scores are entered" << endl;
            }
            else
            {
                for (int i =0; i < size; i++)
                {
                    total += *(arr + i);
                }
                int average = total / size;
                cout << "Average Score: " << average << endl;
            }
        }
        else if (choice == 4)
        {
            delete [] arr;
            break;
        }
        else
        {
            cout << "You have entered wrong choice... Please enter again" << endl;
        }
        cout << endl;
    }
    return 0;
}