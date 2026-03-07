#include "bankaccount.h"

/* 
------------------------------------------------------------------------
                        WRITE YOUR CODE HERE                    
                        
    The return values for all the methods are NOT your actual 
    return values. They've been placed as placeholders so your 
    test cases run until you implement the function.                                     
------------------------------------------------------------------------
*/

// Default constructor
BankAccount::BankAccount()
{
    accountHolder = "";
    accountBalance = 0.0;
}

// Parameterized constructor
BankAccount::BankAccount(string holder, double initialBalance) 
{
    this->accountHolder = holder;
    this->accountBalance = initialBalance;
} 

// Getters
double BankAccount::getBalance() const { return accountBalance; }
string BankAccount::getHolderName() const { return accountHolder; }

// Deposit money from wallet
BankAccount BankAccount::operator+(const Wallet& wallet) const 
{
    double shift = accountBalance + wallet.getBalance();
    return BankAccount(accountHolder, shift);
}

// Withdraw money
BankAccount BankAccount::operator-(double amount) const 
{
    if (amount > accountBalance)
    {
        return BankAccount(accountHolder, accountBalance);
    }
    else
    {
        return BankAccount(accountHolder, accountBalance - amount);
    }
}

// Overloaded stream insertion operator
ostream& operator<<(ostream& os, const BankAccount& account) 
{
    os << "Account Holder: " << account.accountHolder << " | Balance: " << account.accountBalance; 
    return os;
}
