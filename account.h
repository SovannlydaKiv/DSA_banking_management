#include <iostream>
#include <string>
using namespace std;

struct Account{
    int accID;              //id of user here
    string accName;         //name of the account owner
    string password;        //users password
    double balance;         //users balance
};

struct Transaction{
    int transID;
    int fromAcc;
    int toAcc;
    int type;       //what type of transaction, is it deposit or withdrawal or transfer
    double amount;
};

struct Node{
    int type;
    Account data;
    Transaction transData;
    Node* next;
};

struct List{
    int n;
    int transCounter;
    Node* head;
    Node* tail;
};

List* createList();

void addAcc(List* ls, int id, string name, string password, double bal);
void addTrans(List* ls, int fromAcc, int toAcc, int type, double amount);
void deleteAcc(List* ls, int id);
void updateAcc(List* ls, int id);
void searchAcc(List* ls, int id);
int login(List* ls, int id, string password);
bool accExists(List* ls, int id);
void display(List* ls);
void display(List* ls);
