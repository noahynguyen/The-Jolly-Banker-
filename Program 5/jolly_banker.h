#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "bstree.h"
using namespace std;

class JollyBanker
{
    public:
        //constructor
        JollyBanker();
        
        //use a queue to read the transactions into during phase 1
        bool ReadInput(string file_name);
        //the client accounts should be stored in a binary search tree (BSTree)
        void StoringAccounts();
        //display
        void Display();

    private:
        queue<Transaction> banking_action_;
        BSTree account_data_;
};