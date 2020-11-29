/*
#include <iostream>
#include <list>//Import STL container list
//List is actually doubly linked list

using namespace std;

int main(void)
{
	list<char> my_List;//Instantiate a list like using class templete
	//my_List should contains char type data

	for (char c = 'a'; c <= 'z'; ++c)
		my_List.push_back(c);//insert variable c at the end of my_List
	//By using a loop to create a list contains a to z alphabet

	while (!my_List.empty())//.empty() function will return back bool value
	//empty() will return true if my_List is empty
	{
		cout << my_List.front() << " ";//Print our the first value in my_List
		my_List.pop_front();//pop out the first value from my_List
	}
	//At the end of the loop, all the values will be pop out and left an empty list

	return 0;
}
*/

/*
#include <iostream>
#include <vector>//Import STL container vector and its iterator
using namespace std;
int main()
{
	vector<int> my_vector;  
	//my vector will store int type data and does not have a fixed length

	for (int n = 0; n < 5; ++n)
		my_vector.push_back(n);  
	//push_back()member function will push
	//numbers 0 to 5 into the vector container

	vector<int>::iterator my_iterator;  
	//Create a vector int type iterator my_iterator
	
	for (my_iterator = my_vector.begin(); 
		my_iterator != my_vector.end(); 
		++my_iterator) 
	{  //Using iterator to visit each element in my_vector

		cout << *my_iterator << " ";  //iterator is actually a pointer
		//*my_vector is going to visit the element my_vector is pointing at
		*my_iterator *= 2;  //Double each element
	}
	cout << endl;

	vector<int>::reverse_iterator my_reverse_iterator;
	//Creating a reverse iterator
	for (my_reverse_iterator = my_vector.rbegin(); 
		my_reverse_iterator != my_vector.rend(); 
		++my_reverse_iterator)
		cout << *my_reverse_iterator << " ";
	//Print out the iterator pointing element from the end to the beginning
	return 0;
}
*/

/*
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int main() {
	vector<int> my_vector;
	for (int n = 1; n < 5; ++n)
		my_vector.push_back(n);//my_vector includes 1,2,3,4
	vector<int>::iterator my_iterator; //Create an iterator for my_vector

	my_iterator = find(my_vector.begin(), my_vector.end(), 3);
	//Find element 3 in my_vector
	//If exist, return the iterator where 3 is

	if (my_iterator != my_vector.end()) 
		//If find algorithm cannot find target, it will return my_vector.end()
		//Notice that my_vector.end() does not point to the end of numbers
		//my_vector.end()-1 points to 4
		//my_vector.end() points to the end of container which store no element.
		cout << *my_iterator << " is founded" << endl; //Find number 3 in my_vector

	my_iterator = find(my_vector.begin(), my_vector.end(), 9);
	if (my_iterator == my_vector.end())
		cout << "9 is not found " << endl; //Did not find 9 in my_vector

	my_iterator = find(my_vector.begin() + 1, my_vector.end() - 1, 4); 
	//Find 4 from the second element of my_vector(2) to the last element(4)
	//Notice my_vector.begin() really points to the begin of the container
	//my_vector.begin() points at number 1

	cout << *my_iterator << " is found beween 2 to 4" << endl;

	int my_array[10] = { 10,20,30,40 };
	int* my_pointer = find(my_array, my_array + 4, 20);
	//Even without container and iterator, algorithm could still be used
	//Be careful about the data type and pointer data type
	if (my_array == my_array + 4)
		//my_array+4 is the same way as my_vector.end()
		cout << "not found" << endl;
	else
		cout << *my_pointer << " is founded from my_array" << endl;
}
*/

#include<iostream>
using namespace std;
int main()
{
	auto basicLambda = [] { cout << "Hello, world!" << endl; };
	basicLambda();
	/* In this case we create a lambda expression without any
	captures or parameters, simply show how lambda expression
	achieve functional part
	*/

	auto add = [](int a, int b) -> int { return a + b; };
	// auto will automatically adjust the return type
	// In this case, the return type is int
	auto multiply = [](int a, int b) { return a * b; };
	int sum = add(2, 5);
	int product = multiply(2, 5);
	cout << "The sum of 2 and 5 is: " << sum << endl;
	cout << "The product of 2 and 5 is: " << product << endl;
	/* In this code part we are showing you how does parameters and
	return type work in lambda expression
	*/

	int x = 10;
	auto add_x = [x](int a) { return a + x; };
	//Capture part will capture variable x, then x could be used in body part
	auto multiply_x = [&x](int a) { return a * x; };
	// In this case lambda expression will capture the reference of x
	cout << "x add 10 is: " << add_x(10) << endl;
	cout << "x multiply 10 is: " << multiply_x(10) << endl;
	/* In this part we are showing how does capture part works.
	Lambda expression could capture many types like reference, data copy etc.
	Programmers could choose what to capture by their design need.
	*/

	auto change_x_add = [x](int a) mutable { x *= 2; return a + x; };
	//copy capture x
	cout << "Double x and add 10 is: " << change_x_add(10) << endl;
	return 0;
	/* This code part is going to show us that, by using copy capture 
	the lambda expression is similar to const type. If we want to change
	the copy of x, we need to add mutable identifier
	If we directly use copy capture x multiply 2, compiler error occurs.
	*/
}