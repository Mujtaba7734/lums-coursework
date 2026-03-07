#include <iostream>
using namespace std;

bool isValidPassword(string password)
{   
    bool checksmall, checkcapital = false;
    if (password.length() < 8)
    {
        cout << "Invalid Password. Password must be at least 8 characters long" << endl;
        return false;
    }
    for (int i =0; i < password.length(); i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            checkcapital = true;
        }
        if (password[i] >= 'a' && password[i] <= 'z')
        {
            checksmall = true;
        }
    }
    if (checkcapital == false)
    {
        cout << "Invalid Password. Password must contain at least one uppercase letter" << endl;
        return false;
    }
    if (checksmall == false)
    {
        cout << "Invalid Password. Password must contain at least one lowercase letter" << endl;
        return false;
    }
    return true;
}

int main()
{
    bool valid = false;
    string password;
    cout << "Enter a password: ";
    getline(cin, password); 
    while (valid == false)
    {
        valid = isValidPassword(password);
        if (valid == false)
        {
            cout << "Enter a password: ";
            getline(cin, password);
        }
    }
    cout << "Password is valid";
    return 0;
}