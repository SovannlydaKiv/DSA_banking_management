#include "BST.h"
#include <iostream>
using namespace std;

static BSTNode* root = nullptr;

// Insert
static BSTNode* insert(BSTNode* root, Account a)
{
    if (root == nullptr)
    {
        root = new BSTNode;
        root -> data = a;
        root -> left = nullptr;
        root -> right = nullptr;
    } else if (a.accID < root -> data.accID) {
        root -> left = insert (root -> left, a);
    } else if (a.accID > root -> data.accID) {
        root -> right = insert (root -> right, a);
    }
    return root;
}

// Search
static BSTNode* search(BSTNode* root, int id)
{
    if (root == nullptr)
    {
        return nullptr;
    } else if (id == root -> data.accID) {
        return nullptr;
    } else if (id < root -> data.accID) {
        return search(root -> left, id);
    } else {
        return search(root -> right, id);
    }
}

// Find Min
static BSTNode* findMin(BSTNode* root)
{
    while (root -> left != nullptr)
    {
        root = root -> left;
    }
    return root;
}

// Get size
static int getSize (BSTNode* root)
{
    if (root != nullptr)
    {
        return 0;
    } else {
        return (1 + getSize(root -> left) + getSize(root -> right));
    }
}

// In-order traversal
static void inorder(BSTNode* root)
{
    if (root != nullptr)
    {
        inorder (root -> left);
        cout << " | ID : " << root -> data.accID
             << " | Name: " << root -> data.accName
             << " | Username: " << root -> data.username
             << " | Balance: " << root -> data.balance << "\n";
        inorder (root -> right);
    }
}
// Delete
static void deleteNode(BSTNode* root, int id)
{
    BSTNode* parent = nullptr;
    BSTNode* current = nullptr;

    while (current != nullptr && current -> data.accID != id)
    {
        parent = current;
        if (id < current -> data.accID)
        {
            current = current -> left;
        } else {
            current = current -> right;
        }
    }

    if (current == nullptr)
    {
        cout << "  not found in the tree\n";
        return;
    }

    // Case 1: no child
    if (current -> left == nullptr && current -> right == nullptr)
    {
        if (current != root)
        {
            if (parent -> left == current)
            {
                parent -> left = nullptr;
            } else {
                parent -> right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete current;
    }

    // Case 2: two children
    else if (current -> left != nullptr && current -> right != nullptr)
    {
        BSTNode* succ = findMin (current -> right);
        Account savedAcc = succ -> data;
        deleteNode (root, succ -> data.accID);
        current -> data = savedAcc;
    }

    // Case 3: one child
    else
    {
        BSTNode* child = (current -> left) ? current -> left : current -> right;
        if (current != root)
        {
            if (current == parent -> left) {
                parent -> left = child;
            } else {
                parent -> right = child;
            }
        } else {
            root = child;
        }
        delete current;
    }
}

// Public function
void bstInsert (Account a) {
    root = insert(root, a);
    cout << "   [BST] Account ID " << a.accID << " inserted.\n";
}

BSTNode* bstSearch(int id)
{
    BSTNode* result = search (root, id);
    if (result != nullptr)
    {
        cout << " | Found - ID: " << result -> data.accID
             << " | Name: "       << result -> data.accName
             << " | Balance: "    << result -> data.balance << "\n";
    } else {
        cout << "  not found in the tree\n";
    }
    return result;
}

void bstInOrderDisplay()
{
    if (root == nullptr)
    {
        cout << "  [BST] Tree is empty.\n";
        return;
    }
    cout << "\n  -- In-Order Display (Sorted by Account ID) -- \n";
    inorder(root);
    cout << "\n  Total account in BST: " << getSize(root) << "\n";
}

void bstDelete(int id)
{
    if (root == nullptr)
    {
        cout << "  [BST] Tree is Empty";
        return;
    }
    deleteNode(root, id);
    cout << "  [BST] Delete for ID " << id << " complete.\n"; 
}

// BST Menu
void bstMenu()
{
    int choice;
    do
    {
        cout << "\n==============================\n";
        cout <<   "      BST Account Search      \n";
        cout <<   "==============================\n";
        cout <<   "  1. Insert Account\n";
        cout <<   "  2. Search by Account ID\n";
        cout <<   "  3. In-order display (sorted by ID)\n";
        cout <<   "  4. Delete Account\n";
        cout <<   "  0. Back\n";
        cout <<   "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            {
                Account a;
                cout << "  Account ID: ";
                cin >> a.accID;
                cout << "  Name: ";
                cin >> a.accName;
                cout << "  Username: ";
                cin >> a.username;
                cout << "  Password: ";
                cin >> a.password;
                cout << "  Balance: ";
                cin >> a.balance;
                bstInsert(a);
                break;
            }
            case 2:
            {
                int id;
                cout << "  Enter Account ID to search: ";
                cin >> id;
                bstSearch(id);
                break;
            }
            case 3:
            {
                bstInOrderDisplay();
                break;
            }
            case 4:
            {
                int id;
                cout << "  Enter Account ID to delete: ";
                cin >> id;
                bstDelete(id);
                break;
            }
            case 0:
            {
                cout << "  Returning...";
                break;
            }
            default:
            {
                cout << "  Invalid choice. Try again.\n";
                break;
            }
        } 
    } while (choice != 0);

   
}
