#include<iostream>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
// layers to restore how many layers the printed shape could be 
int layers;

int main(void)
{
	cout << "Please enter a positive integer here(Use Enter to continue): ";
	cin >> layers;
	//Give a judement on if the user follow the above direction
	if (layers <= 0)
	{
		//Error message will be printed out if the user input a negative integer or character
		cout << "The number of your input is invalid, please try again" << endl;
		cerr << "System aborted; Erroe code -1";
		return -1;
	}
	cout << "The printed triangle based on your input is:" << endl;
	//Do the for loop for printing out triangle shape
	for (int i = 0;i < layers; i++)
	{
		for (int j = 0;j <= i;j++)
		{
			cout << '*';
		}
		cout << endl;
	}
	return 0;
}