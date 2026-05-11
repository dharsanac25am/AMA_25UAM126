# Bank Account Management System

## Description
This project is a simple **Bank Account Management System** developed using the **C programming language**.  
It uses **binary file handling** to store customer account details securely in a file named `credit.dat`.

The program is menu-driven and allows users to:
- Add new accounts
- Update account balances
- Delete accounts
- Display all account details
- Generate a text file report

---

# Features

## 1. Add New Account
Users can create a new bank account by entering:
- Account Number
- Last Name
- First Name
- Balance

## 2. Update Account
Allows:
- Deposit money
- Withdraw money

## 3. Delete Account
Removes an existing account record from the file.

## 4. List All Accounts
Displays all customer account details stored in the file.

## 5. Generate Text File
Creates a readable text file named `accounts.txt`.

---

# Technologies Used

- C Programming
- Structures
- Functions
- File Handling
- Binary Files
- Menu Driven Programming

---

# Structure Used

```c
struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
};