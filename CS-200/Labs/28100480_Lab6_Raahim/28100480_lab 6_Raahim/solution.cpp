#include <iostream>
#include <string>
#include "MenuItem.hpp"
#include "Customer.hpp"
#include "Order.hpp"

using namespace std;

//Implement these functions

// MenuItem Class
MenuItem::MenuItem()
{
    itemName = "N/A";
    price = 0;
    prepTime = 0.0;
}
MenuItem::MenuItem(string name, double price, int time)
{
    itemName = name;
    this->price = price;
    if (price < 100)
    {
        this->price = 100;
    }
    prepTime = time;

}
MenuItem::MenuItem(const MenuItem &other)
{
    itemName = other.itemName;
    price = other.price;
    prepTime = other.prepTime;
}
void MenuItem::setItemName(string name)
{
    itemName = name; 
}

void MenuItem::setPrice(double price)
{
    this->price = price;
}
void MenuItem::setPrepTime(int time)
{
    prepTime = time;
}
string MenuItem:: getItemName()
{
    return itemName;
}
double MenuItem:: getPrice()
{
    return price;
}
int MenuItem:: getprepTime()
{
    return prepTime;
}
MenuItem::~MenuItem()
{
    cout << "MenuItem is deleted" << endl;
}

// Customer Class
Customer::Customer()
{
    customerName = "N/A";
    contactNumber = "N/A";
}
Customer::Customer(string name, string number)
{
    customerName = name;
    contactNumber = number;
}
Customer::Customer(const Customer &other)
{
    customerName = other.customerName;
    contactNumber = other.contactNumber;
}
void Customer::setCustomerName(string name)
{
    customerName = name;
}
void Customer::setContactNumber(string number)
{
    contactNumber = number;
}
string Customer::getCustomerName()
{
    return customerName;
}

string Customer::getContactNumber()
{
    return contactNumber;
}
bool Customer:: isValidContactNumber(const string &number)
{
    for (int i = 0; i < number.length(); i++)
    {
        if (number[i] < 48 || number[i] > 57)
        {
            return false;
        }
    }
    return true;
}

Customer::~Customer()
{
    cout << "The customer entity is deleted" << endl;
}

// Order Class
Order::Order()
{
    orderTable = 0;
    customer= Customer();
    itemCount = 0;
}

Order::Order(int n, Customer c)
{
    orderTable = n;
    customer = Customer(c);
    itemCount = 0;
}

Order::Order(const Order &other)
{
    orderTable = other.orderTable;
    customer = other.customer;
    for (int i = 0; i < 10; i++)
    {
        items[i] = other.items[i];
    }
    itemCount = other.itemCount;
}

bool Order::addItem(MenuItem item)
{
    
    if (itemCount + 1 > maxItems)
    {
        return false;
    }
    else
    {
        itemCount++;
        items[itemCount] = item;
        return true;
    }
}
bool Order::removeItem(string itemName)
{
    for (int i = 0; i < maxItems; i++)
    {
        if (items[i].getItemName() ==  itemName)
        {
            items[i].setItemName("N/A");
            items[i].setPrepTime(0);
            items[i].setPrice(0.0);
            itemCount--;
            return true;
        }
    }
    return false;
}
void Order::removeDuplicates()
{
    for (int i =0; i < maxItems; i++)
    {
        for (int j =i + 1; j < maxItems; j++)
        {
            if (items[i].getItemName() == items[j].getItemName())
            {
                items[j].itemName = "N/A";
                items[j].setPrepTime(0);
                items[j].setPrice(0.0);
                itemCount--;
            } 
        }
    }
}

bool Order::isOrderFull()
{
    if (itemCount == maxItems)
    {
        return true;
    }
    return false;
}

double Order::calculateTotalPrice(double discount) const
{
    double total_price = 0.0;
    for (int i = 0; i < maxItems; i++)
    {
        total_price += items[i].price;
    }
    double total_discount = (discount/100) * total_price;
    if (total_discount > 60)
    {
        return total_price;
    }
    else
    {
        total_price -= total_discount;
        return total_price;
    }

    
}
string Order::orderServeTime(string currentTime) const
{
    int mins = (int)currentTime[3] * 10;
    mins = mins + (int) currentTime[4];
    int totalpreptime;
    for (int i=0; i < itemCount; i++)
    {
        totalpreptime += items[itemCount].prepTime;
    }

    int hrs = (int)currentTime[0] * 10;
    hrs = hrs + (int) currentTime[1];

    int total_mins = totalpreptime + mins;
    int total_hrs = total_mins/ 60;
    total_mins = total_mins - (total_hrs * 60);

    hrs = hrs + total_hrs;
    if (hrs >= 24)
    {
        hrs = hrs -24;
    }    
    string final_time = to_string(hrs) + ":" + to_string(total_mins);
    
    return final_time;
}
void Order::splitOrder(Order &newOrder, int splitIndex)
{
    int count;
    for (int i =splitIndex; i < maxItems; i++)
    {
        newOrder.items[count] = items[i];
        count++; 
        items[i].setItemName("N/A");
        items[i].setPrice(0);
        items[i].setPrepTime(0.0);
    }
    itemCount = splitIndex;
    newOrder.itemCount = count;
}
void Order::printOrderDetails()
{
    cout << "Customer Name: " << customer.getCustomerName() << endl;
    cout << "Customer Contact Number: " << customer.getContactNumber() << endl;
    cout << "List of ordered items: " << endl;
    for (int i = 0; i < itemCount; i++)
    {
        cout << i + 1 << ":" << items[i].getItemName() << endl; 
    }
    cout << "Total price without discount: " << calculateTotalPrice(0.0);
    cout << "Time right now: 12:03" << endl;
    cout << "Estimated Time :" << orderServeTime("12:03") << endl; 
}
Order::~Order()
{
    cout << "The order was deleted" << endl;
}