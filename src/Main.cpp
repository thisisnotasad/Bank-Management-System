// Main.cpp
// Entry point for the Bank Management System. Initializes the bank and starts the menu system.

#include "Bank.h"
#include "Menu.h"
using namespace std;

int main() {
    Bank bank;
    UserRole role = Login(bank);
    displayMenu(bank, role);
    return 0;
}
