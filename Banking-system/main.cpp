#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "function.hpp"

using namespace std;

// Function to display the menu
void displayMenu() {
    cout << "\n==== Bank Account Management ====\n";
    cout << "1. Create a new account\n";
    cout << "2. View all accounts\n";
    cout << "3. Deposit money into an account\n";
    cout << "4. Exit\n";
    cout << "Select an option: ";
}

// Function to display all accounts
void displayAllAccounts(const vector<Account>& accounts) {
    cout << "\nList of Accounts:\n";
    if (accounts.empty()) {
        cout << "No accounts available.\n";
        return;
    }

    for (const auto& account : accounts) {
        account.displayInfo();
        cout << "--------------------------\n";
    }
}

int main() {
    vector<Account> accounts;
    string filename = "accounts.txt";

    // Load accounts from the file
    loadAccounts(accounts, filename);

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount(accounts, filename);
                break;
            case 2:
                displayAllAccounts(accounts);
                break;
            case 3:
                handleDeposit(accounts, filename);
                break;

            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
