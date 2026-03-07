#ifndef ORDER_HPP
#define ORDER_HPP

#include "Customer.hpp"
#include "MenuItem.hpp"
using namespace std;

class Order {
private:
    int orderTable;
    Customer customer;
    MenuItem items[10];
    int itemCount;
    static const int maxItems = 10;

public:
    //Constructors
    Order();
    Order(int n, Customer c);
    Order(const Order &other);

    //Destructor
    ~Order();

    bool addItem(MenuItem item);
    bool removeItem(string itemName);
    void removeDuplicates();
    bool isOrderFull();
    double calculateTotalPrice(double discount) const;
    string orderServeTime(string currentTime) const;
    void splitOrder (Order &newOrder, int splitIndex);
    void printOrderDetails();
};

#endif