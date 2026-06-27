#pragma once
#include "Account.h"

struct StackNode
{
    Transaction data;
    StackNode *next;
};

struct Stack
{
    int n;
    StackNode *top;
};

Stack *createStack();
bool isEmpty(Stack *s);
void push(Stack *s, Transaction data);
Transaction pop(Stack *s);
Transaction peek(Stack *s);
void display(Stack *s);

void stackMenu();
void pushAction(Transaction t);
void undoLastAction();
void viewActionHistory();