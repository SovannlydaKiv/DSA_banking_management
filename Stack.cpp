#include "Stack.h"
#include <iostream>
using namespace std;

struct StackNode
{
    Transaction data;
    StackNode *next;
};

struct Stack
{
    StackNode *top;
    int n;
};

static Stack *createStack()
{
    Stack *s = new Stack;
    s->top = nullptr;
    s->n = 0;
    return s;
}

static void push(Stack *s, Transaction data)
{
    StackNode *e = new StackNode;
    e->data = data;
    e->next = s->top;
    s->top = e;
    s->n++;
}

static Transaction pop(Stack *s)
{
    // Caller must check s->n > 0 before calling.
    StackNode *e = s->top;
    s->top = e->next;
    Transaction value = e->data;
    delete e;
    s->n--;
    return value;
}

static Stack *actionHistory = createStack();

void pushAction(Transaction t)
{
    push(actionHistory, t);
    cout << "Recorded: " << t.action << " $" << t.amount
         << " on account " << t.accountID << endl;
}

void undoLastAction()
{
    if (actionHistory->n == 0)
    {
        cout << "Nothing to undo.\n";
        return;
    }
    Transaction last = pop(actionHistory);
    cout << "Undid: " << last.action << " $" << last.amount
         << " on account " << last.accountID << endl;
}

void viewActionHistory()
{
    cout << "Action history (most recent first):\n";
    if (actionHistory->n == 0)
    {
        cout << "  (empty)\n";
        return;
    }
    StackNode *e = actionHistory->top;
    while (e != nullptr)
    {
        cout << "  " << e->data.action << " $" << e->data.amount
             << " on account " << e->data.accountID << endl;
        e = e->next;
    }
}

void stackMenu()
{
    int choice;
    do
    {
        cout << "\n--- Stack Menu (action history) ---\n";
        cout << "1. Record an action\n";
        cout << "2. Undo last action\n";
        cout << "3. View history\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        if (choice == 1)
        {
            Transaction t;
            cout << "Account ID: ";
            cin >> t.accountID;
            cout << "Action (deposit/withdraw): ";
            cin >> t.action;
            cout << "Amount: ";
            cin >> t.amount;
            pushAction(t);
        }
        else if (choice == 2)
        {
            undoLastAction();
        }
        else if (choice == 3)
        {
            viewActionHistory();
        }
    } while (choice != 0);
}