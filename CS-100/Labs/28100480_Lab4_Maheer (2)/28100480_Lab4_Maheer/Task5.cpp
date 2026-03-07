#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    string name;
    string EMPTY = "";
    cout << "Enter your full name: ";
    getline (cin, name);
    
    int length = name.length();
    int each_side = (50 - length) / 2;
    cout << setfill('-');
    cout << setw(each_side) << EMPTY << setw(length) << name << setw(each_side) << EMPTY << endl;
    return 0;
}