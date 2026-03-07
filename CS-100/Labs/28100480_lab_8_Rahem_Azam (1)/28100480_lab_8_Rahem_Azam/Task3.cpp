#include <iostream>
using namespace std;

int main ()
{
    int n= 0;
    cout << "Enter your n: ";
    cin >> n;
    cout << "For n = " << n << ":" << endl;
    for (int x =1; x <= n; x++)
    {
        for (int y =0; y < n - x; y++)
        {
            cout << " ";
        }
        int no_sterik = (x * 2) -1;
        for (int z = 0; z < no_sterik ; z++)
        {
            cout << "*";
        }
        cout << endl;
    }
    for (int x = n - 1; x > 0; x--)
    {
        for (int y =n-x; y > 0 ; y--)
        {
            cout << " ";
        }
        int no_sterik = (x * 2) -1;
        for (int z = 0; z < no_sterik ; z++)
        {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}