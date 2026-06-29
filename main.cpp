#include "account.h"
#include "BST.h"
#include "Sorting.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "HashTable.h"
using namespace std;

// ── Global array for sorting (mirrors the linked list accounts) ───────────────
#define MAX_ACCOUNTS 1000
Account globalAccount[MAX_ACCOUNTS];
int globalCount = 0;

// Rebuild globalAccount[] from the linked list
void rebuildGlobalArray(List *ls)
{
    globalCount = 0;
    Node *cur = ls->head;
    while (cur != nullptr && globalCount < MAX_ACCOUNTS)
    {
        if (cur->type == 0)
        { // Account node only
            globalAccount[globalCount++] = cur->data;
        }
        cur = cur->next;
    }
}

string generateID(List *ls)
{
    srand(time(0));
    int randNum = rand() % 9000 + 1000;
    string newID = "BD-" + to_string(randNum);
    return newID;
}

int main()
{
    List *myBank = createList();
    loadFromFile(myBank, "bank_data.csv");

    // Sync globals and BST from loaded data
    rebuildGlobalArray(myBank);
    bstLoadFromList(myBank);
    initHashTable();          // ADDED
    hashLoadFromList(myBank);

    int choice;
    bool isLoggedIn = false;
    string loggedInID = "";

    do
    {
        cout << "\n==== Welcome to BDSM (Banking Data System Management) ====\n";
        cout << "Please pick one of our services:\n\n";
        cout << "1.  Login\n";
        cout << "2.  Register / Add an account\n";
        cout << "3.  Add transaction\n";
        cout << "4.  Delete account\n";
        cout << "5.  Update account\n";
        cout << "6.  Search account\n";
        cout << "7.  Display all\n";
        cout << "8.  Logout\n";
        cout << "9.  Sorting / Reports\n";
        cout << "10. BST Account Search\n";
        cout << "11. Action History (Stack)\n";
        cout << "12. Customer Queue\n";
        cout << "13. Hash Table Lookup\n";
        cout << "14. Exit\n";
        cout << "Input your option: ";
        cin >> choice;

        if (choice == 1)
        {
            if (isLoggedIn)
            {
                cout << "Already logged in!\n";
            }
            else
            {
                string id, password;
                cout << "Enter account ID: ";
                cin >> id;
                cout << "Enter password: ";
                cin >> password;
                loggedInID = login(myBank, id, password);
                if (loggedInID != "")
                {
                    isLoggedIn = true;
                }
            }
        }
        else if (choice == 2)
        {
            if (isLoggedIn)
            {
                cout << "Please logout first before registering a new account!\n";
            }
            else
            {
                string name, password;
                double balance;

                cout << "===== Register New Account =====\n";

                string id = generateID(myBank);

                cin.ignore();
                cout << "Enter Full Name: ";
                getline(cin, name);

                cout << "Enter Password: ";
                cin >> password;

                cout << "Enter Initial Balance: ";
                cin >> balance;

                addAcc(myBank, id, name, password, balance);
                cout << "Your new account ID is: " << id << "\n";
                cout << "Registration successful! Please save your ID and login again to continue.\n";

                // Keep globals and BST in sync
                rebuildGlobalArray(myBank);
                bstLoadFromList(myBank);
                hashLoadFromList(myBank);
            }
        }
        else if (choice == 3)
        {
            if (!isLoggedIn)
            {
                cout << "You need to login first!\n";
            }
            else
            {
                int type;
                string toAcc;
                double amount;

                cout << "Select transaction type:\n";
                cout << "1. Deposit\n";
                cout << "2. Withdraw\n";
                cout << "3. Transfer\n";
                cin >> type;

                cout << "Enter amount: ";
                cin >> amount;

                cout << "Enter destination account ID: ";
                cin >> toAcc;

                addTrans(myBank, loggedInID, toAcc, type, amount);
                cout << "Transaction done!\n";

                // Record this transaction in the undo stack too, using the
                // same transID addTrans() just assigned (myBank->transCounter
                // is the single source of truth, see account.cpp).
                Transaction t;
                t.transID = myBank->transCounter;
                t.fromAcc = loggedInID;
                t.toAcc = toAcc;
                t.type = type;
                t.amount = amount;
                pushAction(t);

                rebuildGlobalArray(myBank);
            }
        }
        else if (choice == 4)
        {
            if (!isLoggedIn)
            {
                cout << "You need to login first!\n";
            }
            else
            {
                cout << "Are you sure you want to delete? (1 = Yes, 2 = No): ";
                int confirm;
                cin >> confirm;

                if (confirm == 1)
                {
                    bstDelete(loggedInID); // remove from BST first
                    deleteAcc(myBank, loggedInID);
                    isLoggedIn = false;
                    loggedInID = "";
                    cout << "Account deleted!\n";
                    rebuildGlobalArray(myBank);
                    hashLoadFromList(myBank);
                }
                else
                {
                    cout << "Cancelled\n";
                }
            }
        }
        else if (choice == 5)
        {
            if (!isLoggedIn)
            {
                cout << "You need to login first!\n";
            }
            else
            {
                updateAcc(myBank, loggedInID);
                rebuildGlobalArray(myBank);
                bstLoadFromList(myBank); // reload BST after update
                hashLoadFromList(myBank);
            }
        }
        else if (choice == 6)
        {
            if (!isLoggedIn)
            {
                cout << "You need to login first!\n";
            }
            else
            {
                searchAcc(myBank, loggedInID);
            }
        }
        else if (choice == 7)
        {
            display(myBank);
        }
        else if (choice == 8)
        {
            if (!isLoggedIn)
            {
                cout << "You are not logged in!\n";
            }
            else
            {
                isLoggedIn = false;
                loggedInID = "";
                cout << "Logged out!\n";
            }
        }
        else if (choice == 9)
        {
            sortingMenu();
        }
        else if (choice == 10)
        {
            bstMenu();
        }
        else if (choice == 11)
        {
            if (!isLoggedIn)
            {
                cout << "You need to login first!\n";
            }
            else
            {
                stackMenu();
            }
        }
        else if (choice == 12)
        {
            queueMenu();
        }
        else if (choice == 13)
        {
            hashTableMenu();
        }
        else if (choice == 14)
        {
            saveToFile(myBank, "bank_data.csv");
            cout << "Bye!\n";
        }
        else
        {
            cout << "Invalid option, try again\n";
        }
    } while (choice != 14);

    return 0;
}