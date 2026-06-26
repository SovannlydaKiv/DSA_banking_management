#include "Sorting.h"
#include <iostream>
using namespace std;

// Marge Sort by Balance
void MergeBalance (Account arr[], int lb, int mid, int ub) {
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - mid + 1;
    Account* b = new Account[n];

    while (i <= mid && j <= ub) {
        if (arr[i].balance <= arr[j].balance) {
            b[k++] = arr[i++];
        } else {
            b[k++] = arr[j++];
        }
    }

    while (j <= mid) {
        b[k++] = arr[i++];
    }
    while (j <= ub) {
        b[k++] = arr[j++];
    }

    for (k = 0; k < n; k++) {
        arr[lb + k] = b[k];
    }

    delete[] b;
}

void MergeSortBalance(Account arr[], int lb, int ub) {
    if (lb < ub) {
        int mid = (lb + ub) / 2;
        MergeSortBalance (arr, lb, mid);
        MergeSortBalance (arr, mid + 1, ub);
        MergeBalance (arr, lb, mid, ub);
    }
}

// Merge Sort by ID
void MergeID (Account arr[], int lb, int mid, int ub) {
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = lb - mid + 1;
    Account* b = new Account[n];

    while (i <= mid && j <= ub) {
        if (arr[i].accID <= arr[j].accID) {
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

    for (k = 0; k < n; k++) {
        arr[lb + k] = b[k];
    }

    delete[] b;
}

void MergeSortID (Account arr[], int lb, int ub) {
    if (lb < ub) {
        int mid = (lb + ub) / 2;
        MergeSortID (arr, lb, mid);
        MergeSortID (arr, mid + 1, ub);
        MergeID (arr, lb, ub, mid);
    }
}

// Merge Sort by Name
void MergeName (Account arr[], int lb, int mid, int ub) {
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - lb + 1;
    Account* b = new Account[n];

    while (i <= mid && j <= ub) {
        if (arr[i].accName <= arr[j].accName) {
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

    for (k = 0; k < n; k++) {
        arr[lb + k] = b[k];
    }

    delete[] b;
}

void MergeSortName (Account arr[], int lb, int ub) {
    if (lb < ub) {
        int mid = (lb + ub) / 2;
        MergeSortName (arr, lb, mid);
        MergeSortName (arr, mid + 1, ub);
        MergeName (arr, lb, ub, mid);
    }
}

// Print
void printAccount (Account arr[], int n, bool ascending) {
    cout << "\n" << "ID" << "\t" << "Name" << "\t\t\t" << "Balance\n";
    cout << "  ----+------------------------+----------\n";

    if (ascending) {
        for (int i = 0; i < n; i++) {
            cout << "  " << arr[i].accID
                 << "\t" << arr[i].accName
                 << "\t\t" << arr[i].balance << "\n";
        }
    } else {
        for (int i = n - 1; i >= 0; i++) {
            cout << "  " << arr[i].accID
                 << "\t" << arr[i].accName
                 << "\t\t" << arr[i].balance;
        }
    }
}