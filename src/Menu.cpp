// Menu.cpp
// Handles all user interface and menu logic for the Bank Management System.
// Provides role-based menu navigation and user/admin operations.

#include "Menu.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
using namespace std;

// Create a new bank account (Admin only)
void createAccount(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    string name, accountNumber, password;
    int bal;
    cout << "----------------------------" << endl;
    cout << "-      Create Account      -" << endl;
    cout << "----------------------------" << endl;
    cin.ignore();
    // Input validation for name (not empty)
    do {
        cout << "Enter Account Holder's Name:" << endl;
        getline(cin, name);
        if (name.empty()) {
            cout << "Name cannot be empty. Please enter a valid name." << endl;
        }
    } while (name.empty());

    // Input validation for password (at least 6 characters)
    do {
        cout << "Set Password (at least 6 characters):" << endl;
        cin >> password;
        if (password.length() < 6) {
            cout << "Password must be at least 6 characters long. Please try again." << endl;
        }
    } while (password.length() < 6);

    // Input validation for initial balance
    cout << "Enter Initial Balance:" << endl;
    cin >> bal;
    if (cin.fail() || bal < 0) {
        cout << "Invalid balance entered. Setting initial balance to $0." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        bal = 0;
    }
    accountNumber = generateAccountNumber();
    bank.addAccount(name, accountNumber, password, bal);
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-      Create Account      -" << endl;
    cout << "----------------------------" << endl;
    cout << "----------------------------" << endl;
    cout << "Name : " << name << endl;
    cout << "Account Number : " << accountNumber << endl;
    cout << "Password: " << password << endl;
    cout << "Balance : $" << bal << endl;
    cout << "----------------------------" << endl;
    cout << endl;
    cout << "Account Created Successfully!" << endl;
}

// Modify an existing account (Admin only)
void modifyAccount(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-      Modify Account      -" << endl;
    cout << "----------------------------" << endl;
    string accountNumber, password;
    cout << "Enter Account Number:" << endl;
    cin >> accountNumber;
    cout << "Enter Password:" << endl;
    cin >> password;
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-      Modify Account      -" << endl;
    cout << "----------------------------" << endl;
    bank.modifyAccount(accountNumber, password);
}

// Delete an account (Admin only)
void deleteAccount(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-      Delete Account      -" << endl;
    cout << "----------------------------" << endl;
    string accountNumber;
    cout << "Enter Account Number to Delete:" << endl;
    cin >> accountNumber;
    bank.deleteAccount(accountNumber);
}

// Display all accounts data (Admin only)
void accountsData(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-      Accounts Data       -" << endl;
    cout << "----------------------------" << endl;
    bank.displayAllAccounts();
}

// Show balance for a specific account (User only)
void balanceInquiry(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-      Balance Inquiry     -" << endl;
    cout << "----------------------------" << endl;
    string accountNumber, password;
    cout << "Enter Account Number:" << endl;
    cin >> accountNumber;
    cout << "Enter Password:" << endl;
    cin >> password;
    bank.showBalance(accountNumber, password);
}

// Deposit money into an account (User only)
void deposit(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-         Deposit          -" << endl;
    cout << "----------------------------" << endl;
    string accountNumber, password;
    int amount;
    cout << "Enter Account Number:" << endl;
    cin >> accountNumber;
    cout << "Enter Password:" << endl;
    cin >> password;
    cout << "Enter Amount to Deposit:" << endl;
    cin >> amount;
    if (amount < 0) {
        cout << "Invalid Amount!" << endl;
        to_Menu(bank, role);
        return;
    }
    bank.deposit(accountNumber, password, amount);
}

// Withdraw money from an account (User only)
void withdraw(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-         Withdraw         -" << endl;
    cout << "----------------------------" << endl;
    string accountNumber, password;
    int amount;
    cout << "Enter Account Number:" << endl;
    cin >> accountNumber;
    cout << "Enter Password:" << endl;
    cin >> password;
    cout << "Enter Amount to Withdraw:" << endl;
    cin >> amount;
    if (amount < 0) {
        cout << "Invalid Amount!" << endl;
        return;
    }
    bank.withdraw(accountNumber, password, amount);
}

// Display transaction history for an account (User only)
void transactionHistory(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-    Transaction History   -" << endl;
    cout << "----------------------------" << endl;
    string accountNumber, password;
    cout << "Enter Account Number:" << endl;
    cin >> accountNumber;
    cout << "Enter Password:" << endl;
    cin >> password;
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-    Transaction History   -" << endl;
    cout << "----------------------------" << endl;
    bank.getTransactionHistory(accountNumber, password);
}

// Display all accounts sorted alphabetically (Admin only)
void SortedAccounts(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-      Sorted Accounts     -" << endl;
    cout << "----------------------------" << endl;
    bank.getSortedAccounts();
}

// Custom exit function to clean up and exit the program
int CustomExit(Bank &bank) {
    cout << "Thank you for using the Bank Management System!" << endl;
    cout << "We hope to see you again soon." << endl;
    cout << "Have a wonderful day! Goodbye!" << endl;
    cout << "------------------------------------------------" << endl;
    bank.deleteEverything();
    exit(0);
}

// Handles login and returns the user role (Admin/User)
UserRole Login(Bank &bank) {
    ClearScreen();
    header();
    cout << "----------------------------" << endl;
    cout << "-          Log In          -" << endl;
    cout << "----------------------------" << endl;
    cout << "Login as: " << endl;
    cout << "1. Admin" << endl;
    cout << "2. User" << endl;
    cout << "Enter choice: ";
    string choice;
    cin >> choice;
    if (choice == "1") {
        cout << "Enter Admin Password: ";
        string password;
        cin >> password;
        if (password == ADMIN_PASSWORD) {
            cout << "Welcome Admin!" << endl;
            return UserRole::Admin;
        } else {
            cout << "Invalid Password!" << endl;
            exit(0);
        }
    } else if (choice == "2") {
        cout << "Welcome User!" << endl;
        return UserRole::User;
    } else {
        cout << "Invalid choice! Exiting..." << endl;
        exit(0);
    }
    return UserRole::None;
}

// Main menu display and navigation based on user role
void displayMenu(Bank &bank, UserRole role) {
    ClearScreen();
    header();
    string ch;
    int choice;
    while (true) {
        cout << "-----------------" << endl;
        cout << "Select An Option:" << endl;
        cout << "-----------------" << endl;
        if (role == UserRole::Admin) {
            cout << "1 - Create Account." << endl;
            cout << "2 - Modify Account." << endl;
            cout << "3 - Delete Account." << endl;
            cout << "4 - View Accounts Data." << endl;
            cout << "5 - List All Accounts Alphabetically." << endl;
            cout << "6 - Exit." << endl;
        } else if (role == UserRole::User) {
            cout << "1 - Balance Inquiry." << endl;
            cout << "2 - Deposit." << endl;
            cout << "3 - Withdraw." << endl;
            cout << "4 - Transaction History." << endl;
            cout << "5 - Exit." << endl;
        }
        cout << "-----------------" << endl;
        cout << "Enter your choice: " << endl;
        cin >> ch;
        stringstream ss(ch);
        ss >> choice;
        if (role == UserRole::Admin) {
            switch (choice) {
                case 1:
                    createAccount(bank, role);
                    to_Menu(bank, role);
                    break;
                case 2:
                    modifyAccount(bank, role);
                    to_Menu(bank, role);
                    break;
                case 3:
                    deleteAccount(bank, role);
                    to_Menu(bank, role);
                    break;
                case 4:
                    accountsData(bank, role);
                    to_Menu(bank, role);
                    break;
                case 5:
                    SortedAccounts(bank, role);
                    to_Menu(bank, role);
                    break;
                case 6:
                    CustomExit(bank);
                    break;
                default:
                    ClearScreen();
                    header();
                    cout << endl;
                    cout << "Invalid choice. Please choose a valid option!" << endl;
                    to_Menu(bank, role);
            }
        } else if (role == UserRole::User) {
            switch (choice) {
                case 1:
                    balanceInquiry(bank, role);
                    to_Menu(bank, role);
                    break;
                case 2:
                    deposit(bank, role);
                    to_Menu(bank, role);
                    break;
                case 3:
                    withdraw(bank, role);
                    to_Menu(bank, role);
                    break;
                case 4:
                    transactionHistory(bank, role);
                    to_Menu(bank, role);
                    break;
                case 5:
                    CustomExit(bank);
                    break;
                default:
                    ClearScreen();
                    header();
                    cout << endl;
                    cout << "Invalid choice. Please choose a valid option!" << endl;
                    to_Menu(bank, role);
            }
        }
    }
}

// Helper function to return to menu or exit
void to_Menu(Bank &bank, UserRole role) {
    string choice;
    cout << "\nPress 1 for menu or any key to exit...!" << endl;
    cin >> choice;
    if (choice == "1") {
        displayMenu(bank, role);
    } else {
        CustomExit(bank);
    }
}
