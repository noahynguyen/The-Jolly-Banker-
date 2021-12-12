#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include "money.h"

//default constructor 
Money::Money() : balance_(0), fund_name_("") {}

//setters
void Money::setFundName(string fund_name)
{
    /* FUND TYPE:
        0: Money Market         5: Capital Value Fund 
        1: Prime Money Market   6: Growth Equity Fund 
        2: Long-Term Bond       7: Growth Index Fund 
        3: Short-Term Bond   
        4: 500 Index Fund   
    */

    //check if fund type is valid 
    if ((fund_name == "Money Market") || (fund_name == "Prime Money Market") || (fund_name == "Long-Term Bond")
        || (fund_name == "Short-Term Bond") || (fund_name == "500 Index Fund") || (fund_name == "Capital Value Fund")
        || (fund_name == "Growth Equity Fund") || (fund_name == "Growth Index Fund"))
    {
        fund_name_ = fund_name;
    }
    //error: fund type is not valid 
    else
    {
        cerr << "ERROR: Invalid Fund Name." << endl;
        fund_name_ = "";
    }
}

void Money::setBalance(int balance)
{
    //make sure valid balance is not negative 
    if (balance >= 0)
    {
        balance_ = balance;
    }
    //error: set balance to 0
    else
    {
        cerr << "ERROR: Invalid Balance." << endl;
        balance_ = 0;
    }
}

//getters
string Money::getFundName() const
{
    return fund_name_;
}

int Money::getBalance() const
{
    return balance_;
}

//add money
bool Money::AddMoney(int added)
{
    //money added must be >= 0
    if (added >= 0)
    {
        balance_ += added;
        return true;
    }
    //invalid money added
    else
    {
        cerr << "ERROR: Invalid amount of money added. Transaction refused." << endl;
        return false;
    }
}

//subtract money
bool Money::MinusMoney(int minus)
{
    //money added must be >= 0 
    if (minus >= 0)
    {
        balance_ -= minus;
        return true;
    }
    //invalid money added
    else
    {
        cerr << "ERROR: Invalid amount of money subtracted. Transaction refused." << endl;
        return false;
    }   
}

//check if it's okay to subtract money 
bool Money::CheckMoney(int minus)
{
    return (getBalance() >= minus);
}

//record transaction history
bool Money::RecordTransactionHistory(Transaction& trans)
{
    transaction_history_.push_back(trans);
    return true;
}

//print history of transactions of a specific fund
void Money::PrintSpecificFund()
{
    for (int i = 0; i < transaction_history_.size(); i++)
    {
        cout << " " << transaction_history_[i];
    }  
}

//print all transaction history 
void Money::PrintTransactionHistory()
{
    if (transaction_history_.size() == 0)
    {
        return;
    }
    cout << fund_name_ << ": $" << balance_ << endl;
    for (int i = 0; i < transaction_history_.size(); i++)
    {
        cout << " " << transaction_history_[i];
    }
}