#include <iostream>
using namespace std;

bool isordered(int arr[], int size)
{
    bool sort = true;
    for (int i =0; i < size; i++)
    {
        for (int j= i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                sort = false;
            }
        }
    }
    return sort;
}

int main()
{
    int arr[5] ={1,2,8,4,5};
    int size =5;
    // cout << "Please enter " << size << " elements" << endl;
    // for (int i=0; i < size; i++ )
    // {
    //     cout << i+1 << ": ";
    //     cin >> arr[i];
    // }
    bool sort = isordered(arr, size);
    if (sort == true)
    {
        cout << "True";
    }
    else
    {
        cout << "False";
    }
}