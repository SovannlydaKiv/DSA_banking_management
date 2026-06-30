#pragma once
#include "account.h"

struct BSTNode
{
    Account data;
    BSTNode *left;
    BSTNode *right;
};

void bstInsert(Account a);
BSTNode *bstSearch(string id);
void bstInOrderDisplay();
void bstDelete(string id);
void bstMenu(List *ls);
void bstLoadFromList(List *ls);