#include <iostream>
#include "bstree.h"
using namespace std;

//constructor 
BSTree::BSTree()
{
    root = nullptr;
}

//destructor 
BSTree::~BSTree() 
{
    this->Empty();
}

bool BSTree::HelperInsert(Node* temp_root, Account* rhs)
{
    if (rhs->getID() > temp_root->pAcct->getID())
    {
        if (temp_root->right == nullptr)
        {
            //found a place to insert 
            Node* ins_acc = new Node;
            ins_acc->pAcct = rhs;
            //create branches
            ins_acc->left = nullptr;
            ins_acc->right = nullptr;
            temp_root->right = ins_acc;
            return true;
        }
        else
        {
            HelperInsert(temp_root->right, rhs);
        }
    }
    //check left side 
    else if (rhs->getID() < temp_root->pAcct->getID())
    {
        if (temp_root->left == nullptr)
        {
            //found a place to insert 
            Node* ins_acc = new Node;
            ins_acc->pAcct = rhs;
            //create branches
            ins_acc->left = nullptr;
            ins_acc->right = nullptr;
            temp_root->left = ins_acc;
            return true;
        }
        else 
        {
            HelperInsert(temp_root->left, rhs);
        }
    }
    else
    {
        cerr << "ERROR: Account " << rhs->getID() << " is already open. Transaction refused." << endl;
        return false;
    }
    return false;
}

bool BSTree::Insert(Account* rhs)
{
    //this is the first account inserted in the tree
    if (root == nullptr)
    {
        root = new Node;
        root->pAcct = rhs;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    //the root is already there
    else
    {
        //keep track of root
        Node* temp_root = root;
        //start insertion
        HelperInsert(temp_root, rhs);
    }
    return false;
}

bool BSTree::Retrieve(const int &account_id, Account*& rhs) const
{
    //create temp root
    Node* temp_root = root;

    while (temp_root != nullptr)
    {
        //account needed is right at the root
        if (temp_root->pAcct->getID() == account_id)
        {
            rhs = temp_root->pAcct;
            return true;
        }
        //check the right side
        else if (temp_root->pAcct->getID() < account_id)
        {
            temp_root = temp_root->right;
        }
        //check the left side
        else if (temp_root->pAcct->getID() > account_id)
        {
            temp_root = temp_root->left;
        }
    }
    //search whole tree but there's no such account id
    cerr << "ERROR: Account Number " << account_id  << " Cannot Be Found" << endl;
	return false;
}

void BSTree::HelperDisplay(Node* temp_root) const
{
    if (temp_root == nullptr)
    {
        return;
    }
    HelperDisplay(temp_root->left);
    if (temp_root != nullptr)
    {
        cout << *(temp_root->pAcct) << endl;
    }
    HelperDisplay(temp_root->right);
}

void BSTree::Display() const
{
    //empty tree
    if (root == nullptr)
    {
        cerr << "ERROR: Account list is empty" << endl;
    }
    HelperDisplay(root);
}

//check if the tree is empty
bool BSTree::isEmpty() const
{
    return (root == nullptr);
}

//Empty the tree
void BSTree::HelperDelete(Node* temp_root)
{
    //base case: root null
    if (temp_root == nullptr)
    {
        return;
    }
    HelperDelete(temp_root->left);
    HelperDelete(temp_root->right);
    delete temp_root;
    temp_root = nullptr;
}

void BSTree::Empty()
{
    HelperDelete(root);
}


