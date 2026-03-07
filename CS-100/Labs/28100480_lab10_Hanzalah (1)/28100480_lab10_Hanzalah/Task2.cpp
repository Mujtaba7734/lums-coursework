#include <iostream>
using namespace std;

int mod(int integer)
{
    if (integer < 10)
    {
        return integer;
    }
    else
    {
        return (integer % 10) + mod(integer / 10);
    }
}

int main()
{
    int integer, sum;
    cout << "Enter a non-negative integer: ";
    cin >> integer;
    sum = mod(integer);
    cout << "The sum of the digits of " << integer << " is: " << sum << endl;
    return 0;
}