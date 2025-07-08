// AccountsBST.h
// Declares the AccountsBST class for managing accounts using a binary search tree.

#pragma once
#include <string>

using namespace std;

class AccountTreeNode {
public:
    string name;
    string accountNumber;
    string password;
    int balance;
    AccountTreeNode* left;
    AccountTreeNode* right;
    AccountTreeNode(string name, string accountNumber, string password, int balance);
};

class AccountsBST {
private:
    AccountTreeNode* root;
    AccountTreeNode* insertAccount(AccountTreeNode* node, string name, string accountNumber, string password, int balance);
    void inOrderTraversal(AccountTreeNode* node);
    AccountTreeNode* deleteBST(AccountTreeNode* node, string name);
    AccountTreeNode* minValueNode(AccountTreeNode* node);
    AccountTreeNode* searchBST(AccountTreeNode* node, string name);
public:
    AccountsBST();
    void insert(string name, string accountNumber, string password, int balance);
    void displayInOrder();
    void removeAccount(string name);
    void searchAccount(string name);
    void modifyAccount(string& name, string newName, string newAccountNumber, string newPassword);
};
