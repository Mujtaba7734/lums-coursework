#include <iostream>
using namespace std;

void orderIt(int &a, int &b, int &c)
{
    if ((a > b) || (a > c))
    { 
        if (a > b)
        {
            a = a + b;
            b = a - b;
            a = a - b;
        }
        if (a > c)
        {
            a = a + c;
            c = a - c;
            a = a - c;
        }
    }
    if (b > c)
    {
        b = b + c;
        c = b - c;
        b = b - c;
    } 
    cout << endl;
    cout << "Sorted:" << endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
}

int main()
{
    int a,b,c;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "c: ";
    cin >> c;
    orderIt(a,b,c);
}