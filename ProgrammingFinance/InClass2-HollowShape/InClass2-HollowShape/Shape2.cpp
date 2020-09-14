#include<iostream>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::abs;

int layers;
int spaces;
int total_character;

int main(void)
{
	cout << "Please enter a positive odd integer which means the maximum number of spaces: ";
	cin >> spaces;
	if (spaces <= 0 || (spaces%2==0))
	{
		cerr << "Invalid input, System aborted, Error code -1" << endl;
		return -1;
	}
	//Compute the layers and total characters in one line from the maximum number of spaces
	layers = (spaces / 2 + 1)*2 +1;
	total_character = spaces + 2;
	//Print the hollow shape 
	for (int i = 0;i < layers;i++)
	{
		//Exception for first line and last line
		if (i == 0 || i == layers - 1)
		{
			for (int j = 0;j < (abs(total_character - (i * 2 + 1)) / 2);j++)
			{
				cout << ' ';
			}
			cout << '*';
			for (int j = 0;j < (abs(total_character - (i * 2 + 1)) / 2);j++)
			{
				cout << ' ';
			}
			cout << endl;
		}
		//For upper lines
		else if(i<=(layers/2))
		{
			for (int j = 0;j < (abs(total_character - (i * 2 + 1)) / 2);j++)
			{
				cout << ' ';
			}
			cout << '*';
			for (int k = 0;k < (i * 2 - 1);k++)
			{
				cout << ' ';
			}
			cout << '*';
			for (int j = 0;j < (abs(total_character - (i * 2 + 1)) / 2);j++)
			{
				cout << ' ';
			}
			cout << endl;
		}
		//For downer line
		else
		{
			for (int j = 0;j < (abs(total_character - (i * 2 + 1)) / 2);j++)
			{
				cout << ' ';
			}
			cout << '*';
			for (int k = 0;k < (((layers/2)*2-i) * 2 - 1);k++)
			{
				cout << ' ';
			}
			cout << '*';
			for (int j = 0;j < (abs(total_character - (i * 2 + 1)) / 2);j++)
			{
				cout << ' ';
			}
			cout << endl;
		}
	}
	return 0;
}