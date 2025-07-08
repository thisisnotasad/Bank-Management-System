// Bank.h
// Declares the Bank class for managing accounts and transactions.
// Handles all core banking operations and data persistence.

#pragma once
#include <string>
#include "AccountNode.h"
#include "TransactionStack.h"
#include "AccountsBST.h"

using namespace std;

class Bank {
private:
    AccountNode* head;
    TransactionStack historyStack;
    AccountsBST bst;
    void saveAccounts();
    void loadAccounts();
    void clearAccounts();
public:
    Bank();
    ~Bank();
    void addAccount(string name, string accountNumber, string password, int balance);
    void deleteAccount(string accountNumber);
    void displayAllAccounts();
    void getSortedAccounts();
    void showBalance(string accountNo, string password);
    void deposit(string accountNo, string password, int amount);
    void withdraw(string accountNo, string password, int amount);
    void modifyAccount(string accountNo, string password);
    void getTransactionHistory(string accountNumber, string password);
    void deleteEverything();
    // Expose head for utility (read-only)
    AccountNode* getHead();
};
