#include <iostream>
using namespace std;

int main()
{
    string fullname, emailaddress, password;
    int length, check;
    int index = 0;

    cout << "Enter your full name: ";
    getline(cin, fullname);

    for (int count = 1; count < 5; count ++)
    {
        cout << "Enter your email: ";
        cin >> emailaddress;
        index = emailaddress.find('@');
        if (index > 0)
        {
            break;
        }
        cout << "Invalid email: missing '@' symbol." << endl;
        check = count;
    }
    if (check == 4)
    {
        cout << "Too many invalid attempts. Registration failed." << endl;
        return 1;
    }

    cout << endl;
    cout << "Email verified" << endl;
    cout << endl;

    for (int count = 1; count < 5; count ++)
    {
        cout << "Enter your password: ";
        cin >> password;
        length = password.length();
        if (length > 8 && length < 15)
        {
            break;
        }
        cout << "Invalid password: must be between 8 and 15 characters long." << endl;
        check = count; 
    }
    if (check == 4)
    {
        cout << "Too many invalid attempts. Registration failed." << endl;
        return 1;
    }
    else
    {
        cout << endl;
        cout << "Registration successful!" << endl;
        cout << "Full name: " << fullname << endl;
        cout << "Email: " << emailaddress << endl;
        cout << "Password: " << password << endl;
        return 1;
    }
    return 0;
}