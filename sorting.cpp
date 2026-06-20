#include "Sorting.h"
#include <stdio.h>
#include <string.h>

// Merge Sort by Balance
void MergeBalance(Account arr[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - lb + 1;
    Account* b = new Account[n];

    while (i <= mid && j <= ub)
    {
        if (arr[i].balance < arr[j].balance)
        {
            b[k++] = arr[i++];
        } else {
            b[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        b[k++] = arr[i++];
    }
    while (j <= ub) {
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
    if (lb < ub) {
        int mid = (lb + ub) / 2;
        MergeSortBalance (arr, lb, mid);
        MergeSortBalance (arr, mid+1, ub);
        MergeBalance (arr, lb, mid, ub);
    }
}

// Merge sort By ID
void MergeID(Account arr[], int lb, int mid, int ub)
{
    int i = lb; 
    int j = mid + 1;
    int k = 0;
    int n = ub - lb + 1;
    Account* b = new Account[n];

    while (i <= mid && j <= ub)
    {
        if (arr[i].accID < arr[j].accID)
        {
            b[k++] = arr[i];
        } else {
            b[k++] = arr[j];
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
        MergeSortID (arr, lb, ub);
        MergeSortID (arr, mid + 1, ub);
        MergeID (arr, lb, mid, ub);
    }
}

// Merge Sort by Name (A - Z)
void MergeName(Account arr[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - lb + 1;
    Account* b = new Account[n];

    while (i <= mid && j <= ub)
    {
        if (arr[i].accName < arr[i].accName)
        {
            b[k++] = arr[i++];
        } else {
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

    for (k = 0;k < n; k++)
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
        MergeSortName (arr, lb, ub);
        MergeSortName (arr, mid + 1, ub);
        MergeName (arr, lb, mid, ub);
    }
}