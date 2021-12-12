#ifndef MONEY_H_
#define MONEY_H_
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include "transaction.h"

class Money
{
    public:
        //constructor
        Money();

        //setters
        void setFundName(string fund_name);
        void setBalance(int balance);

        //getters
        string getFundName() const;
        int getBalance() const;

        //add money
        bool AddMoney(int added);
        //subtract money
        bool MinusMoney(int minus);
        //check if it's okay to subtract money 
        bool CheckMoney(int minus);
        //record transaction history
        bool RecordTransactionHistory(Transaction& trans);
        //print history of transactions of a specific fund
        void PrintSpecificFund();
        //print all transaction history 
        void PrintTransactionHistory();

private:
	string fund_name_;
	int balance_;
	vector<Transaction> transaction_history_;
};
#endif