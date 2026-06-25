#include "account.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string generateID(List* ls){
    srand(time(0));
    int randNum = rand() % 9000 + 1000;
    string newID = "BD-" + to_string(randNum);
    return newID;
}

int main(){
    List* myBank = createList();
    loadFromFile(myBank, "bank_data.csv");
    int choice;
    bool isLoggedIn = false;
    string loggedInID = "";

    do{
        cout << "==== Welcome to BDSM (Banking Data System Management) ====" << endl;
        cout << "Please pick one of our services:" << endl << endl;
        cout << "1. Login" << endl;
        cout << "2. Register/ Add an account" << endl;
        cout << "3. Add transaction" << endl;
        cout << "4. Delete account" << endl;
        cout << "5. Update account" << endl;
        cout << "6. Search account" << endl;
        cout << "7. Display all" << endl;
        cout << "8. Logout" << endl;
        cout << "9. Exit" << endl;
        cout << "Input your option: ";
        cin >> choice;

        if (choice == 1){
            if (isLoggedIn){
                cout << "Already logged in!" << endl << endl;
            }
            else{
                string id, password;
                cout << "Enter account ID: ";
                cin >> id;
                cout << "Enter password: ";
                cin >> password;
                loggedInID = login(myBank, id, password);
                if (loggedInID != ""){
                    isLoggedIn = true;
                }
            }
        }
        else if (choice == 2){
            if (isLoggedIn){
                cout << "Please logout first before registering a new account!" << endl << endl;
            }
            else{
                string name, password;
                double balance;

                cout << "===== Register New Account =====" << endl;

                string id = generateID(myBank);

                cin.ignore();
                cout << "Enter Full Name: ";
                getline(cin, name);

                cout << "Enter Password: ";
                cin >> password;

                cout << "Enter Initial Balance: ";
                cin >> balance;

                addAcc(myBank, id, name, password, balance);
                cout << "Your new account ID is: " << id << endl;
                cout << "Registration successful! Please save your ID and login again to continue." << endl << endl;
            }
        }
        else if (choice == 3){
            if (!isLoggedIn){
                cout << "You need to login first!" << endl << endl;
            }
            else{
                int type;
                string toAcc;
                double amount;

                cout << "Select transaction type:" << endl;
                cout << "1. Deposit" << endl;
                cout << "2. Withdraw" << endl;
                cout << "3. Transfer" << endl;
                cin >> type;

                cout << "Enter amount: ";
                cin >> amount;

                cout << "Enter destination account ID: ";
                cin >> toAcc;

                addTrans(myBank, loggedInID, toAcc, type, amount);
                cout << "Transaction done!" << endl << endl;
            }
        }
        else if (choice == 4){
            if (!isLoggedIn){
                cout << "You need to login first!" << endl << endl;
            }
            else{
                cout << "Are you sure you want to delete? (1 = Yes, 2 = No): ";
                int confirm;
                cin >> confirm;

                if (confirm == 1){
                    deleteAcc(myBank, loggedInID);
                    isLoggedIn = false;
                    loggedInID = "";
                    cout << "Account deleted!" << endl << endl;
                }
                else{
                    cout << "Cancelled" << endl << endl;
                }
            }
        }
        else if (choice == 5){
            if (!isLoggedIn){
                cout << "You need to login first!" << endl << endl;
            }
            else{
                updateAcc(myBank, loggedInID);
            }
        }
        else if (choice == 6){
            if (!isLoggedIn){
                cout << "You need to login first!" << endl << endl;
            }
            else{
                searchAcc(myBank, loggedInID);
            }
        }
        else if (choice == 7){
            display(myBank);
        }
        else if (choice == 8){
            if (!isLoggedIn){
                cout << "You are not logged in!" << endl << endl;
            }
            else{
                isLoggedIn = false;
                loggedInID = "";
                cout << "Logged out!" << endl << endl;
            }
        }
        else if (choice == 9){
            saveToFile(myBank, "bank_data.csv");
            cout << "Bye!" << endl;
        }
        else{
            cout << "Invalid option, try again" << endl << endl;
        }
    } while (choice != 9);

    return 0;
}