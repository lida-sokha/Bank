#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Account {
private:
    string name;
    int id;
    double amount;

public:
    Account(string name, int id, double amount) : name(name), id(id), amount(amount) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getAmount() const { return amount; }

    void deposit(double amount) { this->amount += amount; }
    bool withdraw(double amount) {
        if (amount > this->amount) {
            cout << "Insufficient funds.\n";
            return false;
        }
        this->amount -= amount;
        return true;
    }
    void displayInfo() const {
        cout << "Name: " << name << "\nID: " << id << "\nAmount: $" << amount << "\n";
    }

    string toString() const {
        return name + " " + to_string(id) + " " + to_string(amount);
    }
};