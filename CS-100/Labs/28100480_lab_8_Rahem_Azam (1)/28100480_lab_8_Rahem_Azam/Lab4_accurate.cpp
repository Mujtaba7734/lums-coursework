#include <iostream>
using namespace std;

int main()
{
    string compress_string, check_string;
    string new_string = "";
    int count;

    cout << "Enter string to compress: ";
    cin >> compress_string;
    for (int i =0; i < compress_string.length(); i++)
    {
        count = 1;
        for (int j = i +1; j <= compress_string.length(); j++)
        {
            if (compress_string[i] == compress_string[j])
            {
                count++;
            }
            else
            {
                if (count == 1)
                {
                    new_string += compress_string[i];
                }
                else
                {   
                    new_string += compress_string[i] + to_string(count);
                }
                i = j-1;
                break;
            }
        }
        
    }
    cout << new_string;
    return 0;
}