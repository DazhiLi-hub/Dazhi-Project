#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST
#include "functions.h"

class Node 
{
	/*Each node should contain the stock symbol and the
	number of shares of that stock in the portfolio. */
private:
	string stock_symbol;
	int num_shares;
	float price_per_shares;
	float total_value;
	Node* previous;
	Node* next;
public:
	Node(string,int,float);
	friend class Doubly_linked_list;
};

class Doubly_linked_list
{
private:
	Node* myHead;
	Node* myTail;
	int length;
public:
	Doubly_linked_list();
	void Insert_one(Node*);
	void Increase_one(stock,int);
	void decreasing_sort();
	bool is_exsisting(string);
	void save_portfolio();
	void update_nodes(vector<stock>&);
	float cal_portfolio_value();
	void print_list();
	void load_portfolio();
};
#endif