// Utils.h
// Utility functions for the Bank Management System (timestamp, account number generation, etc.)

#pragma once
#include <string>

using namespace std;

// Global constant for admin password
const string ADMIN_PASSWORD = "1234";

// Global constant for account number length
const int ACCOUNT_NUMBER_LENGTH = 8;

string getCurrentTimestamp();
string generateAccountNumber(int length = ACCOUNT_NUMBER_LENGTH);
void ClearScreen();
void header();
bool confirmation();
