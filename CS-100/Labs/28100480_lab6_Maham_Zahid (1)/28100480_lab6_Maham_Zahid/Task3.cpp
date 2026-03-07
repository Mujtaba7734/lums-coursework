#include <iostream>
using namespace std;

int main()
{
    cout << "Hello! I will tell you which type of paralellogram (rectangle, square, rhombus) you are thnking about, let's start... " << endl;
    cout << endl;
    cout << "Note: Please answer all the questions with YES & NO only" << endl;
    cout << endl;

    string sides_check, angles_check;

    cout << "Are all the sides of parallelogram equal?\t";
    cin >> sides_check;
    if (sides_check == "NO")
    {
        cout << "It is a rectangle!!" << endl;
        return 1;
    } 
    else
    {
        cout << "Are all the sides of parallelogram 90 degrees?  ";
        cin >> angles_check;
        if (angles_check == "YES")
        {
            cout << "It is square!!" << endl;
            return 1;
        }
        else
        {
            cout << "It is rhombus!!" << endl;
            return 1;
        }
    }
    return 0;
}