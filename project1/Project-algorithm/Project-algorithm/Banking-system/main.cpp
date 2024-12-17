#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "function.hpp"
using namespace std;
// Function declarations
void loadAccounts(vector<Account>& accounts, const string& filename);
void saveAccounts(const vector<Account>& accounts, const string& filename);
void createAccount(vector<Account>& accounts, const string& filename);
int main(){
    vector<Account> accounts;
    string filename = "accounts.txt";
    // Load accounts from the file
    loadAccounts(accounts, filename);
    // createAccount(accounts, filename);
    char choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Create a new account\n";
        cout << "2. Display all accounts\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                createAccount(accounts, filename);
                break;
            case '2':
                cout << "Account List:\n";
                for (const auto& acc : accounts) {
                    acc.displayInfo();
                }
                break;
            case '3':
                cout << "Exiting...\n";
                saveAccounts(accounts, filename);  // Save before exiting
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
#ddfd
    return 0;

}