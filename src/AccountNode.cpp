// AccountNode.cpp
// Implements the AccountNode class for linked list representation of accounts.

#include "AccountNode.h"
using namespace std;

AccountNode::AccountNode(string name, string accountNumber, string password, int balance) {
    this->name = name;
    this->accountNumber = accountNumber;
    this->password = password;
    this->balance = balance;
    this->next = nullptr;
}
