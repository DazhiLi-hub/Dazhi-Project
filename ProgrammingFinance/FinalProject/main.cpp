#include "account.h"
#include "functions.h"
#include<stdlib.h>

int main(void)
{
	srand((unsigned)time(NULL));
	int random_num;
	vector<stock> stock_day_1 = Stock_files_import("Result_1.txt");
	vector<stock> stock_day_2 = Stock_files_import("Result_2.txt");
	Stock_Portfolio_Account my_stocks;
	BankAccount my_bank;
	//BankAccount my_bank;
	/*Account management system
	Ask user if they want to start a new account 
	in place of the previous one
	*/
	cout << "Welcome to the Account Management System." << endl;
	cout << "Do you want to use your previous account or a new account" << endl;
	char choice =  'a';
	while (choice != '1'&& choice != '2')
	{
		cout << "1. Using an existing account." << endl;
		cout << "2. Using a new account." << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice here:";
		cin>>choice;
		if (choice == '1')
		{
			ifstream account_info("Stock_Portfolio_Account.txt");
			if (!account_info)
			{
				cout << "There is no account existed, leading you to new account" << endl;
				cout << "New account created!" << endl;
			}
			else
			{
				cout << "Login with existed account!" << endl;
			}
		}
		else if (choice == '2')
		{
			ifstream account_info("Stock_Portfolio_Account.txt");
			if (account_info)
			{
				cout << "You have aleady have an account"
					<< ", opening a new account will delete your previous account"
					<< endl << "Are you sure you want to continue[y/n]?:";
				char new_choice;
				cin >> new_choice;
				if (new_choice == 'n' || new_choice == 'N')
				{
					choice = '\n';
				}
				else if (new_choice == 'y' || new_choice == 'Y')
				{
					clear_ALL();
					my_stocks.initself();
					cout << "New account created!" << endl;
				}
				else
				{
					cerr << "Invalid input,please try again" << endl;
					choice = '\n';
				}
			}
			else
			{
				cout << "New account created!" << endl;
			}
		}
		else if(choice =='0')
		{
			cout << "System exited" << endl;
			return 0;
		}
		else
		{
			cerr << "Invalid input, please try again" << endl;
		}
	}
	cout << my_stocks.get_balance() << endl;
	cout << my_stocks.get_portfolio_value() << endl;
	my_stocks.save_account_info();

	/*Choosing which kind of account
	Stock Portfolio account/ Bank account*/
	while (choice != '0')
	{
		cout << endl << "Welcome to the Account Management System." << endl;
		cout << "Please select an account to access:" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "0. Exit" << endl << endl;
		cout << "Option: ";
		cin >> choice;
		char inner_choice='a';
		switch (choice)
		{
		case '1':
		{
			inner_choice = 'a';
			while (inner_choice!='7')
			{
				Display_Portfolio_menu();
				cin >> inner_choice;
				switch (inner_choice)
				{
				case '1':
				{
					cout << "Please enter the stock symbol: ";
					string stock_symbol = "\n";
					getline(cin, stock_symbol);
					getline(cin, stock_symbol);
					random_num = random_gen();
					stock searched_one;
					if (random_num == 1)
					{
						searched_one = Find_Stock_Symbol(stock_day_1, stock_symbol);
						my_stocks.update_portfolio(stock_day_1);
					}
					else if (random_num == 2)
					{
						searched_one = Find_Stock_Symbol(stock_day_2, stock_symbol);
						my_stocks.update_portfolio(stock_day_2);
					}
					if (searched_one.name == "Fail")
					{
						cout << "The symbol you are looking for does not exsis"
							<< ", please try again" << endl;
					}
					else
					{
						cout << "Company-Symbol --- Price per share" << endl;
						cout <<  searched_one.name << setw(19)
							<< "$" << searched_one.price_per_share << endl;
					}
					break;
				}
				case '2':
				{
					cout << "Cash Balance = " << my_stocks.get_balance() << endl;
					cout << "Company-Symbol    Number    Price-per-share    Total value" << endl;
					my_stocks.print_portfolio();
					break;
				}
				case '3':
				{
					/*Purchase amount > cash balance -> failed*/
					/*Stock not found -> failed*/
					/*Cost more than willing -> failed*/
					/*Stock exsited -> add shares*/
					/*write a history*/
					cout << "Please enter the stock symbol you wish to purchase: ";
					string stock_symbol = "\n";
					int num_shares=0;
					float maximum_per_share = 0;
					getline(cin, stock_symbol);
					getline(cin, stock_symbol);
					random_num = random_gen();
					stock searched_one;
					if (random_num == 1)
						searched_one = Find_Stock_Symbol(stock_day_1, stock_symbol);
					else if (random_num == 2)
						searched_one = Find_Stock_Symbol(stock_day_2, stock_symbol);
					if (searched_one.name == "Fail")
					{
						cout << "The symbol you are looking for does not exsis"
							<< ", please try again" << endl;
					}
					else
					{
						while (num_shares <= 0)
						{
							cout << "Please enter the number of shares you wish to purchase: ";
							cin >> num_shares;
							if (num_shares <= 0)
							{
								cout << "Please enter a positive value and try again" << endl;
							}
							if ((num_shares * searched_one.price_per_share) > my_stocks.get_balance())
							{
								cout << "Sorry for your cash balance is not enough for this amount of shares"
									<< endl << "Please try to input a smaller shares" << endl;
								num_shares = 0;
							}
						}
						while (maximum_per_share <= 0)
						{
							cout << "Please enter the maximum amount you are willing to pay per share: ";
							cin >> maximum_per_share;
							if (maximum_per_share <= 0)
							{
								cout << "Please enter a positive value and try again" << endl;
							}
						}
						if (maximum_per_share < searched_one.price_per_share)
						{
							cout << "Purchase failed !!!" << endl
								<< "Your willing price is lower than the market price" << endl;
						}
						else
						{
							my_stocks.Buy_Shares(searched_one, num_shares);
							if (random_num == 1)
								my_stocks.update_portfolio(stock_day_1);
							else if (random_num == 2)
								my_stocks.update_portfolio(stock_day_2);
							write_history("Buy", searched_one.name, num_shares, searched_one.price_per_share);
							write_bank_history("BuyShares", num_shares* searched_one.price_per_share
								, my_bank.get_balance(my_stocks));
							cout << "You have purchased " << num_shares
								<< " shares of " << searched_one.name <<
								" at $" << searched_one.price_per_share <<
								" each for a total of $" <<
								num_shares * searched_one.price_per_share << endl;
						}
					}
					break;
				}
				case '4':
				{
					/*not in portfolio -> failed*/
					/*insufficient stocks->failed*/
					/*lower than expection -> failed*/
					/*remove nodes/decrease shares*/
					/*write history*/
					cout << "Please enter the stock symbol you wish to sell: ";
					string stock_symbol="\n";
					float minimum_per_share = 0;
					int num_shares = 0;
					getline(cin, stock_symbol);
					getline(cin, stock_symbol);
					random_num = random_gen();
					if (random_num == 1)
						my_stocks.update_portfolio(stock_day_1);
					else if (random_num == 2)
						my_stocks.update_portfolio(stock_day_2);
					if (my_stocks.is_in_portfolio(stock_symbol))
					{
						while (num_shares <= 0)
						{
							cout << "Please enter the number of shares you wish to sell: ";
							cin >> num_shares;
							if (num_shares <= 0)
							{
								cout << "Please enter a positive value and try again" << endl;
							}
							if (num_shares > my_stocks.check_shares(stock_symbol))
							{
								cout << "Your does not have so much shares to sell"
									<< ", please try again with a smaller number"
									<< endl;
								num_shares = 0;
							}
						}
						while (minimum_per_share <= 0)
						{
							cout << "Please enter the minimum amount you are willing to sell per share: ";
							cin >> minimum_per_share;
							if (minimum_per_share <= 0)
							{
								cout << "Please enter a positive value and try again" << endl;
							}
						}
						if (minimum_per_share > my_stocks.check_price(stock_symbol))
						{
							cout << "Selling failed !!!" << endl
								<< "Your willing price is higher than the market price" << endl;
						}
						else
						{
							float selling_price = my_stocks.check_price(stock_symbol);
							my_stocks.Sell_Shares(stock_symbol,num_shares);
							if (random_num == 1)
								my_stocks.update_portfolio(stock_day_1);
							if (random_num == 2)
								my_stocks.update_portfolio(stock_day_2);
							write_history("Sell",stock_symbol,num_shares,
								selling_price);
							write_bank_history("SellShares", num_shares* selling_price
								, my_bank.get_balance(my_stocks));
							cout << "You have selled " << num_shares
								<< " shares of " << stock_symbol
								<< " at $" << selling_price
								<< " each for a total of $"
								<< num_shares * selling_price << endl;
						}
					}
					else
					{
						cout << "You have no such kind of stocks, "
							<< "please check your account portfolio and try again" << endl;
					}
					break;
				}
				case '5':
				{
					cout << "Developing" << endl;
					break;
				}
				case '6':
				{
					read_transaction_history();
					break;
				}
				case '7':
				{
					break;
				}
				default:
				{
					cerr << "Invalid input, please try again" << endl;
					break;
				}
				}
			}
			break;
		}
		case '2':
		{
			inner_choice = 'a';
			while (inner_choice != '5')
			{
				Display_Bank_menu();
				cin >> inner_choice;
				switch (inner_choice)
				{
				case '1':
				{
					cout << "Your bank cash balance is: $"
						<< my_bank.get_balance(my_stocks) << endl;
					break;
				}
				case '2':
				{
					float deposit_money = 0;
					cout << "Please enter an amount you wish to deposit: ";
					cin >> deposit_money;
					if (deposit_money <= 0)
					{
						cout << "Please deposit a positive value of money" << endl;
					}
					else
					{
						my_bank.deposit_money(deposit_money, my_stocks);
						write_bank_history("Deposit", deposit_money,
							my_bank.get_balance(my_stocks));
						cout << "You have deposited $" << deposit_money
							<< " in your account now." << endl;
					}
					break;
				}
				case '3':
				{
					float withdraw_money = 0;
					cout << "Please enter an amount you wish to withdraw: ";
					cin >> withdraw_money;
					if (withdraw_money <= 0)
					{
						cout << "Please withdraw a positive value of money" << endl;
					}
					else if (withdraw_money>my_bank.get_balance(my_stocks))
					{
						cout << "You do not have such amount of money in your account"
							<< ", please check your account balance" << endl;
					}
					else
					{
						my_bank.withdraw_money(withdraw_money, my_stocks);
						write_bank_history("Withdraw", withdraw_money,
							my_bank.get_balance(my_stocks));
						cout << "You have withdrawed $" << withdraw_money
							<< " from your account now." << endl;
					}
					break;
				}
				case '4':
				{
					read_bank_history();
					break;
				}
				case '5':
				{
					break;
				}
				default:
				{
					cout << "Invalid input, please try again" << endl;
					break;
				}
				}
			}
			break;
		}
		case '0':
		{
			cout << "System exited" << endl;
			break;
		}
		default:
		{
			cerr << "Invalid input, please try again" << endl;
			break;
		}
		}
	}
	my_stocks.save_account_info();
	return 0;
}