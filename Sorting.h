#pragma once
#include "account.h"

void MergeBalance(Account arr[], int lb, int mid, int ub);
void MergeSortBalance(Account arr[], int lb, int ub);

void MergeID(Account arr[], int lb, int mid, int ub);
void MergeSortID(Account arr[], int lb, int ub);

void MergeName(Account arr[], int lb, int mid, int ub);
void MergeSortName(Account arr[], int lb, int ub);

void printAccounts(Account arr[], int n, bool ascending = true);
void sortingMenu();