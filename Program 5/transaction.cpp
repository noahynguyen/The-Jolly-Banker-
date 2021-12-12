#include "transaction.h"
#include <string>
#include <iostream>
using namespace std;

//default constructors 
Transaction::Transaction()
{
    transaction_type_ = ' ';
    first_name_ = "";
    last_name_ = "";
    account_id_ = 0;
    account_fund_id_ = 0;
    receiving_account_id_ = 0;
    receiving_fund_id_ = 0;
    amount_ = 0;
}

//constructor for opening account 
Transaction::Transaction(char transaction_type, string first_name, string last_name, int account_id)
{
	transaction_type_ = transaction_type;
	first_name_ = first_name;
	last_name_ = last_name;
	account_id_ = account_id;
}

//constructor for deposit/ withdraw
Transaction::Transaction(char transaction_type, int account_id, int fund_id, int amount)
{
    transaction_type_ = transaction_type;
    account_id_ = account_id;
    account_fund_id_ = fund_id;
    amount_ = amount;
}

//constructor for transfer
Transaction::Transaction(char transaction_type, int account_id, int fund_id, int amount, int receiving_account_id, int receiving_fund_id)
{
    transaction_type_ = transaction_type;
    account_id_ = account_id;
    account_fund_id_ = fund_id;
    amount_ = amount;
    receiving_account_id_ = receiving_account_id;
    receiving_fund_id_ = receiving_fund_id;
}

//constructor for display history of account
Transaction::Transaction(char transaction_type, int account_id)
{
    transaction_type_ = transaction_type;
    account_id_ = account_id;
}

//constructor for display specific fund 
Transaction::Transaction(char transaction_type, int account_id, int fund_id)
{
    transaction_type_ = transaction_type;
    account_id_ = account_id;
    account_fund_id_ = fund_id;
}

//failed transfer 
Transaction::Transaction(char transaction_type, int account_id, int account_fund_id, int amount, int receiving_account_id, int receiving_fund_id, string is_fail)
{
    transaction_type_ = transaction_type;
    account_id_ = account_id;
    account_fund_id_ = account_fund_id;
    amount_ = amount;
    receiving_account_id_ = receiving_account_id;
    receiving_fund_id_ = receiving_fund_id;
    is_fail_ = is_fail;
}

//failed withdrawal 
Transaction::Transaction(char transaction_type, int account_id, int account_fund_id, string is_fail, int amount)
{
    transaction_type_ = transaction_type;
    account_id_ = account_id;
    account_fund_id_ = account_fund_id;
    is_fail_ = is_fail;
    amount_ = amount;
}

//getters 
string Transaction::getFirstName() const
{
    return first_name_;
}

string Transaction::getLastName() const
{
    return last_name_;
}

char Transaction::getTransactionType() const
{
    return transaction_type_;
}

int Transaction::getAccountID() const
{
    return account_id_;
}

int Transaction::getFundID() const
{
    return account_fund_id_;
}

int Transaction::getReceivingAccountID() const
{
    return receiving_account_id_;
}

int Transaction::getReceivingFundID() const
{
    return receiving_fund_id_;
}

int Transaction::getAmount() const
{
    return amount_;
}

string Transaction::getFail() const
{
    return is_fail_;
}

//setters 
bool Transaction::setTransactionType(char transaction_type)
{
    if ((transaction_type == 'O') || (transaction_type == 'D') || (transaction_type == 'W') || (transaction_type == 'T') 
    || (transaction_type == 'A') || (transaction_type == 'F'))
    {
        transaction_type_ = transaction_type;
        return true;
    }
    else
    {
        transaction_type_ = ' ';
        return false;
    }
}

void Transaction::setFirstName(string first_name)
{
    first_name_ = first_name;
}

void Transaction::setLastName(string last_name)
{
    last_name_ = last_name;
}

void Transaction::setAccountID(int account_id)
{
    account_id_ = account_id;
}

void Transaction::setAccountFundID(int account_fund_id)
{
    account_fund_id_ = account_fund_id;
}

void Transaction::setReceivingID(int receiving_id)
{
    receiving_account_id_ = receiving_id;
}

void Transaction::setReceivingFundID(int receiving_fund_id)
{
    receiving_fund_id_ = receiving_fund_id;
}

void Transaction::setMoneySent(int amount)
{
    amount_ = amount;
}

void Transaction::setFail(string is_fail)
{
    is_fail_ = is_fail;
}

bool Transaction::isFailed()
{
    return (is_fail_.empty());
}

ostream& operator<<(ostream &out, const Transaction &rhs)
{
	if (rhs.is_fail_.empty())
	{
		if (rhs.getTransactionType() == 'D' || rhs.getTransactionType() == 'W')
		{
			out << "\t" << rhs.getTransactionType() << " " << rhs.getAccountID() << " " << rhs.getFundID() 
                << " " << rhs.getAmount() << endl;
		}
		else if (rhs.getTransactionType() == 'T')
		{
			out << "\t" << rhs.getTransactionType() << " " << rhs.getAccountID() << " " << rhs.getFundID() << " "  
                << rhs.getReceivingAccountID() << " " << rhs.getReceivingFundID() << " " << rhs.getAmount() << endl;
		}
	}
	else
	{
		if (rhs.getTransactionType() == 'W')
		{
			out << "\t" << rhs.getTransactionType() << " " << rhs.getAccountID() << " " << rhs.getFundID() 
                << " " << rhs.getAmount() << " FAILED" << endl;
		}
		else if (rhs.getTransactionType() == 'T')
		{
			out << "\t" << rhs.getTransactionType() << " " << rhs.getAccountID() << " " << rhs.getFundID() << " " 
                << rhs.getReceivingAccountID() << " " << rhs.getReceivingFundID() << " " << rhs.getAmount() << " FAILED " << endl;
		}
	}
	return out;
}