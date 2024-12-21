#include<string>
#include<vector>
#include<fstream>
#include "account.hpp"
#include "history.hpp"

using namespace std;

// Function to display the menu
void displayMenu() {
    cout << "\n==== Bank Account Management ====\n";
    cout << "1. Create a new account\n";
    cout << "2. Deposit amount into an account \n";
    cout << "3. withdraw amount from the account. \n";
    cout << "4. transfer amount from an account to another account\n";
    cout << "5. delete an account\n";
    cout << "6. Display account information\n";
    cout << "7. View history\n";
    cout << "8. exit the program\n";
    cout << "Please select an option(function) from 1 to 8 (1->8): ";
}

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
void createAccount(vector<Account>& accounts, const string& filename, HistoryList& history) {
    string name;
    double amount;
    int id = accounts.empty() ? 1 : accounts.back().getId() + 1; // Assign the next ID

    cout << "Enter name: ";
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, name);
    cout << "Enter initial deposit amount: ";
    cin >> amount;

    accounts.emplace_back(name, id, amount); // Create the account
    cout << "Account created successfully!\n";
    cout << "Assigned Account ID: " << id << "\n";
    accounts.back().displayInfo(); // Display the new account info
    history.logHistory("Created account: " + name + " with ID: " + to_string(id) + " and initial amount: $" + to_string(amount));
    
    // Save the updated accounts to the file
    saveAccounts(accounts, filename);
}

// Deposit to a specific account
void handleDeposit(vector<Account>& accounts, const string& filename, HistoryList& history) {
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
            history.logHistory("Deposited $" + to_string(amount) + " to account ID: " + to_string(id));
            // Save updated accounts back to the file
            saveAccounts(accounts, filename);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account ID " << id << " not found.\n";
    }

}

//withdraw
void withdraw(vector<Account>& accounts, const string& filename, HistoryList& history) {
    int id;
    double amount;

    cout << "Enter your account ID: ";
    cin >> id;

    Account* accountToWithdraw = nullptr;
    for (auto& account : accounts) {
        if (account.getId() == id) {
            accountToWithdraw = &account;
            break;
        }
    }

    if (!accountToWithdraw) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Withdrawal amount must be positive.\n";
        return;
    }

    if (accountToWithdraw->withdraw(amount)) {
        cout << "Withdrawal successful!\n";
        history.logHistory("Withdrew $" + to_string(amount) + " from account ID: " + to_string(id));
        saveAccounts(accounts, filename); // Save the updated accounts to the file
    } else {
        cout << "Insufficient funds. Withdrawal failed.\n";
    }
}

// transfer
void Transfer(vector<Account>& accounts, const string& filename, HistoryList& history) {
    int idFrom, idTo;
    double amount;

    cout << "Enter your account ID: ";
    cin >> idFrom;

    Account* fromAccount = nullptr;
    for (auto& account : accounts) {
        if (account.getId() == idFrom) {
            fromAccount = &account;
            break;
        }
    }

    if (!fromAccount) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter the amount to transfer: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Transfer amount must be positive.\n";
        return;
    }

    cout << "Enter the ID of the account to transfer to: ";
    cin >> idTo;

    if (idFrom == idTo) {
        cout << "Cannot transfer to the same account. Please choose a different target account.\n";
        return;
    }

    Account* toAccount = nullptr;
    for (auto& account : accounts) {
        if (account.getId() == idTo) {
            toAccount = &account;
            break;
        }
    }

    if (!toAccount) {
        cout << "Target account not found!\n";
        return;
    }

    // Perform the transfer
    if (fromAccount->withdraw(amount)) {
        toAccount->deposit(amount);
        cout << "Transfer completed successfully!\n";

        // Log history
        history.logHistory("Transferred $" + to_string(amount) + 
                           " from account ID: " + to_string(idFrom) + 
                           " to account ID: " + to_string(idTo));

        // Save updated accounts
        saveAccounts(accounts, filename);
    } else {
        cout << "Insufficient funds in account ID: " << idFrom << ". Transfer failed.\n";
    }
}

// Delate account 
void deleteAccount(vector<Account>& accounts , const string& filename, HistoryList& history) {
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
