#include "Sorting.h"
#include <iostream>
using namespace std;

extern Account globalAccount[];
extern int globalCount;
extern Account globalAccount[];
extern int globalCount;

// Marge Sort by Balance
void MergeBalance(Account arr[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - mid + 1;
    Account *b = new Account[n];

    while (i <= mid && j <= ub)
    {
        if (arr[i].balance <= arr[j].balance)
        {
            b[k++] = arr[i++];
        }
        else
        {
            b[k++] = arr[j++];
        }
    }

    while (j <= mid)
    {
        b[k++] = arr[i++];
    }
    while (j <= ub)
    {
        b[k++] = arr[j++];
    }

    for (k = 0; k < n; k++)
    {
        arr[lb + k] = b[k];
    }

    delete[] b;
}

void MergeSortBalance(Account arr[], int lb, int ub)
{
    if (lb < ub)
    {
        int mid = (lb + ub) / 2;
        MergeSortBalance(arr, lb, mid);
        MergeSortBalance(arr, mid + 1, ub);
        MergeBalance(arr, lb, mid, ub);
    }
}

// Merge Sort by ID
void MergeID(Account arr[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = lb - mid + 1;
    Account *b = new Account[n];

    while (i <= mid && j <= ub)
    {
        if (arr[i].accID <= arr[j].accID)
        {
            b[k++] = arr[i++];
        }
        else
        {
            b[k++] = arr[j++];
        }
    }

    while (i <= mid)
    {
        b[k++] = arr[i++];
    }
    while (j <= ub)
    {
        b[k++] = arr[j++];
    }

    for (k = 0; k < n; k++)
    {
        arr[lb + k] = b[k];
    }

    delete[] b;
}

void MergeSortID(Account arr[], int lb, int ub)
{
    if (lb < ub)
    {
        int mid = (lb + ub) / 2;
        MergeSortID(arr, lb, mid);
        MergeSortID(arr, mid + 1, ub);
        MergeID(arr, lb, ub, mid);
    }
}

// Merge Sort by Name
void MergeName(Account arr[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - lb + 1;
    Account *b = new Account[n];

    while (i <= mid && j <= ub)
    {
        if (arr[i].accName <= arr[j].accName)
        {
            b[k++] = arr[i++];
        }
        else
        {
            b[k++] = arr[j++];
        }
    }

    while (i <= mid)
    {
        b[k++] = arr[i++];
    }
    while (j <= ub)
    {
        b[k++] = arr[j++];
    }

    for (k = 0; k < n; k++)
    {
        arr[lb + k] = b[k];
    }

    delete[] b;
}

void MergeSortName(Account arr[], int lb, int ub)
{
    if (lb < ub)
    {
        int mid = (lb + ub) / 2;
        MergeSortName(arr, lb, mid);
        MergeSortName(arr, mid + 1, ub);
        MergeName(arr, lb, ub, mid);
    }
}

// Print
void printAccounts(Account arr[], int n, bool ascending)
{
    cout << "\n"
         << "ID" << "\t" << "Name" << "\t\t\t" << "Balance\n";
    cout << "  ----+------------------------+----------\n";

    if (ascending)
    {
        for (int i = 0; i < n; i++)
        {
            cout << "  " << arr[i].accID
                 << "\t" << arr[i].accName
                 << "\t\t" << arr[i].balance << "\n";
        }
    }
    else
    {
        for (int i = n - 1; i >= 0; i++)
        {
            cout << "  " << arr[i].accID
                 << "\t" << arr[i].accName
                 << "\t\t" << arr[i].balance;
        }
    }
}

void sortingMenu()
{
    int choice;
    do
    {
        cout << "====== Sorting / Reports =======";
        cout << "  1. Sort Balance: Low to High\n";
        cout << "  2. Sort Balance: High to Low\n";
        cout << "  3. Sort by Account ID\n";
        cout << "  4. Sort by Name (A - Z)\n";
        cout << "  0. Return to main menu\n";
        cout << "  Choice: ";
        cin >> choice;

        if (choice == 0)
        {
            cout << "  Returning...\n";
            break;
        }
        if (choice < 1 || choice > 4)
        {
            cout << "  Invalid input. Try again.\n";
            continue;
        }

        if (globalCount == 0)
        {
            cout << "  No accounts to sort.\n";
            continue;
        }

        Account *temp = new Account[globalCount];
        for (int i = 0; i < globalCount; i++)
            temp[i] = globalAccount[i];

        switch (choice)
        {
        case 1:
        {
            MergeSortBalance(temp, 0, globalCount - 1);
            cout << "  -- Balance: Low to High --\n";
            printAccounts(temp, globalCount, true);
            break;
        }
        case 2:
        {
            MergeSortBalance(temp, 0, globalCount - 1);
            cout << "  -- Balance: High to Low --\n";
            printAccounts(temp, globalCount, false); // BUG WAS: true
            break;
        }
        case 3:
        {
            MergeSortID(temp, 0, globalCount - 1);
            cout << "  -- Sorted by Account ID --\n";
            printAccounts(temp, globalCount, true);
            break;
        }
        case 4:
        {
            MergeSortName(temp, 0, globalCount - 1);
            cout << "  -- Sorted by Name --\n";
            printAccounts(temp, globalCount, true);
            break;
        }
        }

        delete[] temp;
    } while (choice != 0);
}