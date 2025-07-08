// Bank.cpp
// Handles all core banking operations and data persistence.

#include "AccountNode.h"
#include "Utils.h"
#include "Bank.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Bank::Bank()
{
    head = nullptr;
    loadAccounts();
}

Bank::~Bank()
{
    clearAccounts();
}

void Bank::saveAccounts()
{
    ofstream file("accounts.txt");
    if (!file)
    {
        cout << "Error opening file for writing." << endl;
        return;
    }
    AccountNode *temp = head;
    while (temp != nullptr)
    {
        file << temp->name << "," << temp->accountNumber << "," << temp->password << "," << temp->balance << endl;
        temp = temp->next;
    }
}

void Bank::loadAccounts()
{
    ifstream file("accounts.txt");
    if (!file)
    {
        cout << "Error opening file for reading." << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name, accountNumber, password;
        int balance;
        getline(ss, name, ',');
        getline(ss, accountNumber, ',');
        getline(ss, password, ',');
        ss >> balance;
        addAccount(name, accountNumber, password, balance);
    }
}

void Bank::clearAccounts()
{
    while (head != nullptr)
    {
        AccountNode *temp = head;
        head = head->next;
        delete temp;
    }
}

void Bank::addAccount(string name, string accountNumber, string password, int balance)
{
    AccountNode *newNode = new AccountNode(name, accountNumber, password, balance);
    newNode->next = head;
    head = newNode;
    bst.insert(name, accountNumber, password, balance);
    saveAccounts();
}

void Bank::deleteAccount(string accountNumber)
{
    AccountNode *temp = head;
    AccountNode *prev = nullptr;
    while (temp != nullptr && temp->accountNumber != accountNumber)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        cout << "Account not found!" << endl;
        return;
    }
    if (prev == nullptr)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }
    delete temp;
    saveAccounts();
}

void Bank::displayAllAccounts()
{
    AccountNode *temp = head;
    if (temp == nullptr)
    {
        cout << "No Accounts Found!" << endl;
        return;
    }
    while (temp != nullptr)
    {
        cout << "----------------------------" << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Account Number: " << temp->accountNumber << endl;
        cout << "Balance: $" << temp->balance << endl;
        cout << "----------------------------" << endl;
        temp = temp->next;
    }
}

void Bank::getSortedAccounts()
{
    bst.displayInOrder();
}

void Bank::showBalance(string accountNo, string password)
{
    AccountNode *temp = head;
    while (temp != nullptr)
    {
        if (temp->accountNumber == accountNo && temp->password == password)
        {
            cout << "Your Balance is: $" << temp->balance << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Account not found or incorrect password!" << endl;
}

void Bank::deposit(string accountNo, string password, int amount)
{
    AccountNode *temp = head;
    while (temp != nullptr)
    {
        if (temp->accountNumber == accountNo && temp->password == password)
        {
            temp->balance += amount;
            saveAccounts();
            historyStack.push(temp->accountNumber, amount, "Deposit", getCurrentTimestamp());
            cout << "Deposit successful! New Balance: $" << temp->balance << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Account not found or incorrect password!" << endl;
}

void Bank::withdraw(string accountNo, string password, int amount)
{
    AccountNode *temp = head;
    while (temp != nullptr)
    {
        if (temp->accountNumber == accountNo && temp->password == password)
        {
            if (temp->balance < amount)
            {
                cout << "Insufficient balance!" << endl;
                return;
            }
            temp->balance -= amount;
            historyStack.push(temp->accountNumber, amount, "Withdrawal", getCurrentTimestamp());
            saveAccounts();
            cout << "Withdrawal successful! New Balance: $" << temp->balance << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Account not found or incorrect password!" << endl;
}

void Bank::modifyAccount(string accountNo, string password)
{
    AccountNode *temp = head;
    while (temp != nullptr)
    {
        if (temp->accountNumber == accountNo && temp->password == password)
        {
            cout << "Enter new name: ";
            string newName;
            cin.ignore();
            getline(cin, newName);
            cout << "Enter new password: ";
            string newPassword;
            cin >> newPassword;
            temp->name = newName;
            temp->password = newPassword;
            saveAccounts();
            cout << "Account modified successfully!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Account not found or incorrect password!" << endl;
}

void Bank::getTransactionHistory(string accountNumber, string password)
{
    // Implementation depends on TransactionStack
    historyStack.displayRecord(accountNumber);
}

void Bank::deleteEverything()
{
    clearAccounts();
    historyStack.deleteEverything();
}
