#include<iostream>
#include<deque>
#include<algorithm>
#include<iomanip>
#include<functional>
#include<numeric>
#include<iterator>
using namespace std;

const void show_deque(deque<int> A)
{
	deque<int>::iterator it;
	for (it = A.begin(); it != A.end(); it++)
	{
		cout << setw(3)<< *it ;
	}
	cout << endl;
}

const void print_half(int i)
{
	cout << setw(3) << i / 2;
}

bool greater_than_6(int i)
{
	if (i > 6)
		return true;
	else
		return false;
}

int main(void)
{
	deque<int> my_deque;
	deque<int>::iterator deque_it;
	//Inserting numbers
	my_deque.insert(my_deque.end(), 3);
	my_deque.insert(my_deque.end(), 4);
	my_deque.insert(my_deque.end(), 6);
	my_deque.insert(my_deque.end(), 2);
	my_deque.insert(my_deque.end(), 9);
	my_deque.insert(my_deque.end(), 1);
	my_deque.insert(my_deque.end(), 5);
	my_deque.insert(my_deque.end(), 0);
	my_deque.insert(my_deque.end(), 7);
	my_deque.insert(my_deque.end(), 8);
	cout << "The original deque contains:" << endl;
	show_deque(my_deque);
	//remove number 7
	my_deque.erase(remove(my_deque.begin(), my_deque.end(), 7), my_deque.end());
	cout << "After remove all the numbers equal to 7, the deque contains:" << endl;
	show_deque(my_deque);
	//replace > 6
	replace_if(my_deque.begin(), my_deque.end(), greater_than_6, 10);
	cout << "After replacing all the elements greater than 6 with 10, the deque contains:" << endl;
	show_deque(my_deque);
	//sum of deque
	int sum = accumulate(my_deque.begin(), my_deque.end(), 0);
	cout << "The sum of the deque is: " << sum << endl;
	my_deque.insert(my_deque.begin(), sum);
	cout << "After inserting the sum at the begining of the deque, the deque contains:" << endl;
	show_deque(my_deque);
	// Use STL algorithms to count the number of elements in the deque 
	//that are greater than 6 and print out the count.
	int mycount = count_if(my_deque.begin(), my_deque.end(), greater_than_6);
	cout << "Now the number of elements greater than 6 is: " << mycount << endl;
	//Use STL algorithms to output the half(integer division) of 
	//every element in the deque. (Do not modify the elements in the deque.)
	cout << "The half of every element in the deque is: " << endl;
	for_each(my_deque.begin(), my_deque.end(), print_half);
	cout << endl;
	//Use STL algorithms to sort the deque.
	sort(my_deque.begin(), my_deque.end());
	cout << "The sorting result is: " << endl;
	show_deque(my_deque);
	//Use the STL algorithms to find the location of 6 in 
	//the deque and print out the location.
	cout << "After sorting, the location of 6 is at index: " << my_deque.at(6) << endl;
	// Use the ostream_iterator and the copy algorithm to print out the deque 
	//elements with a comma in between the numbers.  The last element can 
	//also have a comma after it.  
	ostream_iterator<int> out(cout<<setw(3), ", ");
	copy(my_deque.begin(), my_deque.end(), out);
	return 0;
}