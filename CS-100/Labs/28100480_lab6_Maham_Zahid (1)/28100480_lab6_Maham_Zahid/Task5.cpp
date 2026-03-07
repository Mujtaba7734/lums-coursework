#include <iostream>
using namespace std;

int main()
{
    float RATES_UNIT100 = 22.0;
    float RATES_UNIT200 = 36.90;
    float RATES_UNIT300 = 39.10;
    float RATES_UNITABOVE300 = 40.0;

    int units_consumed, remaining_units, total_price;
    cout << "Enter the number of electricity units consumed: ";
    cin >> units_consumed;

    if (units_consumed < 100)
    {
        total_price = units_consumed * RATES_UNIT100;
    }
    else if (units_consumed < 200)
    {
        remaining_units = units_consumed - 100;
        total_price += 100 * RATES_UNIT100;
        total_price += remaining_units * RATES_UNIT200;
    }
    else if (units_consumed < 300)
    {
        total_price += 100 * RATES_UNIT100;
        total_price += 100 * RATES_UNIT200;
        remaining_units = units_consumed - 200;
        total_price += remaining_units * RATES_UNIT300;  
    }
    else
    {
        total_price += 100 * RATES_UNIT100;
        total_price += 100 * RATES_UNIT200;
        total_price += 100 * RATES_UNIT300;
        remaining_units = units_consumed - 300;
        total_price += remaining_units * RATES_UNITABOVE300;
    }

    cout << "The total bill amout is Rs. " << total_price;
    return 0;
}