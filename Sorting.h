#pragma once;
#include "Account.h"

void sortingMenu();

void BubbleSortByBalance(Account arr[], int n, bool asecending);
void MergeSortByID(Account arr[], int lb, int ub);
void sortByName(Account arr[], int n);

void printAccounts(Account arr[], int n);

void Merge(Account arr[], int lb, int mid, int ub);