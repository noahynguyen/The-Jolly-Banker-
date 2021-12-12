#include <iostream>
#include "jolly_banker.h"
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;

//constructor
JollyBanker::JollyBanker() {}

//use a queue to read the transactions into during phase 1
bool JollyBanker::ReadInput(string file_name)
{
    ifstream inputFile(file_name);
    //cannot open file
    if (!inputFile.is_open())
    {
        cerr << "ERROR: Cannot open input file." << endl;
        return false;
    }

    string line;
    while (!inputFile.eof())
    {
        getline(inputFile, line);

        //get the first character on the line
        istringstream get_char(line);
        char trans_type;
        get_char >> trans_type;

        //open account
        if (trans_type == 'O')
        {
            string last_name, first_name;
            int id;
            get_char >> id >> last_name >> first_name;
            Transaction open_account(trans_type, first_name, last_name, id);
            banking_action_.push(open_account);
        }
        //deposit account/ withdraw money
        else if (trans_type == 'D' || trans_type == 'W')
        {
            int id, fund_num, amount;
            get_char >> id >> fund_num >> amount;
            Transaction deposit(trans_type, id, fund_num, amount); 
            banking_action_.push(deposit);
        }
        //transfer money
        else if (trans_type == 'T')
        {
            int acc_id, sent_id, receiver_id, receiver_trans_num, amount;
            get_char >> acc_id >> sent_id >> receiver_id >> receiver_trans_num >> amount;
	        Transaction transfer(trans_type, acc_id, sent_id, amount, receiver_id, receiver_trans_num);
            banking_action_.push(transfer);
        }
        //Display the history of all transactions for a client account 
        else if (trans_type == 'A')
        {
            int id;
            get_char >> id;
            Transaction display(trans_type, id);
            banking_action_.push(display);
        }
        //Display transactions of a given fund
        else if (trans_type == 'F')
        {
            int id, fund_id;
            get_char >> id >> fund_id;
            Transaction display(trans_type, id, fund_id);
            banking_action_.push(display);
        }
        else
        {
            cerr << "ERROR: Invalid action." << endl;
            return false;
        }
    }

    //close file
    inputFile.close();
    return true;
}

void JollyBanker::StoringAccounts()
{
    while (!banking_action_.empty())
	{
		Transaction trans = banking_action_.front();
        //open an account 
		if (trans.getTransactionType() == 'O')
		{
			Account* acc = new Account(trans.getAccountID(), trans.getLastName(), trans.getFirstName());
			account_data_.Insert(acc);
		}
        //deposit money in an account 
		else if (trans.getTransactionType() == 'D')
		{
			int accountID = trans.getAccountID();
			int fund_ID = trans.getFundID();
			int amount = trans.getAmount();
			Account *acc;
            //check if account is in the list
			if (account_data_.Retrieve(accountID, acc))
			{
				acc->AddMoney(fund_ID, amount);
				acc->RecordTransaction(trans, fund_ID);
			}
		}
        //withdraw money 
		else if (trans.getTransactionType() == 'W')
		{
			int accountID = trans.getAccountID();
			int fund_id = trans.getFundID();
			int amount = trans.getAmount();
			Account *acc;
            //check if account exists 
			if (account_data_.Retrieve(accountID, acc))
			{
                acc->SubtractMoney(fund_id, amount, trans);
			}
		}
        //transfer 
		else if (trans.getTransactionType() == 'T')
		{
			int accountID = trans.getAccountID();
			int receivingID = trans.getReceivingAccountID();
			int fund_id = trans.getFundID();
			int receiving_fund_id = trans.getReceivingFundID();
			int amount = trans.getAmount();
			Account *to, *from;
            //check if accounts are in the website 
			if(account_data_.Retrieve(accountID, from) && account_data_.Retrieve(receivingID, to))
			{
				if (from->SubtractMoney(fund_id, amount, trans))
				{
                    to->AddMoney(receiving_fund_id, amount);
					to->RecordTransaction(trans, receiving_fund_id);
				}
				else
				{
					cerr << "ERROR: Not enough fund to transfer " << amount << " from account " << from->getFirstName() 
                         << " " << from->getLastName() << " " << from->GetFundName(fund_id) << " to " 
                         << to->getFirstName() << " " << to->getLastName() << " " << to->GetFundName(receiving_fund_id) << endl;
					Transaction fail('T', accountID, fund_id, amount, receivingID, receiving_fund_id, "(Failed)");
                    from->RecordTransaction(fail, receiving_fund_id);
				
                }
			}
		}
        //display history of the account 
		else if (trans.getTransactionType() == 'A')
		{
            Account* acc;
            int account_id = trans.getAccountID();
            if (account_data_.Retrieve(account_id, acc))
            {
                acc->PrintHistory();
                cout << endl;
            }
        }
        //display history of specific fund
        else if (trans.getTransactionType() == 'F')
        {
            Account* acc;
            int account_id = trans.getAccountID();
            int fund_id = trans.getFundID();
            if (account_data_.Retrieve(account_id, acc))
            {
                acc->PrintSpecificFundHistory(fund_id);
                cout << endl;
            }
        }
		banking_action_.pop();
	}
}

void JollyBanker::Display()
{
    cout << "FINAL BALANCES: " << endl;
    account_data_.Display();
}