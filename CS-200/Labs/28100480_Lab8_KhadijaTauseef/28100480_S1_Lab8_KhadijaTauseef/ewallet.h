#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <string>
using namespace std;

/* 
------------------------------------------------------------------------
                        DO NOT WRITE CODE HERE                                                         
------------------------------------------------------------------------
*/

class Wallet {
private:
    string ownerName;
    double balance;
    bool isPremium;

public:
    // Constructors
    Wallet();
    Wallet(string owner, double initialBalance, bool premium);

    // Getters
    double getBalance() const;
    string getOwnerName() const;
    bool isPremiumStatus() const;

    // Operator overloading
    Wallet operator+(const Wallet& other) const;   // Transfer money between wallets
    Wallet operator-(double amount) const;        // Withdraw money
    Wallet& operator+=(double amount);            // Add money to wallet
    Wallet& operator-=(double amount);            // Deduct money from wallet
    bool operator==(const Wallet& other) const;   // Compare wallets by balance
    bool operator!=(const Wallet& other) const;
    bool operator<(const Wallet& other) const;
    bool operator>(const Wallet& other) const;

    // Overloaded stream insertion operator
    friend ostream& operator<<(ostream& os, const Wallet& wallet);
};

#endif // WALLET_H
