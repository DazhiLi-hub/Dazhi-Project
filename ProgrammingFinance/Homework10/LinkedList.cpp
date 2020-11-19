#include "LinkedList.h"
#include<iomanip>
#include<iostream>
LinkedList::LinkedList()
{
	myHead = NULL;
	myTail = NULL;
	mySize = 0;
}

LinkedList::~LinkedList()
{
	cout << "List destroyed" << endl;
}

int LinkedList::size() const
{
	Node* tmp=myHead;
	int cnt=0;
	if (tmp != NULL)
	{
		cnt++;
		while (tmp->next != NULL)
		{
			cnt++;
			tmp = tmp->next;
		}
	}
	if (cnt == mySize)
		return mySize;
	else
		return 0;
}

void LinkedList::addToStart(Node* A)
{
	if (mySize == 0)
	{
		myHead = A;
		myTail = A;
	}
	else
	{
		A->next = myHead;
		myHead = A;
	}
	mySize++;
	return;
}

void LinkedList::addToEnd(Node* A)
{
	if (mySize == 0)
	{
		myHead = A;
		myTail = A;
	}
	else
	{
		myTail->next = A;
		myTail = A;
	}
	mySize++;
	return;
}

void LinkedList::printList()
{
	Node* tmp=myHead;
	cout << "List" << endl;
	cout << "Item No  Item Name" << endl;
	while (tmp!= NULL)
	{
		cout << setw(4) << tmp->itemNo;
		cout << setw(7) << " "<< tmp->itemName << endl;
		tmp = tmp->next;
	}
}

bool LinkedList::removeFromStart()
{
	if (mySize == 0)
	{
		return false;
	}
	Node* new_head = myHead->next;
	delete myHead;
	myHead = new_head;
	mySize--;
	return true;
}

bool LinkedList::removeFromEnd()
{
	if (mySize == 0)
	{
		return false;
	}
	else if (mySize == 1)
	{
		delete myTail;
		myHead = NULL;
		myTail = NULL;
	}
	else
	{
		Node* new_tail=myHead;
		while (new_tail->next != myTail)
		{
			new_tail = new_tail->next;
		}
		delete myTail;
		myTail = new_tail;
		new_tail->next = NULL;
	}
	mySize--;
	return true;
}

void LinkedList::removeNodeFromList(int item_no)
{
	if (mySize == 0)
	{
		cout << "Nothing in the list yet, remove failed" << endl;
		return;
	}
	else if (mySize == 1)
	{
		if (myHead->itemNo == item_no)
		{
			delete myHead;
			myHead = NULL;
			myTail = NULL;
			mySize--;
			cout << "Your requested item is removed successfully" << endl;
			return;
		}
		else
		{
			cout << "Your requested item could not be found, remove failed" << endl;
			return;
		}
	}
	else
	{
		Node* previous_one=myHead;
		Node* deleted_one;
		Node* next_one;
		bool found = false;
		if (myHead->itemNo == item_no)
		{
			removeFromStart();
			cout << "Your requested item is removed successfully" << endl;
			return;
		}
		else if (myTail->itemNo == item_no)
		{
			removeFromEnd();
			cout << "Your requested item is removed successfully" << endl;
			return;
		}
		else
		{
			while (previous_one != myTail)
			{
				if (previous_one->next->itemNo == item_no)
				{
					found = true;
					deleted_one = previous_one->next;
					next_one = deleted_one->next;
					previous_one->next = next_one;
					delete deleted_one;
					cout << "Your requested item is removed successfully" << endl;
					mySize--;
					return;
				}
				previous_one = previous_one->next;
			}
			if (!found)
			{
				cout << "Your requested item could not be found, remove failed" << endl;
				return;
			}
		}
	}
}

void LinkedList::removeNodeFromList(string item_name)
{
	if (mySize == 0)
	{
		cout << "Nothing in the list yet, remove failed" << endl;
		return;
	}
	else if (mySize == 1)
	{
		if (myHead->itemName == item_name)
		{
			delete myHead;
			myHead = NULL;
			myTail = NULL;
			mySize--;
			cout << "Your requested item is removed successfully" << endl;
			return;
		}
		else
		{
			cout << "Your requested item could not be found, remove failed" << endl;
			return;
		}
	}
	else
	{
		Node* previous_one = myHead;
		Node* deleted_one;
		Node* next_one;
		bool found = false;
		if (myHead->itemName == item_name)
		{
			removeFromStart();
			cout << "Your requested item is removed successfully" << endl;
			return;
		}
		else if (myTail->itemName == item_name)
		{
			removeFromEnd();
			cout << "Your requested item is removed successfully" << endl;
			return;
		}
		else
		{
			while (previous_one != myTail)
			{
				if (previous_one->next->itemName == item_name)
				{
					found = true;
					deleted_one = previous_one->next;
					next_one = deleted_one->next;
					previous_one->next = next_one;
					delete deleted_one;
					cout << "Your requested item is removed successfully" << endl;
					mySize--;
					return;
				}
				previous_one = previous_one->next;
			}
			if (!found)
			{
				cout << "Your requested item could not be found, remove failed" << endl;
				return;
			}
		}
	}
}
