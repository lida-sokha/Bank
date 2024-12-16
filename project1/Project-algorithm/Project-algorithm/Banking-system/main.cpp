#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "function.hpp"
using namespace std;
int main(){
    vector<Account> accounts;
    string filename = "accounts.txt";
    // Load accounts from the file
    loadAccounts(accounts, filename);
    // createAccount(accounts, filename);
}