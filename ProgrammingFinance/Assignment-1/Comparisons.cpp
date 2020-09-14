#include<iostream>
#include<iomanip>
#include<string.h>
#include<climits>
//announce standard library for C++
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::setw;

//Main funcetion: Compare 5 numbers
int main()
{
	int numbers[5]; //Create a number array which can holds 5 numebrs
	int i=0; //Create an index for user to input
	int maximum=INT_MIN, minimum=INT_MAX;
	cout << "Please enter 5 numbers here: ";
	while(cin >> numbers[i])
	{
		char ch=getchar();
		if (ch=='\n') //End input with an enter
		{
			break;
		}
		i++;
	}
	for (int i=0;i<5;i++)
	{
		if(numbers[i]>=maximum)
		{
			maximum=numbers[i];
		}
		if(numbers[i]<=minimum)
		{
			minimum=numbers[i];
		}
	}
	cout << "The biggest number among your inputs is: " << maximum << endl;
	cout << "The smallest number among your inputs is: " << minimum << endl;
	return 0;
}
