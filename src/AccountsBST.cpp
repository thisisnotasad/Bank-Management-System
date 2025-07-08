// AccountsBST.cpp
// Implements the AccountsBST class for managing accounts using a binary search tree.

#include "AccountsBST.h"
#include <iostream>
using namespace std;

AccountTreeNode::AccountTreeNode(string name, string accountNumber, string password, int balance)
{
    this->name = name;
    this->accountNumber = accountNumber;
    this->password = password;
    this->balance = balance;
    this->left = nullptr;
    this->right = nullptr;
}

AccountsBST::AccountsBST() : root(nullptr) {}

AccountTreeNode *AccountsBST::insertAccount(AccountTreeNode *node, string name, string accountNumber, string password, int balance)
{
    if (node == nullptr)
    {
        return new AccountTreeNode(name, accountNumber, password, balance);
    }
    if (name < node->name)
    {
        node->left = insertAccount(node->left, name, accountNumber, password, balance);
    }
    else if (name > node->name)
    {
        node->right = insertAccount(node->right, name, accountNumber, password, balance);
    }
    return node;
}

void AccountsBST::insert(string name, string accountNumber, string password, int balance)
{
    root = insertAccount(root, name, accountNumber, password, balance);
}

void AccountsBST::inOrderTraversal(AccountTreeNode *node)
{
    if (node != nullptr)
    {
        inOrderTraversal(node->left);
        cout << "----------------------------" << endl;
        cout << "Name: " << node->name << endl;
        cout << "Account Number: " << node->accountNumber << endl;
        cout << "Balance: $" << node->balance << endl;
        cout << "----------------------------" << endl;
        inOrderTraversal(node->right);
    }
}

void AccountsBST::displayInOrder()
{
    if (root == nullptr)
    {
        cout << "No Accounts Found!" << endl;
        return;
    }
    inOrderTraversal(root);
}

AccountTreeNode *AccountsBST::deleteBST(AccountTreeNode *node, string name)
{
    if (node == nullptr)
        return node;
    if (name < node->name)
    {
        node->left = deleteBST(node->left, name);
    }
    else if (name > node->name)
    {
        node->right = deleteBST(node->right, name);
    }
    else
    {
        if (node->left == nullptr)
        {
            AccountTreeNode *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            AccountTreeNode *temp = node->left;
            delete node;
            return temp;
        }
        AccountTreeNode *temp = minValueNode(node->right);
        node->name = temp->name;
        node->accountNumber = temp->accountNumber;
        node->password = temp->password;
        node->balance = temp->balance;
        node->right = deleteBST(node->right, temp->name);
    }
    return node;
}

AccountTreeNode *AccountsBST::minValueNode(AccountTreeNode *node)
{
    AccountTreeNode *current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

AccountTreeNode *AccountsBST::searchBST(AccountTreeNode *node, string name)
{
    if (node == nullptr || node->name == name)
        return node;
    if (name < node->name)
        return searchBST(node->left, name);
    else
        return searchBST(node->right, name);
}

void AccountsBST::removeAccount(string name)
{
    if (searchBST(root, name) == nullptr)
    {
        cout << "Account not found!" << endl;
    }
    else
    {
        root = deleteBST(root, name);
    }
}

void AccountsBST::searchAccount(string name)
{
    AccountTreeNode *foundAccount = searchBST(root, name);
    if (foundAccount)
    {
        cout << "Account Found: " << endl;
        cout << "Name: " << foundAccount->name << endl;
        cout << "Account Number: " << foundAccount->accountNumber << endl;
        cout << "Balance: $" << foundAccount->balance << endl;
    }
    else
    {
        cout << "Account not found!" << endl;
    }
}

void AccountsBST::modifyAccount(string &name, string newName, string newAccountNumber, string newPassword)
{
    AccountTreeNode *foundAccount = searchBST(root, name);
    if (foundAccount)
    {
        foundAccount->name = newName;
        foundAccount->accountNumber = newAccountNumber;
        foundAccount->password = newPassword;
    }
    else
    {
        cout << "Account not found!" << endl;
    }
}
