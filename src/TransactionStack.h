// TransactionStack.h
// Declares the TransactionStack class for managing transaction history using a stack.

#pragma once
#include <string>

using namespace std;

class transactionNode {
public:
    string id;
    int amount;
    string type;
    string timestamp;
    transactionNode* next;
    transactionNode(string id, int amount, string type, string time);
};

class TransactionStack {
private:
    transactionNode* top;
    void saveTransactions();
    void loadTransactions();
    void clearHistory();
public:
    TransactionStack();
    ~TransactionStack();
    bool isEmpty();
    void push(string id, int amount, string type, string timestamp);
    void pop();
    void displayStack();
    void displayRecord(string id);
    void peek();
    void deleteTransactionsByID(string id);
    void deleteEverything();
};
