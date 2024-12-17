#include<string>
#include<vector>
#include<fstream>
#include "account.hpp"

using namespace std;
// Load accounts from file
void loadAccounts(vector<Account>& accounts, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string name;
        int id;
        double amount;
        while (file >> name >> id >> amount) {
            accounts.emplace_back(name, id, amount);
        }
        file.close();
    } else {
        cout << "Error opening file. Starting with an empty account list.\n";
    }
}

// Save accounts to file
void saveAccounts(const vector<Account>& accounts, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& account : accounts) {
            file << account.toString() << "\n";
        }
        file.close();
    } else {
        cout << "Error saving accounts to file.\n";
    }
}

// Create a new account
void createAccount(vector<Account>& accounts, const string& filename) {
    string name;
    double amount;
    int id = accounts.empty() ? 1 : accounts.back().getId() + 1; // Assign the next ID

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter initial deposit amount: ";
    cin >> amount;

    accounts.emplace_back(name, id, amount); // Create the account
    cout << "Account created successfully!\n";
    cout << "Assigned Account ID: " << id << "\n";
    accounts.back().displayInfo(); // Display the new account info

    // Save the updated accounts to the file
    saveAccounts(accounts, filename);
}

// Deposit to a specific account
void handleDeposit(vector<Account>& accounts, const string& filename) {
    if (accounts.empty()) {
        cout << "No accounts to deposit into. Please create an account first.\n";
        return;
    }

    int id;
    double amount;

    cout << "Enter the Account ID to deposit into: ";
    cin >> id;

    // Find the account by ID
    bool found = false;
    for (auto& account : accounts) {
        if (account.getId() == id) {
            cout << "Enter the amount to deposit: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount. Deposit amount must be positive.\n";
                return;
            }

            account.deposit(amount);
            cout << "Deposit successful!\n";
            account.displayInfo();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account ID " << id << " not found.\n";
    }

    // Save updated accounts back to the file
    saveAccounts(accounts, filename);
}

// Deposit to all accounts
void depositAllAccounts(vector<Account>& accounts, const string& filename) {
    if (accounts.empty()) {
        cout << "No accounts to deposit into. Please create an account first.\n";
        return;
    }

    double amount;
    cout << "Enter the amount to deposit into each account: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Deposit amount must be positive.\n";
        return;
    }

    for (auto& account : accounts) {
        account.deposit(amount);
    }

    cout << "Successfully deposited $" << amount << " into all accounts.\n";

    // Save updated accounts back to the file
    saveAccounts(accounts, filename);
}
