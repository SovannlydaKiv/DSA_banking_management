#include "Queue.h"
#include <iostream>
using namespace std;

Queue *createQueue()
{
    Queue *q = new Queue;
    q->n = 0;
    q->front = nullptr;
    q->rear = nullptr;
    return q;
}

bool isEmpty(Queue *q)
{
    return q->n == 0;
}

void enqueue(Queue *q, string data)
{
    Element *e = new Element;
    e->data = data;
    e->next = nullptr;

    if (q->n == 0)
    {
        q->front = e;
        q->rear = e;
    }
    else
    {
        q->rear->next = e;
        q->rear = e;
    }

    q->n += 1;
}

string dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        cout << "Queue is empty!" << endl;
        return ""; 
    }
    string value = q->front->data;
    Element *e = q->front;
    q->front = e->next;
    if (q->front == nullptr)
    {
        q->rear = nullptr;
    }
    delete e;
    q->n -= 1;
    return value;
}

string front(Queue *q)
{
    if (isEmpty(q))
    {
        cout << "Queue is empty" << endl;
        return "";
    }
    return q->front->data;
}

string rear(Queue *q)
{
    if (isEmpty(q))
    {
        cout << "Queue is empty" << endl;
        return "";
    }
    return q->rear->data;
}

int getSize(Queue *q)
{
    return q->n;
}

void display(Queue *q)
{
    if (isEmpty(q))
    {
        cout << "Queue is empty" << endl;
        return;
    }
    Element *e = q->front;
    while (e != nullptr)
    {
        cout << e->data << "  ";
        e = e->next;
    }
    cout << endl;
}

static Queue *customerQueue = createQueue();

void enqueueCustomer(string accountID)
{
    enqueue(customerQueue, accountID);
    cout << "Customer (account " << accountID << ") joined the queue.\n";
}

void dequeueCustomer()
{
    if (isEmpty(customerQueue))
    {
        cout << "No customers in the queue.\n";
        return;
    }
    string accountID = dequeue(customerQueue);
    cout << "Now serving customer (account " << accountID << ").\n";
}

void displayQueue()
{
    cout << "Customers waiting (front -> rear): ";
    display(customerQueue);
}

bool accountExists(List* ls, string id)
{
    Node* cur = ls->head;
    while (cur != nullptr)
    {
        if (cur->type == 0 && cur->data.accID == id)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void queueMenu(List* ls)
{
    int choice;
    do
    {
        cout << "\n--- Queue Menu (customer line) ---\n";
        cout << "1. Add customer to queue\n";
        cout << "2. Serve next customer\n";
        cout << "3. Display queue\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string id;
            cout << "Account ID: ";
            cin >> id;
            if (accountExists(ls, id))
            {
                enqueueCustomer(id);
            }
            else
            {
                cout << "Error: Account ID '" << id << "' does not exist in the bank!\n";
            }
        }
        else if (choice == 2)
        {
            dequeueCustomer();
        }
        else if (choice == 3)
        {
            displayQueue();
        }
    } while (choice != 0);
}
