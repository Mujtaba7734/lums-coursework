#include <iostream>
using namespace std;

int main()
{
    int firstarray[5];
    int secondarray[5];
    int num;
    int finalarray[10];

    cout << "Enter 5 elements for the first sorted array: " << endl;
    for (int i =0; i < 5; i++)
    {
        cin >> num;
        firstarray[i] = num;
    }
    cout << endl << endl;

    cout << "Enter 5 elements for the second sorted array: " << endl;
    for (int i =0; i < 5; i++)
    {
        cin >> num;
        secondarray[i] = num;
    }
    
    for (int i =0; i < 5; i++)
    {
        finalarray[i] = firstarray[i];
    }
    finalarray[5] = secondarray[0];
    finalarray[6] = secondarray[1];
    finalarray[7] = secondarray[2];
    finalarray[8] = secondarray[3];
    finalarray[9] = secondarray[4];
    // final array includes both arrays


    for (int i = 0; i < 10; i++)
    {
        int minindex = i;
        for (int j= i + 1; j < 10; j++)
        {
            if (finalarray[j] < finalarray[minindex])
            {
                minindex=j;
            }
        }
        int temp = finalarray[minindex];
        finalarray[minindex] = finalarray[i];
        finalarray[i] = temp;
    }
    // sorted, now finishing duplicates

    for (int i =0; i < 10; i++)
    {
        for(int j = i + 1; j < 10; j++)
        {
            if (finalarray[i] == finalarray[j] && finalarray[j] != -1)
            {
                finalarray[j] = -1;
            }
        }
    }
    int size = 10;
    for (int j = 0; j < size; j++)
    {
        if (finalarray[j] == -1)
        {
            int i = j;
            while (i < size)
            {
                int temp = finalarray[i];
                finalarray[i] = finalarray[i+ 1];
                finalarray[i + 1] = temp;
                i++;
            }
            size --;
        }
    }
    cout << "Merged and sorted array without duplicates: ";
    for (int i = 0; i < size; i++)
    {
        cout << finalarray[i] << " "; 
    }

}