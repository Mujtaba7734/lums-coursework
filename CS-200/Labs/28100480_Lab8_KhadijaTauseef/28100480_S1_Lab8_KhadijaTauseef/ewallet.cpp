#include "ewallet.h"

/* 
------------------------------------------------------------------------
                        WRITE YOUR CODE HERE                    
                        
    The return values for all the methods are NOT your actual 
    return values. They've been placed as placeholders so your 
    test cases run until you implement the function. Do not 
    remove them until you've implemented that particular method                                   
------------------------------------------------------------------------
*/


// Default constructor
Wallet::Wallet() 
{
    ownerName = "";
    balance = 0.0;
    isPremium = false;
}

// Parameterized constructor
Wallet::Wallet(string owner, double initialBalance, bool premium) 
{
    this->ownerName = owner;
    this->balance = initialBalance;
    this->isPremium = premium;
}

// Getters
double Wallet::getBalance() const
{ 
    return balance; 
}

string Wallet::getOwnerName() const 
{ 
    return ownerName; 
}

bool Wallet::isPremiumStatus() const 
{ 
    return isPremium; 
}

// Transfer money between wallets
Wallet Wallet::operator+(const Wallet& other) const 
{
    double sum;
    sum = this->balance + other.balance;

    return Wallet(ownerName, sum, false); 
}

// Withdraw money
Wallet Wallet::operator-(double amount) const 
{
    double shift = 0.0;
    if (amount < this->balance)
    {
        shift = this->balance - amount;
    }

    return Wallet(ownerName, shift, false); 
}

// Add money
Wallet& Wallet::operator+=(double amount) 
{
    this->balance += amount;
    if (this->balance > 50000 && isPremium == false)
    {
        this->balance = 50000;
    }
    return *this; 
}

// Deduct money
Wallet& Wallet::operator-=(double amount) 
{
    if (amount < this->balance)
    {
        this->balance -= amount;
    }
    if (this->balance < 50,000)
    {
        isPremium = false;
    }
    else
    {
        isPremium = true;
    }
    return *this; 
}

// Compare wallets
bool Wallet::operator==(const Wallet& other) const 
{
    if (this->balance == other.balance)
    {
        return true;
    }
    return false; 
}

bool Wallet::operator!=(const Wallet& other) const 
{
    if (this->balance != other.balance)
    {
        return true;
    }
    return false; 
}

bool Wallet::operator<(const Wallet& other) const 
{
    if (this->balance < other.balance)
    {
        return true;
    }
    return false; 
}

bool Wallet::operator>(const Wallet& other) const 
{
    if (this->balance > other.balance)
    {
        return true;
    }
    return false; 
}

// Overloaded stream insertion operator
ostream& operator<<(ostream& os, const Wallet& wallet) 
{
    if (wallet.isPremium == false)
    {
        os << "Owner: " << wallet.ownerName << " | Balance: " << wallet.balance << " | Premium: No ";
    }
    else
    {
        os << "Owner: " << wallet.ownerName << " | Balance: " << wallet.balance << " | Premium: Yes";
    }
    
    return os; 
}
