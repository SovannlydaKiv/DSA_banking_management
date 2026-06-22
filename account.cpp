#include "account.h"
#include <iostream>
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

void addAcc(List* ls, int id, string name, string password, double bal){
    Node* newNode = new Node();
    newNode -> data.accID = id;
    newNode -> data.accName = name;
    newNode -> data.password = password;
    newNode -> data.balance = bal;
    newNode -> type = 0;
    newNode -> next = nullptr;

    if (ls -> n ==0){
        ls -> head = newNode;
    }
    else{
        ls -> tail -> next = newNode;
    }
    ls -> tail = newNode;
    ls -> n++;

}

void addTrans(List* ls, int fromAcc, int toAcc, int type, double amount){
    Node* newNode = new Node();
    newNode -> transData.transID = ls -> transCounter + 1;
    newNode -> transData.fromAcc = fromAcc;
    newNode -> transData.toAcc = toAcc;
    newNode -> type = 1;
    newNode -> transData.type = type;
    newNode -> transData.amount = amount;
    newNode -> next = nullptr;

        if (ls -> n ==0){
            ls -> head = newNode;
        }
        else{
            ls -> tail -> next = newNode;
        }
        ls -> tail = newNode;
        ls -> n++;
        ls -> transCounter++;
}

void deleteAcc(List* ls, int id){
    if (ls -> n == 0){
        cout << "There's no such account, try again" << "\n";
        return;
    }
    // check to delete acc at head 
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
    // check to delete acc thats either in the middle or at the end
    Node* current = ls -> head;
    while (current -> next != nullptr){
        if (current -> next -> data.accID == id){
            Node* tmp = current -> next;
            current -> next = tmp -> next;
            // if the id is at the end
            if (tmp == ls -> tail){
                ls -> tail = current;
            }
            delete tmp;
            ls -> n--;
            return;
        }
        current = current -> next;
    }
    cout << "Account not found" << endl;
}

void updateAcc(List* ls, int id){
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
                cin >> tmp -> data.password;
            }
            else if (choice == 3){
                cout << "Enter new balance: ";
                cin >> tmp -> data.balance;
            }
            break;
        }
        tmp = tmp -> next;
    }
    if (isFound){
        cout << "You have successfully updated your account!" << endl;
    } 
    else {
        cout << "No such account found in the system" << endl;
    }
}
//to search for diff id 
void searchAcc(List* ls, int id){
    Node* tmp = ls -> head;
    bool isFound = false;

    while (tmp != nullptr){
        if (tmp -> type == 0 && tmp -> data.accID == id){
            isFound = true;
            
            cout << "Account found!" << endl;
            cout << "The account ID is: " << tmp -> data.accID << endl;
            cout << "The account name is: " << tmp -> data.accName << endl;
            cout << "The account's balance is: " << tmp -> data.balance << endl;
        }
        tmp = tmp -> next;
    }
    if(!isFound){
        cout << "No such account found, try again!" << endl;
    }
}
//to handle login acc and stuff
int login(List* ls, int id, string password){
    Node* tmp = ls -> head;

    while (tmp != nullptr){
        if (tmp -> type == 0 && tmp -> data.accID == id && tmp -> data.password == password){
            cout << "Login successful! Welcome " << tmp -> data.accName << "!" << endl;
            return tmp -> data.accID;
        }
        tmp = tmp -> next;
    }
    cout << "Invalid ID or password" << endl;
    return -1;
}

//check if the acc exist or not so it doesnt let us register the same 
bool accExists(List* ls, int id){
    Node* tmp = ls -> head;
    while (tmp != nullptr){
        if (tmp -> type == 0 && tmp -> data.accID == id){
            return true;
        }
        tmp = tmp -> next;
    }
    return false;
}

void display(List* ls){
    Node* tmp;
    tmp = ls -> head;

    if (tmp == nullptr){
        cout << "No account to display, login or try again" << endl;
        return;
    }
    while (tmp != nullptr){
        if (tmp -> type == 0){
            cout << "Welcome!" << endl;
            cout << "Your ID is: " << tmp -> data.accID << "\n";
            cout << "Your account name is: " << tmp -> data.accName << "\n";
            cout << "Your current balance is: " << tmp -> data.balance << "\n";
        }
        else if (tmp -> type == 1){
            cout << "Your transaction record" << "\n";
            cout << "Your transaction ID is: " <<  tmp -> transData.transID << "\n";

            if (tmp -> transData.type == 1){
                cout << "You selected transaction type: Deposit" << "\n";
            }
            else if (tmp -> transData.type == 2){
                cout << "You selected transaction type: Withdrawal" << "\n";
            }
            else if (tmp -> transData.type == 3){
                cout << "You selected transaction type: Transfer" << "\n";
            }
            cout << "From Account: " << tmp -> transData.fromAcc << "\n";
            cout << "To Account: " << tmp -> transData.toAcc << "\n";
            cout << "Amount: " << tmp -> transData.amount << "\n";
        }
        tmp = tmp -> next; 
    }
}