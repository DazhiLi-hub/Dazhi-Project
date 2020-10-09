#include<iostream>
#include<sstream>
#include<string>
using namespace std;

int puzzle_jump(int* array, int index)
{
	int result,num,array_len=0;
	while (array[array_len] != 0)
	{
		array_len++;
	}
	if (array[index] == 0)
	{
		return 0;
	}
	else if (array[index]==-1)
	{
		return -1;
	}
	else
	{
		num = array[index];
		array[index] = -1;
		if (num > index)
		{
			if (index + num > array_len)
			{
				return -1;
			}
			else
			{
				result=puzzle_jump(array, index + num);
				if (result == 0)
					return 0;
				else if (result == -1)
					return -1;
			}
		}
		else if (index + num > array_len)
		{
			if (num > index)
			{
				return -1;
			}
			else
			{
				result=puzzle_jump(array, index - num);
				if (result == 0)
					return 0;
				else if (result == -1)
					return -1;
			}
		}
		else
		{
			result=puzzle_jump(array, index + num);
			if (result == 0)
				return 0;
			result=puzzle_jump(array, index - num);
			if (result == 0)
				return 0;
			else if (result == -1)
				return -1;
		}
	}
}

int main(void)
{
	char test;
	cout << "Would you like use prepared testing data?[y/n]:";
	cin >> test;
	int* puzzle;
	if (test == 'y' || test == 'Y')
	{
		int array[5] = { 3, 3, 2, 2, 0 };
		puzzle = array;
		cout << "The example array is [3, 3, 2, 2, 0]" << endl;
	}
	else if(test=='n'||test=='N')
	{
		int num,array_len=0;
		cout << "Please input your array here:(space as intervals):" << endl;
		cout << "(Please remember the last number must be 0, the other numbers must be positve)" << endl;
		string your_string = "\n";
		getline(cin, your_string);
		getline(cin, your_string);
		stringstream ss(your_string),ss_input(your_string);
		while (ss >> num)
		{
			array_len++;
		}
		puzzle = new int[array_len];
		array_len = 0;
		while (ss_input >> num)
		{
			puzzle[array_len] = num;
			array_len++;
		}
		if (puzzle[array_len - 1] != 0)
		{
			cerr << "Your last number is not 0, invalid input" << endl;
			return -1;
		}
		for (int i = 0; i < array_len - 1;i++)
		{
			if (puzzle[i] <= 0)
			{
				cerr << "Your array has non-positive number, invalid input" << endl;
				return -1;
			}
		}
	}
	else
	{
		cerr << "Invalid input" << endl;
		return -1;
	}
	int result=puzzle_jump(puzzle, 0);
	if (result == 0)
	{
		cout << "Your input array can be solved" << endl;
	}
	else if (result == -1)
	{
		cout << "Your input array cannot be solved" << endl;
	}
}