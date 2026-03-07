#include <iostream>
#include <sstream>
#include "ewallet.h"
#include "bankaccount.h"

using namespace std;

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

int totalMarks = 0, maxMarks = 100;  // maxMarks 100

// **Wallet Tests**
void testWalletConstructor() {
    Wallet wallet("Ali", 15000, false);
    bool passed = (wallet.getBalance() == 15000 && wallet.getOwnerName() == "Ali" && !wallet.isPremiumStatus());
    cout << "Testing Wallet Constructor: " << (passed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (10 marks)\n";
    if (passed) totalMarks += 10;
}

void testWalletAddition() {
    Wallet w1("Ali", 15000, false);
    Wallet w2("Maryam", 25000, true);
    Wallet result = w1 + w2;
    bool passed = (result.getBalance() == 40000);
    cout << "Testing Wallet Addition: " << (passed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (10 marks)\n";
    if (passed) totalMarks += 10;
}

void testWalletWithdrawal() {
    Wallet w1("Ali", 15000, false);
    Wallet result = w1 - 5000;
    bool passed = (result.getBalance() == 10000);
    cout << "Testing Wallet Withdrawal: " << (passed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (10 marks)\n";
    if (passed) totalMarks += 10;
}

void testWalletDeposit() {
    Wallet w1("Ali", 15000, false);
    w1 += 5000;
    bool passed = (w1.getBalance() == 20000);
    cout << "Testing Wallet Deposit: " << (passed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (10 marks)\n";
    if (passed) totalMarks += 10;
}

void testWalletComparison() {
    Wallet w1("Ali", 15000, false);
    Wallet w2("Maryam", 25000, true);
    Wallet w3("Sarah", 15000, false);

    bool eqPassed = (w1 == w3);
    bool neqPassed = (w1 != w2);
    bool ltPassed = (w1 < w2);
    bool gtPassed = (w2 > w1);

    cout << "Testing Wallet Equality (==): " << (eqPassed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (5 marks)\n";
    if (eqPassed) totalMarks += 5;

    cout << "Testing Wallet Inequality (!=): " << (neqPassed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (5 marks)\n";
    if (neqPassed) totalMarks += 5;

    cout << "Testing Wallet Less Than (<): " << (ltPassed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (5 marks)\n";
    if (ltPassed) totalMarks += 5;

    cout << "Testing Wallet Greater Than (>): " << (gtPassed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (5 marks)\n";
    if (gtPassed) totalMarks += 5;
}

void testWalletOutputStream() {
    Wallet w1("Ali", 15000, false);
    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());
    cout << w1;
    cout.rdbuf(oldCout);

    string expectedOutput = "Owner: Ali | Balance: 15000 | Premium: No";
    bool passed = (buffer.str().find(expectedOutput) != string::npos);
    
    cout << "Testing Wallet Output Stream: " << (passed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (15 marks)\n";
    if (passed) totalMarks += 15;
}

// **BankAccount Tests**
void testBankConstructor() {
    BankAccount bank("Ali", 50000);
    bool passed = (bank.getBalance() == 50000 && bank.getHolderName() == "Ali");
    cout << "Testing BankAccount Constructor: " << (passed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (5 marks)\n";
    if (passed) totalMarks += 5;
}

void testBankDepositFromWallet() {
    BankAccount bank("Ali", 50000);
    Wallet wallet("Ali", 15000, false);
    BankAccount result = bank + wallet;
    bool passed = (result.getBalance() == 65000);
    cout << "Testing Bank Deposit from Wallet: " << (passed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (5 marks)\n";
    if (passed) totalMarks += 5;
}

void testBankWithdrawal() {
    BankAccount bank("Ali", 50000);
    BankAccount result = bank - 10000;
    bool passed = (result.getBalance() == 40000);
    cout << "Testing Bank Withdrawal: " << (passed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (5 marks)\n";
    if (passed) totalMarks += 5;
}

void testBankOutputStream() {
    BankAccount bank("Ali", 50000);
    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());
    cout << bank;
    cout.rdbuf(oldCout);

    string expectedOutput = "Account Holder: Ali | Balance: 50000";
    bool passed = (buffer.str().find(expectedOutput) != string::npos);

    cout << "Testing Bank Output Stream: " << (passed ? GREEN "PASSED" RESET : RED "FAILED" RESET) << " (10 marks)\n";
    if (passed) totalMarks += 10;
}

// **Main Function**
int main() {
    cout << "\n\033[1;34m==== Testing Wallet Class ====\033[0m\n";
    testWalletConstructor();
    testWalletAddition();
    testWalletWithdrawal();
    testWalletDeposit();
    testWalletComparison();
    testWalletOutputStream();

    cout << "\n\033[1;34m==== Testing Bank Account Class ====\033[0m\n";
    testBankConstructor();
    testBankDepositFromWallet();
    testBankWithdrawal();
    testBankOutputStream();

    cout << "\nFinal Score: " << totalMarks << "/" << maxMarks << "\n";
    return 0;
}
