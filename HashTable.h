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

int hashFunction(string value) {
    int sum = 0;
    for (char c : value) {
        sum += c;
    }
    return sum % TABLE_SIZE;
}



Bucket* createEmptyBucket() {
    Bucket* b = new Bucket;
    b -> head = nullptr; 
    b -> tail = nullptr;
    return b;
}

void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {   
        hashTable[i] = createEmptyBucket(); 
    }
}

// help append the new data to the previous 
void addToBucket(Bucket* b, Account a) {
    Element* e = new Element;
    e->data = a;
    e->next = nullptr;

    if (b -> n == 0) {
        b->head = e;
        b->tail = e;
    } else {
        b->tail->next = e;   // append the new data 
        b->tail = e;        // new node becomes the last node
    }
    b->n++;
}


bool hashInsert(Account a) {
    int index = hashFunction (a.accID);

    // Check for duplicated accID first
    Element* e = hashTable[index] -> head;
    while (e != nullptr) {
        if (e -> data.accID == a.accID) {
            cout << "Insert Failed: Account ID " << a.accID << " already exists." << endl;
            return;
        }
        e = e -> next;
    }
    
    addToBucket(hashTable[index], a);
    cout << "Account " << a.accID << " inserted at bucket " << index << endl;
}

bool hashSearch(string value) {
    int index = hashFunction(value);
    if (hashTable[index] -> n != 0) {
        Element* e = hashTable[index] -> head;
        while (e != nullptr) {
            if (e -> data.accID == value) {
                cout << value << " is contained in position " << index << endl;
                cout << "  Name: " << e -> data.accName << " Balance: " << e -> data.balance << endl;
                return true;
            }
            e = e -> next;
        }
    }

    cout << value << " is not found." << endl;
    return false;
}


bool hashDelete(string value) {
    int index = hashFunction(value);
    if (hashTable[index] -> n != 0) {
        Element* e = hashTable[index] -> head;
        Element* prev = nullptr;

        while (e != nullptr) {
            if (e -> data.accID == value) {
                if (prev == nullptr) {
                    hashTable[index] -> head = e -> next;
                    if (hashTable[index] -> tail == e) {
                        hashTable[index] -> tail = nullptr;
                    }
                } else {
                    prev -> next = e -> next;
                    if (hashTable[index] -> tail == e) {
                        hashTable[index] -> tail = prev;
                    }
                }

                delete e;
                hashTable[index] -> n--;
                cout << value << " is removed successfully." << endl;
                return true;
            }
            prev = e;
            e = e -> next;
        }
    }

    cout << "Failed to delete as " << value << " does not exists." << endl;
    return false;
}

void hashDisplay() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << "\t--> ";
        if (hashTable[i] -> n != 0) {
            Element* e = hashTable[i] -> head;
            while (e != nullptr) {
                cout << "[" << e -> data.accID << " " << e -> data.accName
                     << " $" << e -> data.balance << "]";
                e = e -> next;
            }
        } else {
            cout << "NULL";
        }
        cout << endl;
    }
}

void hashLoadFromList (List* ls) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Element* e = hashTable[i] -> head;
        while (e != nullptr) {
            Element* next = e -> next;
            delete e;
            e = next;
        }
        hashTable[i] -> head = nullptr;
        hashTable[i] -> tail = nullptr;
        hashTable[i] -> n = 0;
    }

    Node* cur = ls -> head;
    while (cur != nullptr) {
        if (cur -> type == 0) {
            hashInsert (cur -> data);
        }
        cur = cur -> next;
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
            cout << "Enter Account ID: "; 
            cin >> a.accID;
            cout << "Enter Name: ";
            cin >> a.accName;
            cout << "Enter Balance: ";   
            cin >> a.balance;
            hashInsert(a);
        }
        else if (choice == 2) {
            string id;
            cout << "Enter Account ID to search: ";
            cin >> id;
            hashSearch(id);
        }
        else if (choice == 3) {
            string id;
            cout << "Enter Account ID to delete: ";
            cin >> id;
            hashDelete(id);
        }
        else if (choice == 4) {
            hashDisplay();
        }

    } while (choice != 0);
}
