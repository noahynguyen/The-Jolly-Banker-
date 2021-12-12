#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <string>
#include <vector>
#include "money.h"
using namespace std;

/*  EIGHT FUNDS: 
0: Money Market         5: Capital Value Fund 
1: Prime Money Market   6: Growth Equity Fund 
2: Long-Term Bond       7: Growth Index Fund 
3: Short-Term Bond   
4: 500 Index Fund    
*/
const int kNumberOfFunding = 8;
const int kMoneyMarket = 0;
const int kPrimeMoneyMarket = 1;
const int kLongTermBond = 2;
const int kShortTermBond = 3;
const int k500IndexFund = 4;
const int kCapitalValueFund = 5;
const int kGrowthEquityFund = 6;
const int kGrowthIndexFund = 7;

const vector<string> kFundNames = { "Money Market", "Prime Money Market","Long-Term Bond", "Short-Term Bond",
                                    "500 Index Fund", "Capital Value Fund","Growth Equity Fund", 
                                    "Growth Index Fund"};

class Account
{
    //print account info
    friend ostream& operator<<(ostream& output, const Account& rhs);

    public:
        //constructor
        Account();
        Account(int id, string last_name, string first_name);

        //setters
        void setID(int id);
        void setFirstName(string first_name);
        void setLastName(string last_name);

        //getters
        int getID() const;
        string getFirstName() const;
        string getLastName() const;

        //actions
        //get fund names from fund id
        string GetFundName(int fund_id) const;
        //get balance of a specific fund
        int GetFundBalance(int fund_int) const;
        //add money to a fund in account 
        void AddMoney(int fund_id, int amount);
        //subtract money from a fund in account 
        bool SubtractMoney(int fund_id, int amount, Transaction& rec);
        //save transaction history 
        void RecordTransaction(Transaction& rec, int fund_id);
        //withdraw/transfer money 
        void Withdraw(int fund_id, int receiving_fund_id, int amount);
        //print history of account 
        void PrintHistory();
        //print history of specific fund 
        void PrintSpecificFundHistory(int fund_id);
        //failed transactions
        void FailTransaction(int amount, string first_name, string last_name, int fund_id);

    private:
        int id_;
        string first_name_;
        string last_name_;
        int fund_id_;
        Money fund_[kNumberOfFunding];   
};
#endif 