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