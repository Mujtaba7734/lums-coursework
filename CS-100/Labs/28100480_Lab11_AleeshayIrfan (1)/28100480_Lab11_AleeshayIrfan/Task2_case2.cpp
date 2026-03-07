#include <iostream>
using namespace std;

int countOccurances(int arr[], int size, int value, int index)
{
    int count = 0;
    if (index == size)
    {
        return count;
    }
    else
    {
        if (arr[index] == value)
        {
            count ++;
            return count + countOccurances(arr, 7, value, index + 1);
        }
        else
        {
            return count + countOccurances(arr, 7, value, index + 1); 
        }
    }
}

int main()
{
    int arr[] = {5,5,5,5,5};
    int index =0;
    int targetvalue;
    cout << "Enter your target value: ";
    cin >> targetvalue; 
    int total = countOccurances(arr, 7, targetvalue, index);
    cout << "Occurences of " << targetvalue << ": " << total;
    return 0; 
}