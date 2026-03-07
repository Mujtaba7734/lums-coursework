#include <iostream>
using namespace std;

int main()
{
    int CHECK_1000 = 1000;
    int CHECK_100 = 100;
    int CHECK_10 = 10;

    int number;
    int total = 0;
    cout << "Enter a 4-digit number: ";
    cin >> number;
    int orignal_number = number;
    int num_1000 = number / CHECK_1000;
    total += num_1000;
    number = number % CHECK_1000;
    int num_100 = number / CHECK_100;
    total += num_100;
    number = number % CHECK_100;
    int num_10 = number / CHECK_10;
    total += num_10;
    number = number % CHECK_10;
    total += number;

    cout << "The Sum of the digits in " << orignal_number << " is: " << total << endl;
    return 0;
}