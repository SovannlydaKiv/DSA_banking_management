#include "account.h"
#include "BST.h"
#include "Sorting.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MAX_ACCOUNTS 1000
Account globalAccount[MAX_ACCOUNTS];
int globalCount = 0;

List* myBank;
bool isLoggedIn = false;
string loggedInID = "";

void clearConsole();
void rebuildGlobalArray(List *ls);
string generateID(List *ls);
void operationsMenu(List* myBank);

void clearConsole()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void rebuildGlobalArray(List *ls)
{
    globalCount = 0;
    Node* cur = ls->head;
    while (cur != nullptr && globalCount < MAX_ACCOUNTS)
    {
        if (cur->type == 0)
        {
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

void operationsMenu(List* myBank)
{
    int choice;
    do
    {
        clearConsole();
        cout << "\n==== Operations Menu ====\n";
        cout << "Logged in as: " << loggedInID << "\n\n";
        
        cout << "1.  Add transaction\n";
        cout << "2.  Delete account\n";
        cout << "3.  Update account\n";
        cout << "4.  Search account\n";
        cout << "5.  Display all accounts\n";
        cout << "6.  Sorting / Reports\n";
        cout << "7.  BST Account Search\n";
        cout << "8.  Action History (Stack)\n";
        cout << "9.  Customer Queue\n";
        cout << "10. Hash Table Lookup\n";
        cout << "11. Logout (Return to Main Menu)\n";
        cout << "Input your option: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int type;
                string toAcc;
                double amount;
                cout << "Select transaction type:\n1. Deposit\n2. Withdraw\n3. Transfer\n";
                cin >> type;
                cout << "Enter amount: ";
                cin >> amount;
                cout << "Enter destination account ID: ";
                cin >> toAcc;

                addTrans(myBank, loggedInID, toAcc, type, amount);
                cout << "Transaction done!\n";
                rebuildGlobalArray(myBank);
                break;
            }
            case 2:
            {
                cout << "Are you sure you want to delete? (1 = Yes, 2 = No): ";
                int confirm;
                cin >> confirm;
                if (confirm == 1) {
                    deleteAcc(myBank, loggedInID);
                    isLoggedIn = false;
                    loggedInID = "";
                    cout << "Account deleted! You will be logged out.\n";
                    rebuildGlobalArray(myBank);
                    choice = 11; // Force the loop to exit back to main menu
                } else {
                    cout << "Cancelled\n";
                }
                break;
            }
            case 3:
                updateAcc(myBank, loggedInID);
                rebuildGlobalArray(myBank);
                break;
            case 4:
                searchAcc(myBank, loggedInID);
                break;
            case 5:
                display(myBank);
                break;
            case 6:
                sortingMenu(); 
                break;
            case 7:
                bstMenu(); 
                break;
            case 8:
                cout << "Stack Menu Triggered\n";
                break;
            case 9:
                queueMenu(); 
                break;
            case 10:
                hashTableMenu(); 
                break;
            case 11:
                isLoggedIn = false;
                loggedInID = "";
                cout << "Logged out successfully!\n";
                break;
            default:
                cout << "Invalid option, try again\n";
                break;
        }

        if (choice != 11) 
        {
            cout << "\nPress Enter to continue...";
            cin.ignore(10000, '\n');
            cin.get();
        }

    } while (choice != 11 && isLoggedIn); 
}

int main()
{
    List *myBank = createList();
    loadFromFile(myBank, "bank_data.csv"); 

    rebuildGlobalArray(myBank);
    initHashTable();          

    int choice;

    do
    {
        clearConsole();
        cout << "\n==== Welcome to BDSM (Banking Data System Management) ====\n";
        cout << "1. Login\n";
        cout << "2. Register / Add an account\n";
        cout << "3. Exit\n";
        cout << "Input your option: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                string id, password;
                cout << "Enter account ID: ";
                cin >> id;
                cout << "Enter password: ";
                password = getPassword();
                
                loggedInID = login(myBank, id, password);
                
                if (loggedInID != "") 
                {
                    isLoggedIn = true;
                    cout << "Login successful!\n";
                    cout << "\nPress Enter to enter your account...";
                    cin.ignore(10000, '\n');
                    cin.get();
                    
                    // Proceed to Page 2
                    operationsMenu(myBank); 
                } 
                else 
                {
                    cout << "Login failed. Please check your ID and Password.\n";
                    cout << "\nPress Enter to try again...";
                    cin.ignore(10000, '\n');
                    cin.get();
                }
                break;
            }
            case 2:
            {
                string name, password;
                double balance;

                cout << "===== Register New Account =====\n";
                string id = generateID(myBank);

                cin.ignore();
                cout << "Enter Full Name: ";
                getline(cin, name);
                cout << "Enter Password: ";
                password = getPassword();
                cout << "Enter Initial Balance: ";
                cin >> balance;

                addAcc(myBank, id, name, password, balance);
                cout << "Your new account ID is: " << id << "\n";
                cout << "Registration successful! Please save your ID and login to continue.\n";
                rebuildGlobalArray(myBank);
                
                cout << "\nPress Enter to return to main menu...";
                cin.ignore(10000, '\n');
                cin.get();
                break;
            }
            case 3:
            {
                saveToFile(myBank, "bank_data.csv");
                cout << "Bye!\n";
                break;
            }
            default:
            {
                cout << "Invalid option, try again\n";
                cout << "\nPress Enter to continue...";
                cin.ignore(10000, '\n');
                cin.get();
                break;
            }
        }
    } while (choice != 3);

    return 0;
}