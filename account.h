#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Account{
    string accID;    // id of user here
    string accName;  // name of the account owner
    string password; // users password
    double balance;  // users balance
};

struct Transaction{
    int transID;
    string fromAcc;
    string toAcc;
    int type; // what type of transaction, is it deposit or withdrawal or transfer
    double amount;
};

struct Node{
    int type;
    Account data;
    Transaction transData;
    Node *next;
};

struct List{
    int n;
    int transCounter;
    Node *head;
    Node *tail;
};

List *createList();

void addAcc(List *ls, string id, string name, string password, double bal);
void addTrans(List *ls, string fromAcc, string toAcc, int type, double amount);
void deleteAcc(List *ls, string id);
void updateAcc(List *ls, string id);
void searchAcc(List *ls, string id);
void saveToFile(List *ls, string filename);
void loadFromFile(List *ls, string filename);
void display(List *ls);
string login(List *ls, string id, string password);
string hashPassword(string password);
string getPassword();
