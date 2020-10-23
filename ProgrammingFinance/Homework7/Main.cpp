#include"Polynomial.h"

bool valid_size(int size)
{
	if (size > 0 && size < 7)
		return true;
	else
		return false;
}

int main(void)
{
	char sample;
	Polynomial first;
	Polynomial second;
	cout << "Would you like using the sample data?(y/n):";
	cin >> sample;
	if (sample == 'y' || sample == 'Y')
	{
		first.setSize(2);
		first.setCoe(2, 2);
		first.setCoe(3, 3);
		second.setSize(3);
		second.setCoe(1, 1);
		second.setCoe(2, 2);
		second.setCoe(3, 3);
	}
	else if (sample == 'n' || sample == 'N')
	{
		//Creating the first polynomial instance
		cout << "Enter the number of polynomial terms:";
		int size;
		cin >> size;
		if (!valid_size(size))
		{
			cerr << "Please enter a number larger than 0 but less than 6" << endl;
			cerr << "Please try again" << endl;
			return -1;
		}
		first.setSize(size);
		for (int i = 0;i < size;i++)
		{
			int coef, expo;
			cout << "\nEnter coefficientand and exponent" << endl
				<< "(first number input is coefficient"
				<< " second input is exponent)" << endl
				<<"(input example:x y) :";
			cin >> coef >> expo;
			if (!valid_size(expo))
			{
				cerr << "Invalid exponent input, enter a number larger than 0 but less than 6" << endl;
				cerr << "Please try again" << endl;
				i--;
			}
			else if (first.getCoe(expo)!=0)
			{
				cerr << "Your target exponent has already existed, please try agagin" << endl;
				i--;
			}
			else
			{
				first.setCoe(coef, expo);
			}
		}
		//Creating the second polynomial instance
		cout << "\nEnter the number of polynomial terms:";
		cin >> size;
		if (!valid_size(size))
		{
			cerr << "Please enter a number larger than 0 but less than 6" << endl;
			cerr << "Please try again" << endl;
			return -1;
		}
		second.setSize(size);
		for (int i = 0;i < size;i++)
		{
			int coef, expo;
			cout << "\nEnter coefficientand and exponent" << endl
				<< "(first number input is coefficient"
				<< " second input is exponent)" << endl
				<< "(input example:x y) :";
			cin >> coef >> expo;
			if (!valid_size(expo))
			{
				cerr << "Invalid exponent input, enter a number larger than 0 but less than 6" << endl;
				cerr << "Please try again" << endl;
				i--;
			}
			else if (second.getCoe(expo) != 0)
			{
				cerr << "Your target exponent has already existed, please try agagin" << endl;
				i--;
			}
			else
			{
				second.setCoe(coef, expo);
			}
		}
	}
	else
	{
		cerr << "Invalid Input, System abourted" << endl;
	}
	//Print out user's polynomial
	cout << "First polynomial is : " << first << endl;
	cout << "Second polynomial is : " << second << endl;
	cout << "Creating a new Polynomial third by using 'third=first'" << endl;
	Polynomial third = first;
	cout << "Third polynomial is: " << third << endl;
	cout << "Adding polynomial yields: " << first + second << endl;
	third += second;
	cout << "+= the polynomial yields: " << third << endl;
	third = first;
	cout << "Subtracting the polynomial yield :" << first-second << endl;
	third -= second;
	cout << "-= the polynomials yields : " << third << endl;
	third = first;
	cout << "Multiplying the polynomials yields: " << first * second << endl;
	third *= second;
	cout << "*= the polynomial yields: " << third << endl;
	return 0;
}