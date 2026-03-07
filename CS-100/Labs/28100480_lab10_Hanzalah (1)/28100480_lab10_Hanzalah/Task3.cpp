#include <iostream>
using namespace std;

string sterik(int number)
{
    if (number == 0)
    {
        return "";
    }
    else
    {
        string a =  "*" + sterik(number - 1);
        //return "*" + sterik(number - 1);
        return  a ;   
    }
}

void triangle(int num, int &count)
{
    if (count <= num)
    {
        cout << sterik(count) << endl;
        count++;
        return triangle(num, count);
    }

}
int main()
{
    int count = 1;
    int num;
    cout << "Enter the number of rows for the triangle: ";
    cin >> num;
    triangle(num, count);
}