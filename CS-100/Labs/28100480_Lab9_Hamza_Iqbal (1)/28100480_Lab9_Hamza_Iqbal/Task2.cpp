#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = 3.142;

double calculateAreaCircle(double radius)
{
    double area = PI * pow(radius, 2);
    return area;
}

double calculateCircumference(double radius)
{
    double circumference = 2.00 * PI * radius;
    return circumference;
}

double calculateVolumeSphere(double radius)
{
    double volume = PI * pow(radius, 3) * (4.00 / 3.00);
    return volume;
}

double calculateSurfaceArea(double radius)
{
    double surfacearea = 4.00 * PI * pow(radius, 2);
    return surfacearea;
}

int main()
{
    double radius, area, circumference, volume, surfacearea;
    cout << "Enter the radius of circle/sphere (or -1 to exit): ";
    cin >> radius;
    while (radius != -1)
    {
        cout << "Results for radius " << radius << ":" << endl;
        area = calculateAreaCircle(radius);
        circumference = calculateCircumference(radius);
        volume = calculateVolumeSphere(radius);
        surfacearea = calculateSurfaceArea(radius);

        cout << "Area of Circle: " << area  << endl;
        cout << "Circumference of Circle: "  << circumference  << endl;
        cout << "Volume of Sphere: " << volume << endl;
        cout << "Surface Area of Sphere: " << surfacearea << endl;

        cout << "Enter the radius of circle/sphere (or -1 to exit): ";
        cin >> radius;
    }
    cout << "EXITING PROGRAM" << endl;
    return 0;
}