#include <iostream>
using namespace std;

int main()
{
    int num1, num2;
    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;
    int count = 1;
    int hcf = 1;
    if (num1 > num2)
    {
        while (count <= num2)
        {
            if ((num2 % count == 0) && (num1 % count == 0))
            {
                hcf = count;
            }
            count++;
        }
    }
    else
    {
        while (count <= num1)
        {
            if ((num1 % count == 0) && (num2 % count == 0))
            {
                hcf = count;
            }
            count++;
        }
    }
    cout << "HCF of " << num1 << " and " << num2 << " is: " << hcf << endl; 
    return 0;
}