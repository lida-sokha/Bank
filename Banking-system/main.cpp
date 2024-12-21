#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "function.hpp"

using namespace std;

int main() {
    vector<Account> accounts;
    string filename = "accounts.txt";
    HistoryList historyList;
    string historyFile = "history.txt";

    // Load accounts from the file to put in the vector
    loadAccounts(accounts, filename);
    historyList.loadHistoryFromFile(historyFile);

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cout<<"\n";
        switch (choice) {
            case 1:
                createAccount(accounts, filename,historyList);
                historyList.saveHistoryToFile(historyFile);
                break;
            case 2:
                handleDeposit(accounts, filename,historyList);
                historyList.saveHistoryToFile(historyFile);
                break;
            case 3:
                withdraw(accounts, filename,historyList);
                historyList.saveHistoryToFile(historyFile);
                break;
            case 4:
                Transfer(accounts, filename,historyList);
                historyList.saveHistoryToFile(historyFile);
                break;
            case 5:
                deleteAccount(accounts, filename,historyList);
                historyList.saveHistoryToFile(historyFile);
                break;
            case 6:
                displayAccountInfo(accounts);
                break;
            case 7:
                historyList.viewHistory();
                break;
            case 8:
                cout<<"Program exited";
                break;
            default:
                cout << "Invalid option. Please try again. The valid option has only the number from 1 to 8 \n";
        }
    } while (choice != 8);
    cout<<"\n\n";
    return 0;
}
