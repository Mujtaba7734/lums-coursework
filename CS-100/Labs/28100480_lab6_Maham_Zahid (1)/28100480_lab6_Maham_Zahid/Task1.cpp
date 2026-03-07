#include <iostream>
using namespace std;

int main()
{
    string word;
    bool check = true;
    cout << "Enter a word to translate into slang: ";
    cin >> word;
    if (word == "cool")
    {
        word = "lit";
    }
    else if (word == "amazing")
    {
        word = "fire";
    }
    else if (word == "tired")
    {
        word = "dead";
    }
    else if (word == "jealous")
    {
        word = "salty";
    }
    else if (word == "outfit")
    {
        word = "fit";
    }
    else
    {
        word = "I don't know";
        check = false;
    }
    if (check == true)
    {
        cout << "slang equivalent: " << word << endl;
    }
    else
    {
        cout << "I don't know" << endl;
    }
    return 0;
}