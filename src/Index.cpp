#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <stack>
#include <sstream>
#include <fstream>
#define passCode "1234"

using namespace std;

class AccountTreeNode
{
public:
	string name;
	string accountNumber;
	string password;
	int balance;
	AccountTreeNode *left;
	AccountTreeNode *right;

	AccountTreeNode(string name, string accountNumber, string password, int balance)
	{
		this->name = name;
		this->accountNumber = accountNumber;
		this->password = password;
		this->balance = balance;
		this->left = NULL;
		this->right = NULL;
	}
};

class AccountsBST
{
private:
	AccountTreeNode *root;

private:
	AccountTreeNode *insertAccount(AccountTreeNode *node, string name, string accountNumber, string password, int balance)
	{
		if (node == NULL)
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

	void inOrderTraversal(AccountTreeNode *node)
	{
		if (node != NULL)
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

	AccountTreeNode *deleteBST(AccountTreeNode *node, string name)
	{
		if (node == NULL)
		{
			return node;
		}

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
			if (node->left == NULL)
			{
				AccountTreeNode *temp = node->right;
				delete node;
				return temp;
			}
			else if (node->right == NULL)
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

	AccountTreeNode *minValueNode(AccountTreeNode *node)
	{
		AccountTreeNode *current = node;
		while (current && current->left != NULL)
		{
			current = current->left;
		}

		return current;
	}

	AccountTreeNode *searchBST(AccountTreeNode *node, string name)
	{
		if (node == NULL || node->name == name)
		{
			return node;
		}

		if (name < node->name)
		{
			return searchBST(node->left, name);
		}
		else
		{
			return searchBST(node->right, name);
		}
	}

public:
	AccountsBST() : root(NULL) {}

	void insert(string name, string accountNumber, string password, int balance)
	{
		root = insertAccount(root, name, accountNumber, password, balance);
	}

	void displayInOrder()
	{
		if (root == NULL)
		{
			cout << "No Accounts Found!" << endl;
			return;
		}
		inOrderTraversal(root);
	}

	void removeAccount(string name)
	{
		if (searchBST(root, name) == NULL)
		{
			cout << "Account not found!" << endl;
		}
		else
		{
			root = deleteBST(root, name);
		}
	}

	void searchAccount(string name)
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

	void modifyAccount(string &name, string newName, string newAccountNumber, string newPassword)
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
};

string getCurrentTimestamp()
{
	time_t now = time(0);

	tm *localTime = localtime(&now);

	char buffer[80];

	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

	return string(buffer);
}

class transactionNode
{
public:
	string id;
	int amount;
	string type;
	string timestamp;
	transactionNode *next;

	transactionNode(string id, int amount, string type, string time) : id(id), amount(amount), type(type), timestamp(time), next(NULL) {}
};

class TransactionStack
{
private:
	transactionNode *top;

	void saveTransactions()
	{
		ofstream file("transactions.txt");
		if (!file)
		{
			cout << "Error opening file for writing." << endl;
			return;
		}

		transactionNode *current = top;

		while (current != NULL)
		{
			file << current->id << ","
				 << current->amount << ","
				 << current->type << ","
				 << current->timestamp << endl;

			current = current->next;
		}

		file.close();
	}

	void loadTransactions()
	{
		ifstream file("transactions.txt");
		if (!file)
		{
			cout << "Error opening file for reading." << endl;
			return;
		}

		stack<transactionNode *> tempStack;

		string line;
		while (getline(file, line))
		{
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

		while (!tempStack.empty())
		{
			transactionNode *node = tempStack.top();
			push(node->id, node->amount, node->type, node->timestamp);
			delete node;
			tempStack.pop();
		}

		file.close();
	}

	void clearHistory()
	{
		while (top != NULL)
		{
			transactionNode *tempDel = top;
			top = top->next;
			delete tempDel;
		}
	}

public:
	TransactionStack() : top(NULL)
	{
		loadTransactions();
	}

	bool isEmpty()
	{
		return top == NULL;
	}

	void push(string id, int amount, string type, string timestamp)
	{
		transactionNode *newNode = new transactionNode(id, amount, type, timestamp);
		newNode->next = top;
		top = newNode;
		saveTransactions();
	}

	void pop()
	{
		if (isEmpty())
		{
			cout << "No transactions found!" << endl;
			return;
		}
		transactionNode *temp = top;
		top = top->next;
		delete temp;
		saveTransactions();
	}

	void displayStack()
	{
		if (isEmpty())
		{
			cout << "No transactions found!" << endl;
			return;
		}
		transactionNode *temp = top;
		cout << "Transaction History:" << endl;
		while (temp != NULL)
		{
			cout << "ID - " << temp->id << endl;
			cout << "Amount - $" << temp->amount << endl;
			cout << "Type - " << temp->type << endl;
			cout << "Timestamp - " << temp->timestamp << endl;
			temp = temp->next;
		}
	}

	void displayRecord(string id)
	{
		if (isEmpty())
		{
			cout << "No Transactions Found for Id - " << id << endl;
			return;
		}

		transactionNode *temp = top;
		bool found = false;

		cout << "Transaction History for Id " << id << ":" << endl;

		while (temp != NULL)
		{
			if (temp->id == id)
			{
				found = true;
				cout << "----------------------------" << endl;
				cout << "Amount - $" << temp->amount << endl;
				cout << "Type - " << temp->type << endl;
				cout << "Timestamp - " << temp->timestamp << endl;
				cout << "----------------------------" << endl;
			}

			temp = temp->next;
		}
		if (!found)
		{
			cout << "No Transactions Found for Id - " << id << endl;
		}
	}

	void peek()
	{
		if (isEmpty())
		{
			cout << "No transactions found!" << endl;
			return;
		}
		cout << "Top Transaction: ID: " << top->id << endl;
		cout << "Amount: $" << top->amount << endl;
		cout << "Type: " << top->type << endl;
		cout << "Timestamp: " << top->timestamp << endl;
	}

	void deleteTransactionsByID(string id)
	{
		while (top != NULL && top->id == id)
		{
			transactionNode *tempDel = top;
			top = top->next;
			delete tempDel;
		}

		transactionNode *current = top;

		while (current != NULL && current->next != NULL)
		{
			if (current->next->id == id)
			{
				transactionNode *temp = current->next;
				current->next = current->next->next;
				delete temp;
			}
			else
			{
				current = current->next;
			}
		}
		saveTransactions();
	}

	void deleteEverything()
	{
		clearHistory();
	}

	~TransactionStack()
	{
		clearHistory();
	}
};

class Bank;
void header();
void ClearScreen();
void to_Menu(Bank &bank);

class AccountNode
{
public:
	string name;
	string accountNumber;
	string password;

	int balance;
	AccountNode *next;
	AccountNode(string name, string accountNumber, string password, int balance)
	{
		this->name = name;
		this->accountNumber = accountNumber;
		this->password = password;
		this->balance = balance;
		this->next = NULL;
	}
};

class Bank
{
private:
	AccountNode *head;
	TransactionStack historyStack;
	AccountsBST bst;

	void saveAccounts()
	{
		ofstream file("accounts.txt");
		if (!file)
		{
			cout << "Error opening file for writing." << endl;
			return;
		}
		AccountNode *temp = head;
		while (temp != NULL)
		{
			file << temp->name << "," << temp->accountNumber << "," << temp->password << "," << temp->balance << endl;
			temp = temp->next;
		}
	}

	void loadAccounts()
	{
		ifstream file("accounts.txt");
		if (!file)
		{
			cout << "Error opening file for reading." << endl;
			return;
		}
		string line;
		while (getline(file, line))
		{
			stringstream ss(line);
			string name, accountNumber, password;
			int balance;
			getline(ss, name, ',');
			getline(ss, accountNumber, ',');
			getline(ss, password, ',');
			ss >> balance;
			addAccount(name, accountNumber, password, balance);
		}
	}

	void clearAccounts()
	{
		AccountNode *temp = head;
		while (temp != NULL)
		{
			AccountNode *next = temp->next;
			delete temp;
			temp = next;
		}
		historyStack.deleteEverything();
	}

public:
	Bank()
	{
		head = NULL;
		loadAccounts();
	}

	void addAccount(string name, string accountNumber, string password, int balance)
	{
		AccountNode *newNode = new AccountNode(name, accountNumber, password, balance);
		if (head == NULL)
		{
			head = newNode;
			bst.insert(name, accountNumber, password, balance);
			return;
		}
		AccountNode *temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
		bst.insert(name, accountNumber, password, balance);
		saveAccounts();
	}

	void deleteAccount(string accountNumber)
	{
		if (head == NULL)
		{
			cout << "No Accounts Found!" << endl;
			return;
		}

		AccountNode *temp = head;
		AccountNode *prev = head;
		while (temp != NULL)
		{
			if (accountNumber == temp->accountNumber)
			{
				cout << "Are you sure you want to delete this account? (y/n): " << endl;
				string confirm;
				cin >> confirm;
				if (confirm == "y" || confirm == "Y")
				{

					if (temp == head)
					{
						head = head->next;
						cout << "Account Deleted Successfully." << endl;
						bst.removeAccount(temp->name);
						historyStack.deleteTransactionsByID(accountNumber);
						delete temp;
						saveAccounts();
						return;
					}
					else
					{
						prev->next = temp->next;
						cout << "Account Deleted Successfully." << endl;
						bst.removeAccount(temp->name);
						historyStack.deleteTransactionsByID(accountNumber);
						delete temp;
						saveAccounts();
						return;
					}
				}
				else
				{
					cout << "Account Deletion Cancelled." << endl;
					return;
				}
			}
			prev = temp;
			temp = temp->next;
		}
		cout << "Account Not Found!" << endl;
	}

	void displayAllAccounts()
	{
		if (head == NULL)
		{
			cout << "No Accounts Found!" << endl;
			return;
		}
		AccountNode *temp = head;
		while (temp != NULL)
		{
			cout << "----------------------------" << endl;
			cout << "Name : " << temp->name << endl;
			cout << "Account Number : " << temp->accountNumber << endl;
			cout << "Balance : $" << temp->balance << endl;
			cout << "----------------------------" << endl;
			temp = temp->next;
		}
	}

	void getSortedAccounts()
	{
		bst.displayInOrder();
	}

	void showBalance(string accountNo, string password)
	{
		AccountNode *temp = head;
		while (temp != NULL)
		{
			if (temp->accountNumber == accountNo)
			{
				if (temp->password == password)
				{
					cout << "Your Current Balance is : $" << temp->balance << endl;
					return;
				}
				else
				{
					cout << "Incorrect Password!" << endl;
					return;
				}
			}

			temp = temp->next;
		}

		cout << "Account Not Found!" << endl;
	}

	void deposit(string accountNo, string password, int amount)
	{
		AccountNode *temp = head;
		while (temp != NULL)
		{
			if (temp->accountNumber == accountNo)
			{
				if (temp->password == password)
				{
					temp->balance += amount;
					cout << "Deposit Successful!" << endl;
					cout << "Your Current Balance is : $" << temp->balance << endl;
					historyStack.push(temp->accountNumber, amount, "Deposit", getCurrentTimestamp());
					saveAccounts();

					return;
				}
				else
				{
					cout << "Incorrect Password!" << endl;
					return;
				}
			}
			temp = temp->next;
		}
		cout << "Account Not Found!" << endl;
	}

	void withdraw(string accountNo, string password, int amount)
	{
		AccountNode *temp = head;
		while (temp != NULL)
		{
			if (temp->accountNumber == accountNo)
			{
				if (temp->password == password)
				{
					if (temp->balance >= amount)
					{
						temp->balance -= amount;
						cout << "Withdrawal Successful!" << endl;
						cout << "Your Current Balance is : $" << temp->balance << endl;
						historyStack.push(temp->accountNumber, amount, "Withdrawal", getCurrentTimestamp());
						saveAccounts();
						return;
					}
					else
					{
						cout << "Insufficient Balance!" << endl;
						return;
					}
				}
				else
				{
					cout << "Incorrect Password!" << endl;
					return;
				}
			}

			temp = temp->next;
		}
		cout << "Account Not Found!" << endl;
	}

	void modifyAccount(string accountNo, string password)
	{
		string newAccountNumber, newPassword, newName;
		AccountNode *temp = head;
		bool found = false;
		while (temp != NULL)
		{
			if (temp->accountNumber == accountNo)
			{
				if (temp->password == password)
				{
					found = true;
					cout << "What do you want to modify:" << endl;
					cout << "1. Name" << endl;
					cout << "2. Password" << endl;
					string choice;
					cin >> choice;
					if (choice == "1")
					{
						cout << "Enter New Name: " << endl;
						cin.ignore();
						getline(cin, newName);
						bst.modifyAccount(temp->name, newName, temp->accountNumber, temp->password);
						temp->name = newName;
						saveAccounts();
						cout << "Name Modified Successfully!" << endl;
						return;
					}
					else if (choice == "2")
					{
						cout << "Enter New Password: " << endl;
						cin >> newPassword;
						temp->password = newPassword;
						bst.modifyAccount(temp->name, temp->name, temp->accountNumber, newPassword);
						saveAccounts();
						cout << "Password Modified Successfully!" << endl;
						return;
					}
					else
					{
						cout << "Invalid Choice!" << endl;
						return;
					}
				}
				else
				{
					cout << "Incorrect Password!" << endl;
					return;
				}
			}
			temp = temp->next;
		}
		if (!found)
		{
			cout << "Account Not Found!" << endl;
		}
	}

	void getTransactionHistory(string accountNumber, string password)
	{
		AccountNode *temp = head;
		while (temp != NULL)
		{
			if (temp->accountNumber == accountNumber)
			{
				if (temp->password == password)
				{
					historyStack.displayRecord(accountNumber);
					return;
				}
				else
				{
					cout << "Incorrect Password!" << endl;
					return;
				}
			}
			temp = temp->next;
		}
		cout << "Account Not Found!" << endl;
	}

	void deleteEverything()
	{
		clearAccounts();
	}

	~Bank()
	{
		clearAccounts();
	}
};

bool confirmation()
{
	ClearScreen();
	header();
	string admin;
	cout << "----------------------------" << endl;
	cout << "-          Log In          -" << endl;
	cout << "----------------------------" << endl;
	cout << "Are You Administrator? (Y/N)" << endl;
	cin >> admin;
	if (admin == "Y" || admin == "y")
	{
		cout << "Enter Admin Password:" << endl;
		string password;
		cin >> password;
		if (password == passCode)
		{
			return true;
		}
		else
		{
			cout << "Invalid Password!" << endl;
			return false;
		}
	}
	else
	{
		cout << "You are not an Administrator!" << endl;
		return false;
	}
}

string generateAccountNumber(int length)
{
	string Number;
	stringstream ss;
	srand(static_cast<unsigned>(time(0)));

	for (int i = 0; i < length; ++i)
	{
		int digit = rand() % 10;
		ss << digit;
	}

	Number = ss.str();

	return Number;
}

void createAccount(Bank &bank)
{
	ClearScreen();
	header();

	string name, accountNumber, password;
	int bal;
	cout << "----------------------------" << endl;
	cout << "-      Create Account      -" << endl;
	cout << "----------------------------" << endl;
	cout << "Enter Account Holder's Name:" << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Set Password:" << endl;
	cin >> password;
	cout << "Enter Initial Balance:" << endl;
	cin >> bal;

	accountNumber = generateAccountNumber(8);

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

void modifyAccount(Bank &bank)
{
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

void deleteAccount(Bank &bank)
{
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

void accountsData(Bank &bank)
{
	ClearScreen();
	header();
	cout << "----------------------------" << endl;
	cout << "-      Accounts Data       -" << endl;
	cout << "----------------------------" << endl;

	bank.displayAllAccounts();
}

void balanceInquiry(Bank &bank)
{
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

void deposit(Bank &bank)
{
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
	if (amount < 0)
	{
		cout << "Invalid Amount!" << endl;
		to_Menu(bank);
		return;
	}
	bank.deposit(accountNumber, password, amount);
}

void withdraw(Bank &bank)
{
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
	if (amount < 0)
	{
		cout << "Invalid Amount!" << endl;
		return;
	}
	bank.withdraw(accountNumber, password, amount);
}

void transactionHistory(Bank &bank)
{
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

void SortedAccounts(Bank &bank)
{
	ClearScreen();
	header();
	cout << "----------------------------" << endl;
	cout << "-      Sorted Accounts     -" << endl;
	cout << "----------------------------" << endl;
	bank.getSortedAccounts();
}

int CustomExit(Bank &bank)
{
	cout << "Thank you for using the Bank Management System!" << endl;
	cout << "We hope to see you again soon." << endl;
	cout << "Have a wonderful day! Goodbye!" << endl;
	cout << "------------------------------------------------" << endl;

	bank.deleteEverything();

	exit(0);
}

void ClearScreen()
{
	system("cls");
}

void displayMenu(Bank &bank)
{
	ClearScreen();
	header();
	string ch;
	int choice;
	while (true)
	{

		cout << "-----------------" << endl;
		cout << "Select An Option:" << endl;
		cout << "-----------------" << endl;
		cout << "1 - Create Account." << endl;
		cout << "2 - Modify Account." << endl;
		cout << "3 - Delete Account." << endl;
		cout << "4 - View Accounts Data." << endl;
		cout << "5 - Balance Inquiry." << endl;
		cout << "6 - Deposit." << endl;
		cout << "7 - Withdraw." << endl;
		cout << "8 - Transaction History." << endl;
		cout << "9 - List All Accounts Alphabetically." << endl;
		cout << "10 - Exit." << endl;

		cout << "-----------------" << endl;
		cout << "Enter your choice: " << endl;
		cin >> ch;

		// choice = ch[0] - '0';
		stringstream ss(ch);
		ss >> choice;

		switch (choice)
		{
		case 1:
		{
			createAccount(bank);
			to_Menu(bank);
			break;
		}
		case 2:
		{
			modifyAccount(bank);
			to_Menu(bank);
			break;
		}
		case 3:
		{
			if (confirmation())
			{
				deleteAccount(bank);
			}
			to_Menu(bank);
			break;
		}
		case 4:
		{
			if (confirmation())
			{
				accountsData(bank);
			}
			to_Menu(bank);
			break;
		}
		case 5:
		{
			balanceInquiry(bank);
			to_Menu(bank);
			break;
		}
		case 6:
		{
			deposit(bank);
			to_Menu(bank);
			break;
		}
		case 7:
		{
			withdraw(bank);
			to_Menu(bank);
			break;
		}
		case 8:
		{
			transactionHistory(bank);
			to_Menu(bank);
			break;
		}
		case 9:
		{
			if (confirmation())
			{
				SortedAccounts(bank);
			}
			to_Menu(bank);
			break;
		}

		case 10:
		{
			CustomExit(bank);
			break;
		}
		default:
			ClearScreen();
			header();
			cout << endl;
			cout << "Invalid choice. Please choose a valid option!" << endl;
			to_Menu(bank);
		}
	}
}

void to_Menu(Bank &bank)
{
	string choice;
	cout << "\nPress 1 for menu or any key to exit...!" << endl;
	cin >> choice;
	if (choice == "1")
	{
		displayMenu(bank);
	}
	else
	{
		CustomExit(bank);
	}
}

void header()
{
	string header_message = "---------------------------------------\n-         BANK MANAGEMENT SYSTEM      -\n---------------------------------------";
	cout << header_message << endl;
}

int main()
{

	Bank bank;

	displayMenu(bank);

	return 0;
}
