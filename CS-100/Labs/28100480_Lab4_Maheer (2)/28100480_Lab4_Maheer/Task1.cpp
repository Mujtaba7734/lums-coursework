#include <iostream>
using namespace std;

int main()
{
    char uppercase, lowercase; 
    cout << "Enter uppercase character: ";
    cin >> uppercase;
    lowercase = uppercase + 32;
    cout << "Orignal Character: " << uppercase << endl;
    cout << "Lowercase Character: " << lowercase << endl;
    return 0;
}