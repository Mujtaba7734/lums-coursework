#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n;
    cout << "Enter Number you want you table be: ";
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        for (int y = 1; y <= n; y++)
        {
            if (y > 1)
            {
                cout << setw(4) << i * y; 
            }
            else
            {
                cout << i;
            }
       }
       cout << endl;
    }
    return 0;
}