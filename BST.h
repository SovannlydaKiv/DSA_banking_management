#pragma once
#include "account.h"

struct BSTNode
{
    Account data;
    BSTNode* left;
    BSTNode* right;
};

void bstNode();
void bstInsert(Account a);
BSTNode* bstSearch(int id);
void bstInOrderDisplay();
void bstDelete(int id);