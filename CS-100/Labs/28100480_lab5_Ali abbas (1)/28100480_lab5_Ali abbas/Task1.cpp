#include <iostream>
using namespace std;

int main()
{
    int number;
    cout << "Enter a number: ";
    cin >> number;
    string check = (number < 0) ? "The number is negative": (number > 0) ? "The number is positive": "The number is zero";
    cout << check << endl;
    
    return 0;
}