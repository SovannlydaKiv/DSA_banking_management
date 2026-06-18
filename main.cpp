#include "account.h"
#include <iostream>
using namespace std;

int main(){
    List* myBank = createList();
    int choice;

    do{
        cout << "==== Welcome to BDSM (Banking Department System Management) ====" << endl;
        cout << "Please pick one of our services:" << endl;
        cout << "1. Login" << endl;
        cout << "2. Add account " << endl;
        cout << "3. Display all accounts" << endl;
        cout << "4. Exit" << endl;
        cout << "Input ur option: ";

        cin >> choice;

        if (choice == 1) {
            string username, password;
            
            cout << "Enter Username: ";
            cin >> username;
            
            cout << "Enter Password: ";
            cin >> password;
            
            cout << "registered successfully" << endl;
        }
        else if (choice == 2) {
            int id;
            string name, username, password;
            double balance;

            cout << "Enter Account ID: ";
            cin >> id;
            cin.ignore(); 

            cout << "Enter Full Name: ";
            getline(cin, name);

            cout << "Enter Username: ";
            cin >> username;

            cout << "Enter Password: ";
            cin >> password;

            cout << "Enter Initial Balance: ";
            cin >> balance;

            addAcc(myBank, id, name, username, password, balance);
            cout << "Your account has been created successfully!" << endl;
        }
        else if (choice == 3){
            display(myBank);
        }
        else if (choice == 4){
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid input, please make a valid input" << endl;
        }
    } while (choice != 4);

    return 0;
    
}