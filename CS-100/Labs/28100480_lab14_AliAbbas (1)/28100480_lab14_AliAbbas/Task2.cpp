#include <iostream>
using namespace std;

void palindrome(char str[100], int length)
{
    bool palindrome = true;
    for (int i= 0; i <= length/2; i++)
    {
        if (str[i] == str[length - i - 1 ])
        {
            palindrome = true;
        }
        else 
        {
            palindrome = false;
        }
    }
    if (palindrome == true)
    {
        cout << "The string is a palindrome" << endl;
    }
    else
    {
        cout << "The string is not a palindrome" << endl;
    }
}
void reverse(char str[100], int length)
{
    cout << "Reversed String; ";
    for (int i = length; i > -1; i--)
    {
        cout << str[i];
    }
}

int main()
{
    char str[100];
    cout << "Enter a string (max 100 characters, no spaces) : ";
    cin.getline(str, 100);
    char* ptr = str;
    int length = 0;
    while (*ptr != '\0')
    {
        length++;
        ptr++;
    }
    cout << "The length of the string is " << length << endl;
    palindrome(str, length);
    reverse(str, length);
    return 0;
}