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
// Display account information
void displayAccountInfo(const vector<Account>& accounts) {
    int choice;
    cout << "1. Display specific account\n2. Display all accounts\nChoose an option: ";
    cin >> choice;

    if (choice == 1) {
        int id;
        cout << "Enter account ID: ";
        cin >> id;

        for (const auto& account : accounts) {
            if (account.getId() == id) {
                account.displayInfo();
                return;
            }
        }
        cout << "Account not found.\n";
    } else if (choice == 2) {
        for (const auto& account : accounts) {
            account.displayInfo();
            cout << "------------------\n";
        }
    } else {
        cout << "Invalid option.\n";
    }
}

// Delate account 
void deleteAccount(vector<Account>& accounts , const string& filename) {
    int id;
    char decision;
    cout << "Enter account ID to delete: ";
    cin >> id;

    for (auto acc = accounts.begin(); acc != accounts.end(); ++acc) {
        if (acc->getId() == id) {
            cout << "Deleting the following account:\n";
            acc->displayInfo();
            cout<<"Are you sure that you want to delete this account\n";
            cout<<"Yes(Y or y) or No(N or n):";
            cin>>decision;
            if(decision=='y' || decision=='Y'){
                accounts.erase(acc);
                cout << "Account deleted successfully.\n";  
            }
            else{
                return;
            }
            return;
        }
    }
    cout << "Account not found.\n";
}