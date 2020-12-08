#include "Doubly_Linked_List.h"

Node::Node(string stock_sybol, int num_shares, float price_per_shares)
{
	this->stock_symbol = stock_sybol;
	this->num_shares = num_shares;
	this->price_per_shares = price_per_shares;
	total_value = num_shares * price_per_shares;
	previous = NULL;
	next = NULL;
}

Doubly_linked_list::Doubly_linked_list()
{
	myHead = NULL;
	myTail = NULL;
	length = 0;
}

void Doubly_linked_list::Insert_one(Node* A)
{
	if (length == 0)
	{
		myHead = A;
		myTail = A;
		A->previous = NULL;
		A->next = NULL;
		length++;
	}
	else
	{
		myTail->next = A;
		A->previous = myTail;
		myTail = A;
		A->next = NULL;
		length++;
	}
	decreasing_sort();
	return;
}

void Doubly_linked_list::decreasing_sort()
{
	if (length <= 1)
		return;
	else
	{
		int cnt = 0;
		while (cnt != length - 1)
		{
			float max = 0;
			Node* p = myHead;
			for (int i = 0;i < cnt;i++)
			{
				p = p->next;
			}
			for (Node* q = p;q != NULL;q = q->next)
			{
				if (q->total_value > max)
				{
					max = q->total_value;
				}
			}
			if (p->total_value == max)
			{
				//Do nothing
			}
			else
			{
				for (Node* q = p;q != NULL;q = q->next)
				{
					if (q->total_value == max)
					{
						if (q != myTail)
						{
							q->previous->next = q->next;
							q->next->previous = q->previous;
						}
						else
						{
							q->previous->next = q->next;
						}
						q->previous = NULL;
						q->next = myHead;
						myHead->previous = q;
						myHead = q;
					}
				}
			}
			cnt++;
		}
	}
	return;
}

bool Doubly_linked_list::is_exsisting(string stock_symbol)
{
	if (length == 0)
	{
		return false;
	}
	else
	{
		Node* tmp=myHead;
		while (tmp != NULL)
		{
			if (tmp->stock_symbol == stock_symbol)
			{
				return true;
			}
			tmp = tmp->next;
		}
	}
	return false;
}

void Doubly_linked_list::Increase_one(stock A, int num)
{
	Node* tmp = myHead;
	while (tmp != NULL)
	{
		if (tmp->stock_symbol == A.name)
		{
			tmp->num_shares += num;
			tmp->price_per_shares = A.price_per_share;
			tmp->total_value = tmp->num_shares * tmp->price_per_shares;
			decreasing_sort();
			return;
		}
		tmp = tmp->next;
	}
}

void Doubly_linked_list::save_portfolio()
{
	ofstream portfolio_info;
	portfolio_info.open("Stock_Portfolio_Info.txt");
	for (Node* p = myHead;p != NULL;p = p->next)
	{
		portfolio_info << p->stock_symbol << "\t"
			<< p->num_shares << "\t" << p->price_per_shares << "\t"
			<< p->total_value << endl;
	}
	portfolio_info.close();
	return;
}

void Doubly_linked_list::update_nodes(vector<stock>& A)
{
	for (Node* p = myHead;p != NULL;p = p->next)
	{
		for (int i = 0;i < A.size();i++)
		{
			if (p->stock_symbol == A[i].name)
			{
				if (p->price_per_shares != A[i].price_per_share)
				{
					p->price_per_shares = A[i].price_per_share;
					p->total_value = p->price_per_shares * p->num_shares;
				}
			}
		}
	}
	decreasing_sort();
	return;
}

float Doubly_linked_list::cal_portfolio_value()
{
	float port = 0;
	for (Node* p = myHead;p != NULL;p = p->next)
	{
		port += p->total_value;
	}
	return port;
}

void Doubly_linked_list::print_list()
{
	for (Node* p = myHead;p != NULL;p = p->next)
	{
		cout << p->stock_symbol << setw(18) << p->num_shares
			<< setw(9) << "$" <<p->price_per_shares << setw(13)
			<< "$" <<p->total_value << endl;
	}
}

void Doubly_linked_list::load_portfolio()
{
	string company_symbol;
	int num_shares;
	float price_per_share;
	float total_value;
	ifstream portfolio_info;
	portfolio_info.open("Stock_Portfolio_Info.txt");
	while (portfolio_info.good() && !portfolio_info.eof())
	{
		portfolio_info >> company_symbol;
		portfolio_info >> num_shares;
		portfolio_info >> price_per_share;
		portfolio_info >> total_value;
		if (portfolio_info.peek() == EOF)
			break;
		this->Insert_one(new Node(company_symbol,num_shares,price_per_share));
	}
	portfolio_info.close();
	return;
}