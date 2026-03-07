#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    double x,y,z;
    cout << "Enter the value of x: ";
    cin >> x;
    cout << "Enter the value of y: ";
    cin >> y;
    cout << "Enter the value of z: ";
    cin >> z;
    double nominator = (pow(x ,2) + pow(y ,2) + pow(z ,2)) * sin(x) + 3 * cos(y) * tan(z);
    double denominator = 4*x + 5*y + 6*z + 15;
    double result = nominator / denominator;
    cout<< fixed;
    cout << "f(" << setprecision(2) << x << ", " << setprecision(2) << y << ", " << setprecision(2) << z << ") in rounded 2 decimal places = " << setprecision(3) << result << endl;
    cout << scientific;
    cout << "f(" << setprecision(4) << x << ", " << setprecision(4) << y << ", " << setprecision(4) << z << ") in scientific notation = " << setprecision(3) << result << endl;
    return 0; 
}