#include <iostream>
using namespace std;

int main()
{
    const string alphabets= "abcdefghijklmnopqrstuvwz";
    string compress_string, check_string;
    string new_string = "";
    bool check;
    int count = 0;

    cout << "Enter string to compress: ";
    cin >> compress_string;
    for (int i =0; i < compress_string.length(); i++)
    {
        check_string = "";
        check_string += compress_string[i];
        for (int j =i + 1; j < compress_string.length(); j++)
        {

            if (compress_string[i] == compress_string[j])
            {
                check_string += compress_string[j];
            }
        }
        check = false;
        for (int k = 0; k < new_string.length(); k++)
        {
            if (new_string[k] == compress_string[i])
            {
                check = true;
            }
        }
        if (check == false)
        {
            new_string = new_string + compress_string[i] + to_string(check_string.length());
        }
    }
    cout << new_string;
    return 0;
}