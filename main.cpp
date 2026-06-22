#include "account.h"
#include <iostream>
using namespace std;

int main(){
    List* myBank = createList();
    int choice;
    bool isLoggedIn = false;
    int loggedInID = -1;

    do{
        cout << "==== Welcome to BDSM (Banking Data System Management) ====" << endl;
        cout << "Please pick one of our services:" << endl;
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
                cout << "You are already logged in!" << endl << endl;
            }
            else{
                int id;
                string password;

                cout << "Enter account ID: ";
                cin >> id;

                cout << "Enter password: ";
                cin >> password;

                loggedInID = login(myBank, id, password);
                if (loggedInID != -1){
                    isLoggedIn = true;
                }
            }
        }
        else if (choice == 2){
            if (isLoggedIn){
                cout << "You are already logged in, please logout first!" << endl << endl;
            }
            else{
                int id;
                string name, password;
                double balance;

                cout << "===== Register New Account =====" << endl;
                cout << "Enter Account ID: ";
                cin >> id;

                if (accExists(myBank, id)){
                    cout << "Account ID already exists, please use a different ID" << endl << endl;
                }
                else{
                    cin.ignore();
                    cout << "Enter Full Name: ";
                    getline(cin, name);

                    cout << "Enter Password: ";
                    cin >> password;

                    cout << "Enter Initial Balance: ";
                    cin >> balance;

                    addAcc(myBank, id, name, password, balance);
                    cout << "Account registered successfully! Please login to continue." << endl << endl;
                }
            }
        }
        else if (choice == 3){
            if (!isLoggedIn){
                cout << "You need to login first!" << endl;
                cout << "Please select option 1 to login" << endl << endl;
            }
            else{
                int toAcc, type;
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
                cout << "Transaction added successfully!" << endl << endl;
            }
        }
        else if (choice == 4){
            if (!isLoggedIn){
                cout << "You need to login first!" << endl;
                cout << "Please select option 1 to login" << endl << endl;
            }
            else{
                cout << "Are you sure you want to delete your account? (1 = Yes, 2 = No): ";
                int confirm;
                cin >> confirm;
                if (confirm == 1){
                    deleteAcc(myBank, loggedInID);
                    isLoggedIn = false;
                    loggedInID = -1;
                    cout << "Account deleted successfully!" << endl << endl;
                }
                else{
                    cout << "Account deletion cancelled" << endl << endl;
                }
            }
        }
        else if (choice == 5){
            if (!isLoggedIn){
                cout << "You need to login first!" << endl;
                cout << "Please select option 1 to login" << endl << endl;
            }
            else{
                updateAcc(myBank, loggedInID);
            }
        }
        else if (choice == 6){
            if (!isLoggedIn){
                cout << "You need to login first!" << endl;
                cout << "Please select option 1 to login" << endl << endl;
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
                loggedInID = -1;
                cout << "Logged out successfully!" << endl << endl;
            }
        }
        else if (choice == 9){
            cout << "Goodbye!" << endl;
        }
        else{
            cout << "Invalid input, please try again" << endl << endl;
        }
    } while (choice != 9);

    return 0;
}