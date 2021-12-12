#include <iostream>
using namespace std;
#include "account.h"

Account::Account() 
{
    id_ = 0;
    first_name_ = "J";
    last_name_ = "Doe";
    fund_id_ = -1;
}

Account::Account(int id, string last_name, string first_name)
{
    id_ = id;
    last_name_ = last_name;
    first_name_ = first_name;
    for (int i = 0; i < kNumberOfFunding; i++)
    {
        fund_[i].setFundName(kFundNames[i]);
    }
}

//setters
void Account::setID(int id)
{
    id_ = id;
}

void Account::setFirstName(string first_name)
{
    first_name_ = first_name;
}

void Account::setLastName(string last_name)
{
    last_name_ = last_name;
}

//getters
int Account::getID() const
{
    return id_;
}

string Account::getFirstName() const
{
    return first_name_;
}

string Account::getLastName() const
{
    return last_name_;
}

string Account::GetFundName(int fund_id) const
{
    return fund_[fund_id].getFundName();
}

int Account::GetFundBalance(int fund_id) const
{
    return fund_[fund_id].getBalance();
}

//add money to a fund in account 
void Account::AddMoney(int fund_id, int amount)
{
    fund_[fund_id].AddMoney(amount);
}

//subtract money from a fund in account 
bool Account::SubtractMoney(int fund_id, int amount, Transaction& rec)
{
    //follow the withdrawal fund 
	if (fund_id == kMoneyMarket || fund_id == kPrimeMoneyMarket || 
        fund_id == kLongTermBond || fund_id == kShortTermBond)
	{
		if (fund_id == kMoneyMarket || fund_id == kPrimeMoneyMarket)
		{
            //if there's enough money then just subtract directly 
			if (fund_[fund_id].CheckMoney(amount))
			{
				fund_[fund_id].MinusMoney(amount);
				fund_[fund_id].RecordTransactionHistory(rec);
				return true;
			}
            //if not then the linked fund can sub in 
			else if(((fund_[kMoneyMarket].getBalance() + fund_[kPrimeMoneyMarket].getBalance()) >= amount))
			{
				if (fund_id == kMoneyMarket)
				{
                    Withdraw(kMoneyMarket, kPrimeMoneyMarket, amount);
					return true;
				}
				else
				{
                    Withdraw(kPrimeMoneyMarket, kMoneyMarket, amount);
					return true;
				}
			}
			else
			{
                FailTransaction(amount, getFirstName(), getLastName(), fund_id);
				return false;
			}
		}
        //similarly with long term bond and short term bond funds 
		else if (fund_id == kLongTermBond || fund_id == kShortTermBond)
		{
			if (fund_[fund_id].CheckMoney(amount))
			{
				fund_[fund_id].MinusMoney(amount);
				fund_[fund_id].RecordTransactionHistory(rec);
				return true;
			}
			else if (((fund_[kLongTermBond].getBalance() + fund_[kShortTermBond].getBalance()) >= amount))
			{
				if (fund_id == kLongTermBond)
				{
                    Withdraw(kLongTermBond, kShortTermBond, amount);
					return true;
				}
				else
				{
                    Withdraw(kShortTermBond, kLongTermBond, amount);
					return true;
				}
			}
			else
			{
                FailTransaction(amount, getFirstName(), getLastName(), fund_id);
				return false;
			}
		}
	}
    //All other funds 
	else
	{
		if (fund_[fund_id].CheckMoney(amount))
		{
			fund_[fund_id].MinusMoney(amount);
			fund_[fund_id].RecordTransactionHistory(rec);
			return true;
		}
		else
		{	
            FailTransaction(amount, getFirstName(), getLastName(), fund_id);
			return false;
		}
	}
	return false;
}

//save transaction history 
void Account::RecordTransaction(Transaction& rec, int fund_id)
{
    fund_[fund_id].RecordTransactionHistory(rec);
}

//withdraw/transfer money 
void Account::Withdraw(int fund_id, int receiving_fund_id, int amount)
{
    /*  WITHDRAWAL RULE: 
        if you are withdrawing from a money market fund with insufficient dollars, and it can be covered with 
        dollars from the other money market fund owned by the client account, the desired amount 
        (only the partial amount needed to cover the withdrawal) is moved to that money market 
        account. The two Bond accounts are handled similarly. 
    */
    if (((fund_[fund_id].getBalance() + fund_[receiving_fund_id].getBalance()) >= amount))
	{
        //subtract all the balance from the first fund and save transaction record 
        int balance = fund_[fund_id].getBalance();
		fund_[fund_id].MinusMoney(balance);
		Transaction sub('W', getID(), fund_id, balance);
		fund_[fund_id].RecordTransactionHistory(sub);
		amount = amount - balance;
        //subtract from the second fund and save transaction record 
		fund_[receiving_fund_id].MinusMoney(amount);
		Transaction sub_sec('W', getID(), receiving_fund_id, amount);
		fund_[receiving_fund_id].RecordTransactionHistory(sub_sec);
	}
    //subtract from each fund 
	else
	{
		int balance = fund_[fund_id].getBalance();
        //subtract from first fund and save transaction history 
		if (balance > amount)
		{
			fund_[fund_id].MinusMoney(balance);
			Transaction sub('W', getID(), fund_id, balance);
			fund_[fund_id].RecordTransactionHistory(sub);
			amount = amount - balance;
		}
        //subtract from second fund and save history if possible 
		if (fund_[receiving_fund_id].CheckMoney(amount))
		{
			fund_[receiving_fund_id].MinusMoney(amount);
			Transaction sub('W', getID(), receiving_fund_id, amount);
			fund_[receiving_fund_id].RecordTransactionHistory(sub);
		}
		else
		{
			cerr << "ERROR: Not enough funds to withdraw " << amount << " from " 
                 << getFirstName() << " " << getLastName() << " " << GetFundName(receiving_fund_id) << " Fund" << endl;
			Transaction fail('W', getID(), receiving_fund_id, " (Failed) ", amount);
            fund_[receiving_fund_id].RecordTransactionHistory(fail);
		}
	}
}

//print history of account 
void Account::PrintHistory()
{
    cout << "Transaction History for " << getFirstName() << " " << getLastName() << " " << "By Fund."<< endl;
    for (int i = 0; i < kNumberOfFunding; i++)
    {
		// if (fund_[i].getBalance() != 0)
		// {
			cout << fund_[i].getFundName() << ": $" << fund_[i].getBalance() << endl;
			fund_[i].PrintSpecificFund();
		//}
    }    
}

//print history of specific fund 
void Account::PrintSpecificFundHistory(int fund_id)
{
    cout << "Transaction History for " << getFirstName() << " " << getLastName() << " " << GetFundName(fund_id) 
		 << ": $" << GetFundBalance(fund_id) << endl;
	fund_[fund_id].PrintSpecificFund();
}

//failed transactions
void Account::FailTransaction(int amount, string first_name, string last_name, int fund_id)
{
	cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << getFirstName() << " " << getLastName() 
         << " " << GetFundName(fund_id) << endl;
	Transaction fail('W', getID(), fund_id, "Failed", amount);
	fund_[fund_id].RecordTransactionHistory(fail);
}


//print account info
ostream& operator<<(ostream& output, const Account& rhs)
{
	output << rhs.getFirstName() << " " << rhs.getLastName() << " Account ID: " << rhs.getID() << endl;
	for (int i = 0; i < kNumberOfFunding; i++)
	{
		output << "\t" << rhs.GetFundName(i) << " :$" << rhs.GetFundBalance(i);
		output << endl;
	}
	
	return output;
}



