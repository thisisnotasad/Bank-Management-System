// AccountNode.h
// Declares the AccountNode class for linked list representation of accounts.

#pragma once
#include <string>

using namespace std;

class AccountNode {
public:
    string name;
    string accountNumber;
    string password;
    int balance;
    AccountNode* next;
    AccountNode(string name, string accountNumber, string password, int balance);
};
