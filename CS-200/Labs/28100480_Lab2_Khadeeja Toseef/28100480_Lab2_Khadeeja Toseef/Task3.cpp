#include <iostream>
using namespace std;

void initializeTemperatures(double temperatures[], int size)
{
    for (int i =0; i < size; i++)
    {
        cout << "Enter the temperatures for " << i+1 << " month:    ";
        cin >> temperatures[i];
        while ((temperatures[i] < -50) || (temperatures[i] > 50))
        {
            cout << "Invalid temperatures, Enter again: ";
            cin >> temperatures[i];
        }
    }
}

double calculateAverageTemperature(double temperatures[],int size)
{
    double total = 0;
    for (int i= 0; i < size; i++)
    {
        total += temperatures[i];
    }
    return total/size;
    
}

double calculateTemperatureVariance(double temperatures[],int size)
{
    double max = -51;
    double min = 51;
    for (int i= 0; i < size; i++)
    {
        if (temperatures[i] > max)
        {
            max = temperatures[i];
        }
        if (temperatures[i] < min)
        {
            min = temperatures[i];
        }
    }
    return max - min;
}

string findHighestTempMonthName(const double temperatures[] ,int size)
{
    double max = -51;
    for (int i= 0; i < size; i++)
    {
        if (temperatures[i] > max)
        {
            max = temperatures[i];
        }
    }
    int intmonth = 0;
    for (int i= 0; i < size; i++)
    {
        if (max == temperatures[i])
        {
            intmonth = i;
            break;
        }
    }
    if (intmonth == 0){return "January";}
    if (intmonth == 1){return "Febuary";}
    if (intmonth == 2){return "March";}
    if (intmonth == 3){return "April";}
    if (intmonth == 4){return "May";}
    if (intmonth == 5){return "June";}
    if (intmonth == 6){return "July";}
    if (intmonth == 7){return "August";}
    if (intmonth == 8){return "September";}
    if (intmonth == 9){return "October";}
    if (intmonth == 10){return "November";}
    if (intmonth == 11){return "December";}
    return "Error";
}
void convertToFahrenheit(double temperatures[] , int size)
{
    for (int i= 0; i < size; i++)
    {
        temperatures[i] = (temperatures[i] * 9.0/5.0) + 32;
    }
}

int main()
{
    double temperatures[12];
    int size = 12;
    initializeTemperatures(temperatures, size);
    double avg = calculateAverageTemperature(temperatures,size);
    double var = calculateTemperatureVariance(temperatures,size);
    string month = findHighestTempMonthName(temperatures,size);
    convertToFahrenheit(temperatures,size);

    cout << endl;
    cout << "Average: " << avg << endl;
    cout << "Variance: " << var << endl;
    cout << "Month with highest temprature:  " << month << endl;

    cout << endl;
    cout << "Changed to Fahrenheit: " << endl;
    for (int i= 0; i < size; i++)
    {
        cout << i + 1 << "   " << temperatures[i] << endl;
    }
}