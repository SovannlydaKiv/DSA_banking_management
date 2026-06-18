#include <iostream>
#include <string>
using namespace std;

struct Account{
    int accID;              //id of user here
    string accName;         //name of the account owner
    string username;        //username for display
    string password;        //users password
    double balance;         //users balance
};

struct Node{
    Account data;
    Node* next;
};

struct List{
    int n;
    Node* head;
    Node* tail;
};

List* createList();

void addAcc(List* ls, int id, string name, string username, string password, double bal);
void display(List* ls);
