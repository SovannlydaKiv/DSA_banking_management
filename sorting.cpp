#include "Sorting.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
using namespace std;

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortAscending(Account arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool flag = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].balance > arr[j + 1].balance)
            {
                swap (arr[j].balance, arr[j+1].balance);
                flag = true;
            }
        }
        if (!flag) break;
    }
}

void bubbleSortDescending(Account arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool flag = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].balance < arr[j+1].balance)
            {
                swap (arr[j].balance, arr[j+1].balance);
                flag = true;
            }
        }
        if (!flag) break;
    }
}

void BubbleSortByBalance(Account arr[], int n, bool ascending)
{
    if (ascending)
    {
        bubbleSortAscending(arr, n);
    } else
    {
        bubbleSortDescending(arr, n);
    }
}

void Merge(Account a[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - lb + 1;
    Account* b = new Account[n];

    while (i <= mid && j <= ub)
    {
        if (a[i].accID < a[j].accID)
        {
            b[k++] = a[i++];
        } else
        {
            b[k++] = a[j++];
        }
    }

    while (i <= mid)
    {
        b[k++] = a[i++];
    }

    while (j <= ub)
    {
        b[k++] = a[j++];
    }

    for (k = 0; k < n; k++)
    {
        a[lb + k] = b[k];
    }

    delete[] b;
}

void MergeSortByID(Account arr[], int lb, int ub)
{
    if (lb < ub)
    {
        int mid = (lb + ub) / 2;
        MergeSortByID(arr, lb, mid);
        MergeSortByID(arr, mid + 1, ub);
        Merge(arr, lb, mid, ub);
    }
}

void sortByName(Account arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = 1;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(arr[j].accName.c_str(), arr[minIdx].accName.c_str()) < 0)
            {
                minIdx = j;
            }
        }

        if (minIdx != i)
        {
            swap(arr[i].accName, arr[minIdx].accName);
        }
    }
}