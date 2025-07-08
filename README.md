# Bank Management System  

![C++](https://img.shields.io/badge/C++-17-blue.svg) 
![License](https://img.shields.io/badge/License-MIT-green.svg)  
*A modular, role-based banking system with data persistence, built with C++ and data structures.*

---

## 📌 Features  
- **Role-based access control**  
  - **Admin**: Create/modify/delete accounts, view all data.  
  - **User**: Deposit/withdraw funds, check balance, view transaction history.  
- **Data persistence**  
  - Accounts and transactions saved to `accounts.txt` and `transactions.txt`.  
- **Efficient data structures**  
  - **Linked List** for account management.  
  - **BST** for sorted account display (by name).  
  - **Stack** for LIFO transaction history.  
- **Input validation**  
  - Password length, negative balances, and invalid choices handled.  

---

## 🛠️ Build & Run  
### **Prerequisites**  
- C++17 compiler (e.g., `g++` on Linux, MinGW on Windows).  

### **Steps**  
1. **Clone the repo**  
   ```bash
   git clone https://github.com/thisisnotasad/Bank-Management-System.git
   cd Bank-Management-System
   ```

2. **Compile**  
   ```bash
   g++ src/*.cpp -o output/Main -std=c++17
   ```

3. **Run**  
   ```bash
   ./output/Main      # Linux/Mac
   output\Main.exe    # Windows
   ```

---

## 📂 Project Structure  
```plaintext
Bank-Management-System/
├── src/                  # Source files
│   ├── AccountNode.h/cpp     # Linked list node for accounts
│   ├── AccountsBST.h/cpp     # BST for sorted accounts
│   ├── Bank.h/cpp            # Core banking logic
│   ├── Menu.h/cpp            # Role-based UI menus
│   ├── TransactionStack.h/cpp # Stack for transaction history
│   ├── Utils.h/cpp           # Utilities (timestamp, etc.)
│   └── Main.cpp              # Entry point
├── data/                 # Sample data (gitignored)
│   ├── accounts_sample.txt
│   └── transactions_sample.txt
├── output/               # Build output (gitignored)
├── accounts.txt          # Runtime account data (gitignored)
├── transactions.txt      # Runtime transaction data (gitignored)
├── .gitignore           # Ignores binaries/sensitive files
└── README.md            # Project Documentation
```

---

## 🖥️ Usage  
1. **Login**  
   - Choose **Admin** (password: `1234`) or **User**.  

2. **Admin Menu**  
   - Create/delete accounts.  
   - View all accounts (raw or sorted).  

3. **User Menu**  
   - Deposit/withdraw funds.  
   - Check balance or transaction history.  

---

## 🔒 Security Notes  
- **Passwords are stored in plaintext** (for simplicity).  
  *For real-world use, implement hashing (e.g., SHA-256).*  
- **`accounts.txt` and `transactions.txt` are gitignored** to avoid leaking sensitive data.  

---

## License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---
