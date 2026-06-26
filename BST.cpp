#include "BST.h"
#include <iostream>
using namespace std;

static BSTNode* bstRoot = nullptr;

// Insert
static BSTNode* insert(BSTNode* node, Account a) {
    if (node == nullptr) {
        node = new BSTNode;
        node -> data = a;
        node -> left = nullptr;
        node -> right = nullptr;
    } else if(a.accID < node -> data.accID) {
        node -> left = insert (node -> left, a);
    } else if (a.accID > node -> data.accID) {
        node -> right = insert (node -> right, a);
    }
    return node;
}

// Search
static BSTNode* search (BSTNode* node, string id) {
    if (node == nullptr) {
        return nullptr;
    } else if (id == node -> data.accID) {
        return node;
    } else if (id < node -> data.accID) {
        return search(node -> left, id);
    } else {
        return search (node -> right, id);
    }
}

// Find min
static BSTNode* findMin(BSTNode* node) {
    while (node -> left != nullptr) {
        node = node -> left;
    }
    return node;
}

// Get size
static int getSize (BSTNode* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return (1 + getSize (node -> left) + getSize (node -> right));
    }
}

// In-Order traversal
static void inorder (BSTNode* node) {
    if (node != nullptr) {
        inorder (node -> left);
        cout << " | ID: "       << node -> data.accID
             << " | Name: "     << node -> data.accName
             << " | Balance: "  << node -> data.balance << "\n";
        inorder (node -> right);
    }
}

// Delete
static BSTNode* deleteNode (BSTNode* node, string id) {
    if (node == nullptr) {
        cout << "  Account not found in the tree";
        return nullptr;
    }

    if (id < node -> data.accID) {
        node -> left = deleteNode (node -> left, id);
    } else if (id > node -> data.accID) {
        node -> right = deleteNode (node -> right, id);
    } else { // find no node to delete
        // Case 1: NO CHILD
        if (node -> left == nullptr && node -> right == nullptr) {
            delete node;
            return nullptr;
        }

        // Case 2: TWO CHILD
        else if (node -> left != nullptr && node -> right != nullptr) {
            BSTNode* succ = findMin (node -> right);
            node -> data = succ -> data;
            node -> right = deleteNode (node -> right, succ -> data.accID);
        }

        // Case 3: ONE CHILD
        else {
            BSTNode* child = (node -> left) ? node -> left : node -> right;
            delete node;
            return child;
        }
    }
    return node;
}

// Public Function
void bstInsert (Account a) {
    bstRoot = insert (bstRoot, a);
    cout << "  [BST] Account ID " << a.accID << " inserted.\n";
}

BSTNode* bstSearch (string id) {
    BSTNode* result = search (bstRoot, id);
    if (result != nullptr) {
        cout << "  Found - ID: " << result -> data.accID
             << " | Name: " << result -> data.accName
             << " | Balance: " << result -> data.balance << endl;
    } else {
        cout << "Account not found" << endl;
    }
    return result;
}

void bstInOrderDisplay() {
    if (bstRoot == nullptr) {
        cout << "  [BST] Tree is empty.\n";
        return;
    }
    cout << "\n  -- In-Order Display (sorted by Account ID) --\n";
    inorder (bstRoot);
    cout << "\n  Total account is BST: " << getSize(bstRoot) << "\n";
}

void bstDelete (string id) {
    if (bstRoot == nullptr) {
        cout << "  [BST] Tree is empty.\n";
        return;
    }
    deleteNode (bstRoot, id);
    cout << "  [BST] Delete for ID " << id << " complete.\n";
}