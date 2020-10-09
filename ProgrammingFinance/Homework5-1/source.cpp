#include<iostream>
#include<math.h>
using namespace std;

int recursive_suqare(int m,int n,bool change)

{
	int end = n;
	if (n % 2 == 1)
	{
		end = n - 1;
	}
	else if (n % 2 == 0&&m==n&&change==false)
	{
		return recursive_suqare(m - 1, n,change);
	}
	if (m == -1)
	{
		if (end==0)
		{
			return 0;
		}
		else
		{
			change = true;
			return recursive_suqare(m + 3, n,change);
		}
	}
	else if (m % 2 == 1)
	{
		if (n == 1)
		{
			cout << pow(m, 2) ;
		}
		else
		{
			cout << pow(m, 2) << ",";
		}
		return recursive_suqare(m - 2, n,change);
	}
	else if (m % 2 == 0)
	{
		if (m == end)
		{
			cout << pow(m, 2);
			return 0;
		}
		else
		{
			cout << pow(m, 2)<<",";
			return recursive_suqare(m + 2, n,change);
		}
	}
}

int main(void)
{
	int num;
	cout << "Please input a positive integer:";
	cin >> num;
	if (num <= 0)
	{
		cerr << "Your input is invalid, please try again" << endl;
		return -1;
	}
	recursive_suqare(num,num,false);
	return 0;
}