#pragma once
#include "account.h"

// Merge Sort by Balance
void MergeBalance(Account arr[], int lb, int mid, int ub);
void MergeSortBalance(Account arr[], int lb, int ub);

// Merge Sort by ID
void MergeID(Account arr[], int lb, int mid, int ub);
void MergeSortID(Account arr[], int lb, int ub);

// Merge Sort by Name
void MergeName(Account arr[], int lb, int mid, int ub);
void MergeSortName(Account arr[], int lb, int ub);

// Printing function
void printAccounts(Account arr[], int n);
void sortingMenu();