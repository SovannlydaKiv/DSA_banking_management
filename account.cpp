#include "account.h"
#include <iostream>
using namespace std;

List* createList(){
    List* ls;
    ls = new List();
    
    ls -> n = 0;
    ls -> head = nullptr;
    ls -> tail = nullptr;

    return ls;
}

void addAcc(List* ls, int id, string name, string username, string password, double bal){
    Node* newNode = new Node();
    newNode -> data.accID = id;
    newNode -> data.username = username;
    newNode -> data.accName = name;
    newNode -> data.password = password;
    newNode -> data.balance = bal;
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

void display(List* ls){
    Node* tmp;
    tmp = ls -> head;

    if (tmp == nullptr){
        cout << "No such account found in the system" << endl;
        return;
    }
    while (tmp != nullptr){
        cout << "Welcome " << tmp -> data.username << "!" << "\n";
        cout << "Your ID is: " << tmp -> data.accID << "\n";
        cout << "Your account name is: " << tmp -> data.accName << "\n";
        cout << "Your current balance is: " << tmp -> data.balance << "\n";

        tmp = tmp -> next; 
    }
}