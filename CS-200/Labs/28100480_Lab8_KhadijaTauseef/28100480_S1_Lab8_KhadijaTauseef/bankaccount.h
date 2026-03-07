#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "ewallet.h"

/* 
------------------------------------------------------------------------
                        DO NOT WRITE CODE HERE                                                         
------------------------------------------------------------------------
*/

class BankAccount {
private:
    string accountHolder;
    double accountBalance;

public:
    // Constructors
    BankAccount();
    BankAccount(string holder, double initialBalance);

    // Getters
    double getBalance() const;
    string getHolderName() const;

    // Operator overloading
    BankAccount operator+(const Wallet& wallet) const;  // Deposit from wallet
    BankAccount operator-(double amount) const;        // Withdraw money
    friend ostream& operator<<(ostream& os, const BankAccount& account);
};

#endif // BANKACCOUNT_H
