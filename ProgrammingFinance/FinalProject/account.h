#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Doubly_Linked_List.h"
#include "functions.h"

class Account
{
public:
	virtual float get_balance() = 0;
};

class Stock_Portfolio_Account : public Account
{
private:
	float cash_balance;
	float portfolio_value;
	Doubly_linked_list portfolio;
public:
	friend class BankAccount;
	Stock_Portfolio_Account();
	float get_balance() override;
	float get_portfolio_value();
	void save_account_info();
	int initself();
	void Buy_Shares(stock, int);
	void update_portfolio(vector<stock>&);
	void print_portfolio();
	bool is_in_portfolio(string);
	int check_shares(string);
};

class BankAccount : public Account
{
public:
	int get_balance(Stock_Portfolio_Account);
};
#endif