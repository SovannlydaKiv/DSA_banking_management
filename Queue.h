#pragma once
#include "Account.h"

struct Element
{
    int data;
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
void enqueue (Queue* q, int data);
int dequeue (Queue* q);
int front(Queue* q);
int rear (Queue* q);
int getSize (Queue* q);
void display (Queue* q);

void queueMenu();
void enqueueCustomer(int accountID);
void dequeueCustomer();
void displayQueue();
