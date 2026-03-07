#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include <iostream>
#include <string>
using namespace std;

class MenuItem {
public:
    string itemName;
    double price;
    int prepTime;

    //Constructors
    MenuItem();
    MenuItem(string name, double price, int time);
    MenuItem(const MenuItem &other);

    //Destructor
    ~MenuItem();

    //setters
    void setItemName(string name);
    void setPrice(double price);
    void setPrepTime(int time);

    //getters
    string getItemName();
    double getPrice();
    int getprepTime();
};

#endif