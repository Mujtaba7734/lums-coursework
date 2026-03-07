#include <iostream>
using namespace std;

void getInput(int &num1, int &num2)
{
    cout << "Enter first Integer: ";;
    cin >> num1;
    cout << "Enter second Integer: ";;
    cin >> num2;
}

void printNumbers(int &num1, int &num2)
{
    cout << "Sorted integers: " << num1 << " " << num2 << endl;
}

void sortNumbers(int &num1, int &num2)
{
    int temp = num1;
    if (num1 > num2)
    {
        num1 = num2;
        num2 = temp;
    }
}

int main()
{
    int num1,num2;
    getInput(num1, num2);
    sortNumbers(num1, num2);
    printNumbers(num1, num2);
}