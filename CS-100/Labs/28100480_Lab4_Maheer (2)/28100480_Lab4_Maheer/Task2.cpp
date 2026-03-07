#include <iostream>
using namespace std;

int main()
{
    char character;
    cout << "Guess the winning character (uppercase): ";
    cin >> character;
    cout << "You guessed: " << character << endl;
    bool result = character == 'R';
    cout << boolalpha;
    cout << "Result: " << result << endl;
    return 0;
}