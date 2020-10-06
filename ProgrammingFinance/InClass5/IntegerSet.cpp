#include <iostream>
#include <iomanip>
#include "IntegerSet.h"
using namespace std;

/* Write include directive for IntegerSet.h here */

// constructor
IntegerSet::IntegerSet()
{
	for (int i = 0; i < 101; i++)
	{
		set[i] = 0;
	}
} // end IntegerSet constructor

// input a set from the user
void IntegerSet::inputSet()
{
	int number;
	do
	{
		cout << "Enter an element (-1 to end): ";
		cin >> number;

		if (validEntry(number))
		{
			set[number] = 1;
		}
		else if (number != -1)
		{
			cout << "Invalid Element\n";
		}
	} while (number != -1); // end do...while

	cout << "Entry complete\n";
} // end function inputSet

IntegerSet IntegerSet::UnionOfSets(IntegerSet B)
{
	IntegerSet C;
	for (int i = 0;i < 101;i++)
	{
		if (set[i] == 1 || B.set[i] == 1)
		{
			C.set[i] = 1;
		}
	}
	return C;
}

IntegerSet IntegerSet::IntersectionOfSets(IntegerSet B)
{
	IntegerSet C;
	for (int i = 0;i < 101;i++)
	{
		if (set[i] == 1 && B.set[i] == 1)
		{
			C.set[i] = 1;
		}
	}
	return C;
}

// prints the set to the output stream
void IntegerSet::printSet() const
{
	cout << "{ ";

	for (int u = 0; u < 101; u++)
	if (set[u]) cout << u << " ";

	cout << "}" << endl;
	} // end function printSet

	/* Write definition for unionOfSets */

	/* Write definition for intersectionOfSets */