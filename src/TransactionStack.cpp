// TransactionStack.cpp
// Implements the TransactionStack class for managing transaction history using a stack.

#include "TransactionStack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;

transactionNode::transactionNode(string id, int amount, string type, string time) : id(id), amount(amount), type(type), timestamp(time), next(nullptr) {}

TransactionStack::TransactionStack() : top(nullptr) {
    loadTransactions();
}

TransactionStack::~TransactionStack() {
    clearHistory();
}

void TransactionStack::saveTransactions() {
    ofstream file("transactions.txt");
    if (!file) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    transactionNode* current = top;
    while (current != nullptr) {
        file << current->id << "," << current->amount << "," << current->type << "," << current->timestamp << endl;
        current = current->next;
    }
}

void TransactionStack::loadTransactions() {
    ifstream file("transactions.txt");
    if (!file) {
        cout << "Error opening file for reading." << endl;
        return;
    }
    stack<transactionNode*> tempStack;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, type, timestamp;
        int amount;
        getline(ss, id, ',');
        ss >> amount;
        ss.ignore(1);
        getline(ss, type, ',');
        getline(ss, timestamp);
        tempStack.push(new transactionNode(id, amount, type, timestamp));
    }
    while (!tempStack.empty()) {
        transactionNode* node = tempStack.top();
        push(node->id, node->amount, node->type, node->timestamp);
        delete node;
        tempStack.pop();
    }
}

void TransactionStack::clearHistory() {
    while (top != nullptr) {
        transactionNode* tempDel = top;
        top = top->next;
        delete tempDel;
    }
}

bool TransactionStack::isEmpty() {
    return top == nullptr;
}

void TransactionStack::push(string id, int amount, string type, string timestamp) {
    transactionNode* newNode = new transactionNode(id, amount, type, timestamp);
    newNode->next = top;
    top = newNode;
    saveTransactions();
}

void TransactionStack::pop() {
    if (isEmpty()) {
        cout << "No transactions found!" << endl;
        return;
    }
    transactionNode* temp = top;
    top = top->next;
    delete temp;
    saveTransactions();
}

void TransactionStack::displayStack() {
    if (isEmpty()) {
        cout << "No transactions found!" << endl;
        return;
    }
    transactionNode* temp = top;
    cout << "Transaction History:" << endl;
    while (temp != nullptr) {
        cout << "ID - " << temp->id << endl;
        cout << "Amount - $" << temp->amount << endl;
        cout << "Type - " << temp->type << endl;
        cout << "Timestamp - " << temp->timestamp << endl;
        temp = temp->next;
    }
}

void TransactionStack::displayRecord(string id) {
    if (isEmpty()) {
        cout << "No Transactions Found for Id - " << id << endl;
        return;
    }
    transactionNode* temp = top;
    bool found = false;
    cout << "Transaction History for Id " << id << ":" << endl;
    while (temp != nullptr) {
        if (temp->id == id) {
            found = true;
            cout << "----------------------------" << endl;
            cout << "Amount - $" << temp->amount << endl;
            cout << "Type - " << temp->type << endl;
            cout << "Timestamp - " << temp->timestamp << endl;
            cout << "----------------------------" << endl;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "No Transactions Found for Id - " << id << endl;
    }
}

void TransactionStack::peek() {
    if (isEmpty()) {
        cout << "No transactions found!" << endl;
        return;
    }
    cout << "Top Transaction: ID: " << top->id << endl;
    cout << "Amount: $" << top->amount << endl;
    cout << "Type: " << top->type << endl;
    cout << "Timestamp: " << top->timestamp << endl;
}

void TransactionStack::deleteTransactionsByID(string id) {
    while (top != nullptr && top->id == id) {
        transactionNode* tempDel = top;
        top = top->next;
        delete tempDel;
    }
    transactionNode* current = top;
    while (current != nullptr && current->next != nullptr) {
        if (current->next->id == id) {
            transactionNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    saveTransactions();
}

void TransactionStack::deleteEverything() {
    clearHistory();
}
