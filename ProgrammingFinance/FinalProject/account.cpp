#include "account.h"

float Stock_Portfolio_Account::get_balance()
{
	return cash_balance;
}

float Stock_Portfolio_Account::get_portfolio_value()
{
	return portfolio_value;
}

Stock_Portfolio_Account::Stock_Portfolio_Account()
{
	ifstream account_info("Stock_Portfolio_Account.txt");
	if (!account_info)
	{
		cash_balance = 10000;
		portfolio_value = 0;
	}
	else
	{
		account_info >> cash_balance;
		account_info >> portfolio_value;
		account_info.close();
	}
	ifstream portfolio_info("Stock_Portfolio_Info.txt");
	if (!portfolio_info)
	{
		portfolio_info.close();
	}
	else
	{
		portfolio_info.close();
		portfolio.load_portfolio();
	}
}

void Stock_Portfolio_Account::save_account_info()
{
	/* store the total portfolio value and current cash balance 
	along with the current date and time in a separate text file */
	ofstream account_info;
	account_info.open("Stock_Portfolio_Account.txt");
	account_info << cash_balance << endl;
	account_info << portfolio_value << endl;
	account_info.close();
	portfolio.save_portfolio();
	return;
}

int Stock_Portfolio_Account::initself()
{
	cash_balance = 10000;
	portfolio_value = 0;
	portfolio.clear_ALL_nodes();
	return 0;
}

void Stock_Portfolio_Account::Buy_Shares(stock A, int num)
{
	cash_balance -= A.price_per_share * num;
	if (portfolio.is_exsisting(A.name))
	{
		portfolio.Increase_one(A,num);
	}
	else
	{
		portfolio.Insert_one(new Node(A.name, num, A.price_per_share));
	}
}

void Stock_Portfolio_Account::update_portfolio(vector<stock>& A)
{
	portfolio.update_nodes(A);
	portfolio_value = portfolio.cal_portfolio_value();
}

void Stock_Portfolio_Account::print_portfolio()
{
	portfolio.print_list();
	cout << "Total portfolio value: $" << cash_balance + portfolio_value << endl;
}

bool Stock_Portfolio_Account::is_in_portfolio(string A)
{
	return portfolio.is_exsisting(A);
}

int Stock_Portfolio_Account::check_shares(string A)
{
	return portfolio.check_shares(A);
}

float Stock_Portfolio_Account::check_price(string A)
{
	return portfolio.check_price(A);
}

void Stock_Portfolio_Account::Sell_Shares(string stock_symble, int num_shares)
{
	cash_balance += portfolio.check_price(stock_symble) * num_shares;
	if (num_shares == portfolio.check_shares(stock_symble))
	{
		portfolio.Delete_one(stock_symble);
	}
	else
	{
		portfolio.Decrease_one(stock_symble,num_shares);
	}
}



float BankAccount::get_balance(Stock_Portfolio_Account& A)
{
	return A.cash_balance;
}

float BankAccount::get_balance()
{
	return 0;
}

void BankAccount::deposit_money(float money,Stock_Portfolio_Account& mystocks)
{
	mystocks.cash_balance += money;
	return;
}

void BankAccount::withdraw_money(float money, Stock_Portfolio_Account& mystocks)
{
	mystocks.cash_balance -= money;
	return;
}
