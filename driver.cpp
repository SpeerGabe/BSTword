#include "BST.h"
#include <iostream>
 
using namespace std;
 
void displayMenu() {
    cout << "\n--- BST Word Frequency Tool ---\n";
    cout << "1. Set a key-value pair\n";
    cout << "2. Find the count for a word\n";
    cout << "3. Print all entries (in-order)\n";
    cout << "4. Save entries to file\n";
    cout << "5. Find the minimum key\n";
    cout << "6. Find the maximum key\n";
    cout << "7. Remove a word\n";
    cout << "8. Read words from a text file\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
}
 
int main() {
    BST tree;
    int choice;
 
    do {
        displayMenu();
        cin >> choice;
 
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            choice = -1;
            continue;
        }
 
        switch (choice) {
            case 1: {
                string key;
                int value;
                cout << "Enter word: ";
                cin >> key;
                cout << "Enter count: ";
                cin >> value;
                tree.set(key, value);
                break;
            }
            case 2: {
                string key;
                cout << "Enter word: ";
                cin >> key;
                cout << "\"" << key << "\" appears " << tree.find(key) << " time(s).\n";
                break;
            }
            case 3:
                tree.print();
                break;
            case 4: {
                string filename;
                cout << "Enter output filename: ";
                cin >> filename;
                tree.saveToFile(filename);
                cout << "Saved to \"" << filename << "\".\n";
                break;
            }
            case 5:
                tree.min();
                break;
            case 6:
                tree.max();
                break;
            case 7: {
                string key;
                cout << "Enter word to remove: ";
                cin >> key;
                tree.remove(key);
                cout << "\"" << key << "\" removed.\n";
                break;
            }
            case 8: {
                string filename;
                cout << "Enter filename to read (.txt extension optional): ";
                cin >> filename;
                if (tree.readFromFile(filename)) {
                    cout << "Done. Use option 3 to print or 4 to save results.\n";
                }
                break;
            }
            case 0:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);
 
    return 0;
}
