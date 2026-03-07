#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int matrix[5][5];
    int val = 0;
    int diagonal1;
    int diagonal2;
    int Sum1 = 0;
    int Sum2 = 0;
    cout << "The 5x5 matrix is:" << endl;
    for (int i=0; i<5; i++)
    {   
        for (int j=0; j < 5;j++ )
        {
            val++;
            matrix[i][j] = val;
            cout << setw(4) << matrix[i][j] << " ";          
        }
        cout << endl;
    }
    diagonal1 = 0;
    diagonal2 = 4;
    for (int i=0; i<5; i++)
    {
        cout << diagonal1 << " "<< diagonal2 << endl;
        for (int j=0; j < 5;j++ )
        {
            if (diagonal1 == diagonal2)
            {
                Sum1= Sum1 + matrix[i][diagonal1];
                Sum2= Sum2 + matrix[i][diagonal2];
                cout << Sum1 << endl;
                break;
            }
            else if (j == diagonal2)
            {
                Sum2= Sum2 + matrix[i][diagonal2];
            }
            else if (j == diagonal1)
            {
                Sum1= Sum1 + matrix[i][diagonal1];
                cout << Sum1 << endl;
            }
        }
        diagonal1++;
        diagonal2--;

    }
    cout << "Sum of the primary diagonal: " << Sum1 << endl;
    cout << "Sum of the secondary diagonal: " << Sum2 << endl;
    return 0;
}