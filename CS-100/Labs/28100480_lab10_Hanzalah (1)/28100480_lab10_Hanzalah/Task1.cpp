#include <iostream>
using namespace std;


int power(int base, int exponent)
{
    int ans;
    if (exponent == 0)
    {
        return 1;
    }
    else
    {
        ans = base * base;
        return base * power(base, exponent -1);
    } 
}

int main()
{
    int base, exponent, ans;
    cout << "Enter base (x): ";
    cin >> base;
    cout << "Enter exponent (n): ";
    cin >> exponent;
    ans = power(base, exponent);
    cout << base << " raised to the power of " << exponent << " is: " << ans;
    return 0;
}