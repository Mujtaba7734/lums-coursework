#include <iostream>
using namespace std;

int main()
{
    int PRICE_ROLL = 80;
    int PRICE_BREAD = 60;
    int PRICE_SALAD = 50;
    int PRICE_CHICKEN = 250;
    int PRICE_PASTA = 200;
    int PRICE_CURRY = 180;
    int PRICE_ICECREAM = 70;
    int PRICE_CAKE = 90;
    int PRICE_FRUITSALAD = 50;
    
    int appetizer_num, main_num, dessert_num;
    int total = 0;

    cout << "Welcome to PDC" <<endl;
    cout << endl;
    cout << "Please select an appetizer:" << endl;
    cout << "1. Spring Rolls - Rs 80" << endl;
    cout << "2. Garlic Bread - Rs 60"<< endl;
    cout << "3. Salad - Rs 80" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> appetizer_num;

    switch (appetizer_num)
    {
        case 1: total += PRICE_ROLL; break;
        case 2: total += PRICE_BREAD; break;
        case 3: total += PRICE_SALAD; break;
        default: cout << "Invalid appetizer selection!"; return 1;
    }

    cout << endl;
    cout << "Please select an main course:" << endl;
    cout << "1. Grilled Chicken - Rs 250" << endl;
    cout << "2. Pasta - Rs 200"<< endl;
    cout << "3. Vegetarian Curry - Rs 180" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> main_num;

    switch (main_num)
    {
        case 1: total += PRICE_CHICKEN; break;
        case 2: total += PRICE_PASTA; break;
        case 3: total += PRICE_CURRY; break;
        default: cout << "Invalid Main Course selection!"; return 1;
    }

    cout << endl;
    cout << "Please select an dessert:" << endl;
    cout << "1. Ice Cream - Rs 70" << endl;
    cout << "2. Chocolate cake - Rs 90"<< endl;
    cout << "3. Fruit Salad - Rs 50" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> dessert_num;
    switch (dessert_num)
    {
        case 1: total += PRICE_ICECREAM; break;
        case 2: total += PRICE_CAKE; break;
        case 3: total += PRICE_FRUITSALAD; break;
        default: cout << "Invalid dessert selection!"; return 1;
    }

    cout << endl;
    cout << "Your total cost for a meal is: Rs. " << total << endl;
    return 0;
}