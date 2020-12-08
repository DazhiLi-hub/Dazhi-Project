#include"functions.h"

int clear_ALL()
{
	remove("Stock_Portfolio_Account.txt");
	remove("Stock_Transaction_History.txt");
	remove("Stock_Portfolio_Info.txt");
	return 0;
}

int Display_Portfolio_menu()
{
	cout << endl << "Portfolio Account Menu" << endl;
	cout << "1. Display the price for a stock symbol" << endl;
	cout << "2. Display the current portfolio" << endl;
	cout << "3. Buy shares" << endl;
	cout << "4. Sell shares" << endl;
	cout << "5. View a graph for the portfolio value" << endl;
	cout << "6. View transaction history" << endl;
	cout << "7. Return to previous menu" << endl;
	cout << endl << "Option:";
	return 0;
}

int Display_Bank_menu()
{
	cout << endl << "Bank Account Menu" << endl;
	cout << "1. View account balance" << endl;
	cout << "2. Deposit money" << endl;
	cout << "3. Withdraw money" << endl;
	cout << "4. Print out history" << endl;
	cout << "5. Return to previous menu" << endl;
	cout << endl << "Option:";
	return 0;
}

vector<stock> Stock_files_import(string PATH)
{
	vector<stock> Stocks;
	ifstream stock_info(PATH);
	if (!stock_info)
	{
		cout << "File not exsisted, check path" << endl;
		return Stocks;
	}
	else
	{
		stock one_stock;
		string time;
		while (stock_info.good() && !stock_info.eof())
		{
			stock_info >> one_stock.name;
			stock_info >> one_stock.price_per_share;
			stock_info >> time;
			Stocks.push_back(one_stock);
		}
		return Stocks;
	}
}

int random_gen()
{
	return (rand() % 2) + 1;
}

const stock Find_Stock_Symbol(vector<stock>& A, string searched_one)
{
	for (int i = 0;i < A.size();i++)
	{
		if (A[i].name == searched_one)
		{
			return A[i];
		}
	}
	stock failed_one;
	failed_one.name = "Fail";
	failed_one.price_per_share = 0;
	return failed_one;
}

void write_history(string event_type, string company_symbol, int num_shares,
	float price_per_shares)
{
	ofstream history;
	time_t now = time(0);
	tm timeinfo;
	char time_now[32];
	localtime_s(&timeinfo, &now);
	asctime_s(time_now, &timeinfo);
	history.open("Stock_Transaction_History.txt", ios::app);
	history << event_type << "\t" << company_symbol << "\t"
		<< num_shares << "\t" << price_per_shares << "\t"
		<< num_shares * price_per_shares << "\t"
		<< time_now << endl;
	history.close();
	return;
}