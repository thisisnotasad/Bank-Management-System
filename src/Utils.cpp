// Utils.cpp
// Implements utility functions for the Bank Management System (timestamp, account number generation, etc.)

#include "Utils.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

string getCurrentTimestamp() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return string(buffer);
}

string generateAccountNumber(int length) {
    string Number;
    stringstream ss;
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < length; ++i) {
        int digit = rand() % 10;
        ss << digit;
    }
    Number = ss.str();
    return Number;
}

void ClearScreen() {
    system("cls");
}

void header() {
    string header_message = "---------------------------------------\n-         BANK MANAGEMENT SYSTEM      -\n---------------------------------------";
    cout << header_message << endl;
}

bool confirmation() {
    ClearScreen();
    header();
    string admin;
    cout << "Are you sure? (y/n): ";
    cin >> admin;
    return (admin == "y" || admin == "Y");
}
