#include "account.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

List* createList(){
    List* ls;
    ls = new List();
    ls -> n = 0;
    ls -> transCounter = 0;
    ls -> head = nullptr;
    ls -> tail = nullptr;
    return ls;
}
string getPassword(){
    string password;
    char ch;
    while ((ch = _getch()) != '\r'){
        if (ch == '\b'){
            if (!password.empty()){
                password.pop_back();
                cout << "\b \b";
            }
        }
        else{
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

string hashPassword(string password){
    int hash = 0;
    for (int i = 0; i < password.length(); i++){
        hash = (hash * 33 + password[i]) % 9999;
    }
    return to_string(hash);
}

void addAcc(List* ls, string id, string name, string password, double bal){
    Node* newNode = new Node();
    newNode -> data.accID = id;
    newNode -> data.accName = name;
    newNode -> data.password = hashPassword(password); 
    newNode -> data.balance = bal;
    newNode -> type = 0;
    newNode -> next = nullptr;

    if (ls -> n == 0){
        ls -> head = newNode;
    }
    else{
        ls -> tail -> next = newNode;
    }
    ls -> tail = newNode;
    ls -> n++;
}

bool addTrans(List* ls, string fromAcc, string toAcc, int type, double amount){
    Node* fromNode = nullptr;
    Node* toNode = nullptr;
    Node* cur = ls->head;
    while (cur != nullptr) {
        if (cur->type == 0) {
            if (cur->data.accID == fromAcc) {
                fromNode = cur;
            }
            if (cur->data.accID == toAcc) {
                toNode = cur;
            }
        }
        cur = cur->next;
    }

    if (fromNode == nullptr) {
        cout << "Source account not found!" << endl;
        return false;
    }

    if (type == 1) { // Deposit
        fromNode->data.balance += amount;
    }
    else if (type == 2) { // Withdraw
        if (fromNode->data.balance < amount) {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        fromNode->data.balance -= amount;
    }
    else if (type == 3) { // Transfer
        if (toNode == nullptr) {
            cout << "Destination account not found!" << endl;
            return false;
        }
        if (fromNode->data.balance < amount) {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        fromNode->data.balance -= amount;
        toNode->data.balance += amount;
    }
    else {
        cout << "Invalid transaction type!" << endl;
        return false;
    }

    Node* newNode = new Node();
    newNode -> transData.transID = ls -> transCounter + 1;
    newNode -> transData.fromAcc = fromAcc;
    newNode -> transData.toAcc = toAcc;
    newNode -> type = 1;
    newNode -> transData.type = type;
    newNode -> transData.amount = amount;
    newNode -> next = nullptr;

    if (ls -> n == 0){
        ls -> head = newNode;
    }
    else{
        ls -> tail -> next = newNode;
    }
    ls -> tail = newNode;
    ls -> n++;
    ls -> transCounter++;
    return true;
}

void deleteAcc(List* ls, string id){
    if (ls -> n == 0){
        cout << "No accounts found in the system" << "\n";
        return;
    }
    if (ls -> head -> data.accID == id){
        Node* tmp = ls -> head;
        ls -> head = tmp -> next;
        delete tmp;
        if (ls -> n == 1){
            ls -> tail = nullptr;
        }
        ls -> n--;
        return;
    }
    Node* current = ls -> head;
    while (current -> next != nullptr){
        if (current -> next -> data.accID == id){
            Node* tmp = current -> next;
            current -> next = tmp -> next;
            if (tmp == ls -> tail){
                ls -> tail = current;
            }
            delete tmp;
            ls -> n--;
            return;
        }
        current = current -> next;
    }
    cout << "Couldnt find that account!" << endl;
}

void updateAcc(List* ls, string id){
    Node* tmp = ls -> head;
    int isFound = 0;

    while (tmp != nullptr){
        if (tmp -> type == 0 && tmp -> data.accID == id){
            isFound = 1;
            cout << "What do you want to update?" << endl;
            cout << "1. Name" << endl;
            cout << "2. Password" << endl;
            cout << "3. Balance" << endl;
            int choice;
            cin >> choice;

            if (choice == 1){
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, tmp -> data.accName);
            }
            else if (choice == 2){
                cout << "Enter new password: ";
                string newPass = getPassword();

                tmp -> data.password = hashPassword(newPass);
            }
            else if (choice == 3){
                cout << "Enter new balance: ";
                cin >> tmp -> data.balance;
            }
            else{
                cout << "Invalid choice" << endl;
            }
            break;
        }
        tmp = tmp -> next;
    }
    if (isFound){
        cout << "Account updated successfully!" << endl;
    } 
    else{
        cout << "No such account found in the system" << endl;
    }
}

void searchAcc(List* ls, string id){
    Node* tmp = ls -> head;
    bool isFound = false;

    while (tmp != nullptr){
        if (tmp -> type == 0 && tmp -> data.accID == id){
            isFound = true;
            cout << "Account found!" << endl;
            cout << "ID: " << tmp -> data.accID << endl;
            cout << "Name: " << tmp -> data.accName << endl;
            cout << "Balance: $" << tmp -> data.balance << endl << endl;
        }
        tmp = tmp -> next;
    }
    if (!isFound){
        cout << "No such account found, try again!" << endl;
    }
}
string login(List* ls, string id, string password){
    Node* tmp = ls -> head;
    string hashed = hashPassword(password);

    while (tmp != nullptr){
        if (tmp -> type == 0 && tmp -> data.accID == id && tmp -> data.password == hashed){
            cout << "Login successful! Welcome " << tmp -> data.accName << "!" << endl << endl;
            return tmp -> data.accID;
        }
        tmp = tmp -> next;
    }
    cout << "Wrong ID or password, please try again" << endl << endl;
    return "";
}

void saveToFile(List* ls, string filename){
    ofstream file(filename);
    Node* tmp = ls -> head;

    while (tmp != nullptr){
        if (tmp -> type == 0){
            string savedName = tmp -> data.accName;
            for (int i = 0; i < savedName.length(); i++){
                if (savedName[i] == ' '){
                    savedName[i] = '_';
                }
            }
            file << "account " << tmp -> data.accID << " " << savedName << " " << tmp -> data.password << " " << tmp -> data.balance << "\n";
        }
        else if (tmp -> type == 1){
            file << "transaction " << tmp -> transData.transID << " " << tmp -> transData.fromAcc << " " << tmp -> transData.toAcc << " " << tmp -> transData.type << " " << tmp -> transData.amount << "\n";
        }
        tmp = tmp -> next;
    }
    file.close();
}

void loadFromFile(List* ls, string filename){
    ifstream file(filename);

    if (!file.is_open()){
        cout << "No data found" << endl;
        return;
    }

    string type;
    while (file >> type){
        if (type == "account"){
            string id, name, password;
            double balance;

            file >> id >> name >> password >> balance;

            for (int i = 0; i < name.length(); i++){
                if (name[i] == '_'){
                    name[i] = ' ';
                }
            }

            Node* newNode = new Node();
            newNode -> data.accID = id;
            newNode -> data.accName = name;
            newNode -> data.password = password;
            newNode -> data.balance = balance;
            newNode -> type = 0;
            newNode -> next = nullptr;

            if (ls -> n == 0){
                ls -> head = newNode;
            }
            else{
                ls -> tail -> next = newNode;
            }
            ls -> tail = newNode;
            ls -> n++;
        }
        else if (type == "transaction"){
            string fromAcc, toAcc;
            int transID, transType;
            double amount;

            file >> transID >> fromAcc >> toAcc >> transType >> amount;

            Node* newNode = new Node();
            newNode -> transData.transID = transID;
            newNode -> transData.fromAcc = fromAcc;
            newNode -> transData.toAcc = toAcc;
            newNode -> transData.type = transType;
            newNode -> transData.amount = amount;
            newNode -> type = 1;
            newNode -> next = nullptr;

            if (ls -> n == 0){
                ls -> head = newNode;
            }
            else{
                ls -> tail -> next = newNode;
            }
            ls -> tail = newNode;
            ls -> n++;
            ls -> transCounter++;
        }
    }
    file.close();
}

void display(List* ls){
    Node* tmp = ls -> head;

    if (tmp == nullptr){
        cout << "Nothing to display yet" << endl;
        return;
    }
    while (tmp != nullptr){
        if (tmp -> type == 0){
            cout << "==== Account ====" << endl;
            cout << "Your ID: " << tmp -> data.accID << "\n";
            cout << "Your account name is: " << tmp -> data.accName << "\n";
            cout << "Your current balance is: $" << tmp -> data.balance << "\n" << endl;
        }
        else if (tmp -> type == 1){
            cout << "==== Transaction ====" << endl;
            cout << "Transaction ID: " << tmp -> transData.transID << "\n";
            if (tmp -> transData.type == 1){
                cout << "Type: Deposit" << "\n";
            }
            else if (tmp -> transData.type == 2){
                cout << "Type: Withdrawal" << "\n";
            }
            else if (tmp -> transData.type == 3){
                cout << "Type: Transfer" << "\n";
            }
            cout << "From account: " << tmp -> transData.fromAcc << "\n";
            cout << "To account: " << tmp -> transData.toAcc << "\n";
            cout << "Amount: $" << tmp -> transData.amount << "\n" << endl;
        }
        tmp = tmp -> next; 
    }
}