#include <iostream>
using namespace std;

int main()
{
    string word;
    string sentence = "";
    cout << "Enter Words: ";
    cin >> word;
    if (word == "EXIT")
    {
        cout << "sentence formed is: " << sentence;
        return 1;
    }
    else
    {
        do
        {
            sentence = sentence + " " + word;
            cin >> word;
        }
        while (word != "EXIT");
        cout << "sentence formed is: " << sentence;
    }
    return 0;
}
