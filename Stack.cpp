#include "Stack.h"
#include <iostream>
using namespace std;

static Stack *createStack() {
    Stack *s = new Stack;
    s -> top = nullptr;
    s -> n = 0;
    return s;
}

bool isEmpty (Stack* s) {
    return s -> n == 0;
}

static void push(Stack *s, Transaction data)
{
    StackNode *e = new StackNode;
    e->data = data;
    e->next = s->top;
    s->top = e;
    s->n++;
}

Transaction pop(Stack *s)
{
    // Caller must check s->n > 0 before calling.
    StackNode *e = s->top;
    s->top = e->next;
    Transaction value = e->data;
    delete e;
    s->n--;
    return value;
}

Transaction peek (Stack* s) {
    return s -> top -> data;
}

void display (Stack* s) {
    if (isEmpty(s)) {
        cout << "  (empty)\n";
        return;
    }
    StackNode* e = s -> top;
    while (e != nullptr) {
        cout << "  " << e -> data.fromAcc << " -> " <<e -> data.toAcc
             << " $" << e -> data.amount << "\n";
        e = e -> next;
    }
}

static Stack *actionHistory = createStack();

static void printTrans(const Transaction& t) {
    string typeName = (t.type == 1) ? "Deposit" : (t.type == 2) ? "Withdraw" : "Transfer";
    cout << typeName << " $" << t.amount
         << " | From: " << t.fromAcc << " To: " << t.toAcc;
}

void pushAction(Transaction t) {
    push (actionHistory, t);
    cout << "  Recorded: ";
    printTrans(t);
    cout << endl;
}

void undoLastAction() {
    if (isEmpty(actionHistory)) {
        cout << "  Nothing to undo." << endl;
        return;
    }
    Transaction last = pop(actionHistory);
    cout << "  Undid: ";
    printTrans (last);
    cout << endl;
}

void viewActionHistory() {
    cout << "  Action history (most recent first): " << endl;
    if (isEmpty(actionHistory)) {
        cout << "  (empty)" << endl;
        return;
    }
    StackNode* e = actionHistory -> top;
    int i = 1;
    while (e != nullptr) {
        cout << "  " << i++ << ". ";
        printTrans(e -> data);
        cout << endl;
        e = e -> next;
    }
}

void stackMenu()
{
    int choice;
    do
    {
        cout << "\n--- Stack Menu (action history) ---\n"; // remove the "record action", repetitive, already exist in main (option 3)
        cout << "1. Undo last action\n";
        cout << "2. View history\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        if (choice == 1)
        {
            undoLastAction();
        }
        else if (choice == 2)
        {
            viewActionHistory();
        }
    } while (choice != 0);
}