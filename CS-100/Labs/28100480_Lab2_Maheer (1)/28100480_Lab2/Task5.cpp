#include <iostream>
using namespace std;

int main(){
    int ascii = 65;
    cout << "Character: " << static_cast<char>(ascii) << endl;
    ascii += 10;
    cout << "New Character: " << static_cast<char>(ascii) << endl;
    char ch = 'z';
    cout << "Ascii value is: " << static_cast<int>(ch) << endl;
}