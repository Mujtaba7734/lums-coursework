#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <iostream>
#include <string>
using namespace std;

class Customer {
private:
    string customerName;
    string contactNumber;

public:
    //Constructors
    Customer();
    Customer(string name, string number);
    Customer(const Customer &other);

    //Destructor
    ~Customer();

    //setters
    void setCustomerName(string name);
    void setContactNumber(string number);
    bool isValidContactNumber(const string &number);

    //getters
    string getCustomerName();
    string getContactNumber();
};

#endif