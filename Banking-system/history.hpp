#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Node structure for the linked list to manage history
struct HistoryNode {
    string history;         
    HistoryNode* next;     
};

// LinkedList class for managing history
class HistoryList {
private:
    HistoryNode* head;  // Head of the linked list

public:
    HistoryList() : head(nullptr) {}  // Constructor initializes the head to nullptr

    // Insert history at the beginning of the linked list
    void logHistory(const string& history) {
        HistoryNode* newNode = new HistoryNode();  // Create a new node
        newNode->history = history;  // Set the history text
        newNode->next = head;  // Link the new node to the current head
        head = newNode;  // Update the head to the new node
    }

    void viewHistory() const {
        HistoryNode* current = head;
        if (!current) {
            cout << "No history available.\n";
            return;
        }

        cout << "------------------ History ------------------\n";
        while (current != nullptr) {
            cout << current->history << endl;
            current = current->next;
        }
        cout<<"---------------------------------------------\n";
    }
    // Save history to a file
    void saveHistoryToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            HistoryNode* current = head;
            while (current != nullptr) {
                file << current->history << "\n";  // Write each history to the file
                current = current->next;
            }
            file.close();
        } else {
            cout << "Error saving history to file.\n";
        }
    }

    // Load history from a file and insert it at the top of the list
    // Load history from a file and insert it at the tail of the list
void loadHistoryFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // Insert at the tail of the list
            if (head == nullptr) {
                logHistory(line);  // If the list is empty, just insert at the head
            } else {
                // Traverse to the last node
                HistoryNode* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                // Insert the new history at the tail
                HistoryNode* newNode = new HistoryNode();
                newNode->history = line;
                newNode->next = nullptr;
                current->next = newNode;  // Link the last node to the new node
            }
        }
        file.close();
    } else {
        cout << "Error loading history from file.\n";
    }
}


    // Destructor to free memory
    ~HistoryList() {
        HistoryNode* current = head;
        while (current != nullptr) {
            HistoryNode* temp = current;
            current = current->next;
            delete temp;  // Delete each node
        }
    }
};