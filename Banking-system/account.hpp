#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;


class Account {
private:
    string name;
    int id;
    double balance;
    vector<Transaction> transactionHistory;

public:
// Constructor
    Account(const string& n, int i, double b)
        : name(n), id(i), balance(b) {}

    // Deposit function
    void deposit(double amount) {
        balance += amount;
        transactionHistory.push_back(Transaction("Deposit", amount, getCurrentDate()));
        cout << "Successfully deposited $" << amount << endl;
    }

    // Display account info
    void displayInfo() const {
        cout << "Name: " << name << "\nID: " << id << "\nBalance: $" << balance << endl;
    }

    // Return account ID
    int getId() const { return id; }

    // Convert account to string (for saving to file)
    string toString() const {
        return name + " " + to_string(id) + " " + to_string(balance);
    }
    
};