#pragma once
#include "account.h"
#include <string>

struct Element
{
    string data;
    Element *next;
};

struct Queue
{
    int n;
    Element *front;
    Element *rear;
};

Queue* createQueue();
bool isEmpty(Queue* q);
void enqueue (Queue* q, string data);
string dequeue (Queue* q);
string front(Queue* q);
string rear (Queue* q);
int getSize (Queue* q);
void display (Queue* q);

void queueMenu(List* ls);
void enqueueCustomer(string accountID);
void dequeueCustomer();
void displayQueue();
