#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <iostream>
using namespace std;
#include <string>

class Transaction
{
    friend ostream & operator<<(ostream &out, const Transaction &rhs);
public:
	//default constructor 
	Transaction();
	//constructor for opening an account 
	Transaction(char transaction_type, string first_name, string last_name, int account_id);
	//constructor for deposit/ withdraw
	Transaction(char transaction_type, int account_id, int account_fund_id, int amount);
	//constructor for transfer
	Transaction(char transaction_type, int account_id, int account_fund_id, int amount, int receiving_account_id, int receiving_fund_id);
	//constructor for display history of account
	Transaction(char transaction_type, int account_id);
	//constructor for display specific fund 
	Transaction(char transaction_type, int account_id, int account_fund_id);

	//constructors for failed transaction
	//failed transfer 
	Transaction(char transaction_type, int account_id, int fund_id, int amount, int receiving_account_id, int receiving_fund_id, string is_fail);
	//failed withdrawal 
	Transaction(char transaction_type, int account_id, int fund_id, string is_fail, int amount);

    //getters 
    string getFirstName() const;
	string getLastName() const;
    char getTransactionType() const;
	int getAccountID() const;
	int getFundID() const;
	int getReceivingAccountID() const;
	int getReceivingFundID() const;
	int getAmount() const;
    string getFail() const;

    //setters 
    bool setTransactionType(char transaction_type);
    void setFirstName(string first_name);
    void setLastName(string last_name);
    void setAccountID(int account_id);
    void setAccountFundID(int account_fund_id);
    void setReceivingID(int receiving_id);
    void setReceivingFundID(int receiving_fund_id);
    void setMoneySent(int amount);
    void setFail(string is_fail);
    
	bool isFailed();

private:
	char transaction_type_;
	string first_name_;
	string last_name_;
	string is_fail_;
	int account_id_, account_fund_id_, receiving_account_id_, receiving_fund_id_, amount_;
};
#endif 