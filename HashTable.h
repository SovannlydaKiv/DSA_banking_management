#pragma once
#include <iostream>
#include "Account.h"
using namespace std;

const int TABLE_SIZE = 10;

struct Element {
    Account data;
    Element* next;
};

struct Bucket {
    int n;            
    Element* head;
    Element* tail;
};

Bucket* hashTable[TABLE_SIZE]; 

int hashFunction(int accountID) {
    return ((accountID % TABLE_SIZE) + TABLE_SIZE) % TABLE_SIZE;     // figure out the number so it can be orginize 
}



Bucket* createEmptyBucket() {
    Bucket* b = new Bucket; 
    b->tail = nullptr;
    return b;
}

void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {   
        hashTable[i] = createEmptyBucket(); 
}


// help append the new data to the previous 
void addToBucket(Bucket* b, Account a) {
    Element* e = new Element;
    e->data = a;
    e->next = nullptr;

    if (b->n == 0) {
        b->head = e;
        b->tail = e;
    } else {
        b->tail->next = e;   // append tthe new data 
        b->tail = e;         // new node becomes the last node
    }
    b->n++;
}


void hashInsert(Account a) {
    int index = hashFunction(a.accountID); 
    addToBucket(hashTable[index], a); 
    cout << "Account " << a.accountID << " inserted at bucket " << index << endl;
}

Account* hashSearch(int id) {
    int index = hashFunction(id)
    Element* e = hashTable[index]->head;

    while (e != nullptr) {
        if (e->data.accountID == id) { 
            return &(e->data);   // when match we output the result and exit
        }
        e = e->next;
    }
    return nullptr;   
}


bool hashDelete(int id) {
    int index = hashFunction(id);
    Element* e = hashTable[index]->head;
    Element* prev = nullptr; 

    while (e != nullptr) {
        if (e->data.accountID == id) {
            if (prev == nullptr) {
                hashTable[index]->head = e->next;
                if (hashTable[index]->tail == e) {
                    hashTable[index]->tail = nullptr;
                }
            } else {
                prev->next = e->next; // skip one
                if (hashTable[index]->tail == e) { // if last, we remove last and the new tail will be come prev
                    hashTable[index]->tail = prev;
                }
            }
            delete e;
            hashTable[index]->n--;
            return true;
        }
        prev = e; // move along, prev is no longer empty 
        e = e->next; 
    }
    return false;  
}

void hashDisplay() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << " --> ";
        Element* e = hashTable[i]->head;
        if (e == nullptr) {
            cout << "NULL";
        }
        while (e != nullptr) {
            cout << "[ID:" << e->data.accountID << " " << e->data.name
                << " $" << e->data.balance << "] ";
            e = e->next;
        }
        cout << endl;
    }
}


void hashTableMenu() {
    int choice;
    do {
        cout << "\n--- Hash Table Menu (Fast Account Lookup) ---\n";
        cout << "1. Insert Account\n";
        cout << "2. Search Account by ID\n";
        cout << "3. Delete Account by ID\n";
        cout << "4. Display Hash Table\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            Account a;
            cout << "Enter Account ID: "; cin >> a.accountID;
            cout << "Enter Name: ";       cin >> a.name;
            cout << "Enter Type (Savings/Checking): "; cin >> a.type;
            cout << "Enter Balance: ";    cin >> a.balance;
            a.status = "Active";
            hashInsert(a);
        }
        else if (choice == 2) {
            int id;
            cout << "Enter Account ID to search: "; cin >> id;
            Account* found = hashSearch(id);
            if (found != nullptr) {
                cout << "Found -> ID: " << found->accountID
                    << ", Name: " << found->name
                    << ", Balance: " << found->balance << endl;
            } else {
                cout << "Account not found.\n";
            }
        }
        else if (choice == 3) {
            int id;
            cout << "Enter Account ID to delete: "; cin >> id;
            if (hashDelete(id)) cout << "Deleted successfully.\n";
            else cout << "Account not found.\n";
        }
        else if (choice == 4) {
            hashDisplay();
        }

    } while (choice != 0);
}
