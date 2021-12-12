#include <iostream>
#include "account.h"
using namespace std;

class BSTree  
{ 
public: 
    BSTree(); 
    ~BSTree();  
    
    bool Insert(Account *rhs); 
 
    // retrieve object, first parameter is the ID of the account 
    // second parameter holds pointer to found object, NULL if not found 
    bool Retrieve(const int& account_id, Account*& rhs) const; 
    
    // displays the contents of a tree to cout 
    void Display() const;  

    void Empty();  
    bool isEmpty() const;  
 
private: 
    struct Node  
    {  
        Account *pAcct; 
        Node *right; 
        Node *left; 
    }; 
    Node *root;      
    bool HelperInsert(Node* temp_root, Account* ins);
    void HelperDisplay(Node* temp_root) const;
    void HelperDelete(Node* temp_root);
}; 