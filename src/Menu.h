// Menu.h
// Declares menu and UI functions for the Bank Management System.
// Provides role-based menu navigation and user/admin operations.

#pragma once
#include "Bank.h"

using namespace std;

enum class UserRole { None, Admin, User };
void createAccount(Bank &bank, UserRole role);
void modifyAccount(Bank &bank, UserRole role);
void deleteAccount(Bank &bank, UserRole role);
void accountsData(Bank &bank, UserRole role);
void balanceInquiry(Bank &bank, UserRole role);
void deposit(Bank &bank, UserRole role);
void withdraw(Bank &bank, UserRole role);
void transactionHistory(Bank &bank, UserRole role);
void SortedAccounts(Bank &bank, UserRole role);
void displayMenu(Bank &bank, UserRole role);
void to_Menu(Bank &bank, UserRole role);
UserRole Login(Bank &bank);
