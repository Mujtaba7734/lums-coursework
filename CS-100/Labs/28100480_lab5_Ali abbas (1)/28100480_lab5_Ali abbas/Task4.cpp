#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int num1, num2, num3;
    cout << "Enter value for num1: ";
    cin >> num1;
    cout << "Enter value for num2: ";
    cin >> num2;
    cout << "Enter value for num3: ";
    cin >> num3;
     
    string check = (num1 & 128) ? "The 8th bit of num1 is set to 1" : "The 8th bit of num1 is not set to 1"; 
    cout << check << endl;
    int bit_14 = pow(2, 13);
    num2 = num2 ^ bit_14;
    cout <<"Modified num2 after flipping the 14th bit: " << num2 << endl;

    int bit_20 = pow(2,19);
    int mod_num2 = num2 | bit_20;
    cout << "Modified num2 after turning on the 20th bit: " << mod_num2 << endl;

    num3 = num3 << 3;
    cout << "Modified num3 after multiplying by 8: " << num3 << endl;

    num3 = num3 >> 2;
    cout << "Modified num3 after dividing by 4: " << num3 << endl;
    return 0;
}  