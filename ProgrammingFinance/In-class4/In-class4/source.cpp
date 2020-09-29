#include<iostream>

using namespace std;

int countBinStr(int n)
{
	int sum=0;
	if (n == 0)
	{
		sum = 1;
	}
	else if (n == 1)
	{
		sum = 2;
	}
	else
	{
		sum = countBinStr(n - 1) + countBinStr(n-2);
	}
	return sum;
}
int main(void)
{
	int Bin_length;
	int Result;
	cout << "Please enter a valid positive integer to show your binary length:";
	cin >> Bin_length;
	if (Bin_length <= 0)
	{
		cerr << "Invalid input, please try enter a number larger than 0" << endl;
		return -1;
	}
	else
	{
		Result=countBinStr(Bin_length);
		cout << "The number of binary strings of length " << Bin_length
			<< " that do not contain two consecutive 0 is " << Result << endl;
		return -1;
	}
}