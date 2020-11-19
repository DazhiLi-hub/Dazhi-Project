#include "LinkedList.h"
#include <iostream>
#include <limits>

void Continue()
{
	cout << "(Press Enter to Continue)";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
}

void Display_manu()
{
	cout << "Please choose an option:" << endl;
	cout << "1.  Add a new node at the beginning" << endl;
	cout << "2.  Add a new node at the end" << endl;
	cout << "3.  Remove the beginning node" << endl;
	cout << "4.  Remove the end node" << endl;
	cout << "5.  Remove a node from the list by entering an item number" << endl;
	cout << "6.  Remove a node from the list by entering an item name" << endl;
	cout << "7.  Print out the list" << endl;
	cout << "8.  Quit the program" << endl;
}

int main(void)
{
	char choice = '0';
	LinkedList* my_list=new LinkedList;
	cout << "Welcome to the shopping list program" << endl;
	while (choice!='8')
	{
		Display_manu();
		cout << "Please enter your choice here: ";
		cin >> choice;
		switch (choice)
		{
		case '1':
		{
			int item_no;
			string item_name="\n";
			cout << "Please enter product number to insert at beginning: ";
			cin >> item_no;
			cout << "Please enter the name for the product: ";
			getline(cin , item_name);
			getline(cin , item_name);
			my_list->addToStart(new Node(item_name, item_no));
			my_list->printList();
			Continue();
			break;
		}
		case '2':
		{
			int item_no;
			string item_name = "\n";
			cout << "Please enter product number to insert at the end: ";
			cin >> item_no;
			cout << "Please enter the name for the product: ";
			getline(cin, item_name);
			getline(cin, item_name);
			my_list->addToEnd(new Node(item_name, item_no));
			my_list->printList();
			Continue();
			break;
		}
		case '3':
		{
			if (my_list->removeFromStart())
			{
				cout << "First element removed" << endl;
				my_list->printList();
			}
			else
			{
				cout << "Nothing in the list now, remove failed" << endl;
			}
			Continue();
			cin.get();
			break;
		}
		case '4':
		{
			if (my_list->removeFromEnd())
			{
				cout << "Last element removed" << endl;
				my_list->printList();
			}
			else
			{
				cout << "Nothing in the list now, remove failed" << endl;
			}
			Continue();
			cin.get();
			break;
		}
		case '5':
		{
			int item_no;
			cout << "Please enter an item number you want to delete: ";
			cin >> item_no;
			my_list->removeNodeFromList(item_no);
			my_list->printList();
			Continue();
			cin.get();
			break;
		}
		case '6':
		{
			string item_name="\n";
			cout << "Please enter an item name you want to delete: ";
			getline(cin, item_name);
			getline(cin, item_name);
			my_list->removeNodeFromList(item_name);
			my_list->printList();
			Continue();
			break;
		}
		case '7':
		{
			my_list->printList();
			cout << "The list contains " << my_list->size() << " items" << endl;
			Continue();
			cin.get();
			break;
		}
		case '8':
		{
			break;
		}
		default:
		{
			cerr << "Invalid input, please try again" << endl;
		}
		}
	}
	delete my_list;
	return 0;
}