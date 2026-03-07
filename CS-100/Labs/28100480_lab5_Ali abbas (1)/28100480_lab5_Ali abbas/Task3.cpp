#include <iostream>
using namespace std;

int main()
{
    string fullstring; 
    cout <<"Enter Campus Id, full name, and Age separated by semicolons: ";
    getline(cin, fullstring);

    string rollnumber = fullstring.substr(0, fullstring.find(';'));
    string year = rollnumber.substr(0,2);
    string grad_year = "20" + year;
    string school_code = rollnumber.substr(2,2);
    string roll_number = rollnumber.substr(4,4);
    
    int length = fullstring.length();
    string remainingstring = fullstring.substr(fullstring.find(';') + 1, length);
    string full_name = remainingstring.substr(0, remainingstring.find(';'));
    string first_name = full_name.substr(0, full_name.find(' '));
    string last_name = full_name.substr(full_name.find(' ') + 1, full_name.length());

    string age = remainingstring.substr(remainingstring.find(';') + 1, remainingstring.length()); 

    cout << "Graduating Year: " << grad_year << endl;
    cout << "School Code: " << school_code << endl;
    cout << "Roll Number: " << roll_number << endl;
    cout << "First Name: " << first_name << endl;
    cout << "Last Name: " << last_name << endl;
    cout << "Age: " << age << endl;
    return 0;
}

