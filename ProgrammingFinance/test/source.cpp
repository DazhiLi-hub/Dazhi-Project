#include<iostream>
#include<iomanip>
#include<MatPlot.h>
#include<Windows.h>
#include<cmath>
using namespace std;//Global namespace
/*
int a=10;//Global variable

int SetValue();//Function Prototype

int main(void)
{//code block begins
	int b=100;//local variable, only accessible in main function
	cout << "This is a:"<< a << endl;
	cout << "This is b:" << b << endl;
	SetValue();
	cout << "This is a:" << a << endl;
	return 0;
}//code block ends

//b = 10; If you want to use variable b out of main function, error happened

int SetValue()
{//code block begins
	a = 100; //Global value could be accessed through the whole code
	return 0;
}//code block ends

*/

/*
int main()
{
	int a;//automatic variable a was created
	int b[3] = { 0,1,2 };
	//cout << "a is:" << a << endl; since a is not given a value, we cannot visit it
	cout << "the adress of a is:" << &a << endl;
	cout << "b[0] is:" << b[0] << endl;
	cout << "b[1] is:" << b[1] << endl;
	cout << "b[2] is:" << b[2] << endl;
	//cout << "b[3] is:" << b[3] << endl; this is a typical stack overflow
	return 0;
}
*/

/*
int PrintPoint(int a=0,int b=0)//Default parameters when function called
{
	cout << "The point of yours is (" << a << "," << b << ")" << endl;
	return 0;
}

int main(void)
{
	PrintPoint();
	PrintPoint(1);
	PrintPoint(3, 3);
}
*/

/*
inline int Max(int x, int y)//Inline function
{
	return (x > y) ? x : y;
}

int main()
{

	cout << "Max (20,10): " << Max(20, 10) << endl;
	cout << "Max (0,200): " << Max(0, 200) << endl;
	cout << "Max (100,1010): " << Max(100, 1010) << endl;
	return 0;
}
*/

/*
int pass_by_value(int a)
{
	a = 20;
	return 0;
}

int pass_by_reference(int& a)
{
	a = 20;
	return 0;
}

int main()
{
	int a = 10;
	cout << "A is:" << a << endl;
	pass_by_value(a);
	cout << "A is:" << a << endl;
	pass_by_reference(a);
	cout << "A is:" << a << endl;
	return 0;
}
*/

/*
int number = 7; // global variable named number
int main()
{
	double number = 10.5; // local variable named number
	cout << "Local double value of number = " << number << endl;
	cout << "Global int value of number = " << ::number << endl;
return 0; // indicates successful termination
} // end main
*/

/*
int print(int a)
{
	cout << "This is a int type " << a <<endl;
	return 0;
}

int print(float a)
{
	cout << "This is a float type " << a <<endl;
	return 0;
}

int main()
{
	print(int(10));
	print(float(0.1));
	return 0;
}
*/

/*
template <class myType> //Create a function template
myType GetMax(myType a, myType b) 
{
	return (a > b ? a : b);
}
int main()
{
	int a = 10, b = 5,c;
	float d;
	c = GetMax(a, b);
	cout<< "The larger number is:" << c << endl;
	//d = GetMax(10.5, b); Compiler error if you use two different types as templates
	return 0;
}
*/

/*
int fib(int n)
{
	if (n <= 1)
		return n;
	return fib(n - 1) + fib(n - 2);
}

int main()
{
	int n = 9;
	cout << n << " sequence fibonacci is: " << fib(n) << endl;
	return 0;
}
*/

/*
template< typename T > class array {
private:
	int size;
	T* myarray;
public:
	// constructor with user pre-defined size
	array(int s) {
		size = s;
		myarray = new T[size];
	}
	// calss array member function to set element of myarray 
	// with type T values
	void setArray(int elem, T val) {
		myarray[elem] = val;
	}

	// for loop to display all elements of an array
	void getArray() {
		for (int j = 0; j < size; j++) {
			// typeid will retriev a type for each value
			cout << setw(7) << j << setw(13) << myarray[j]
				<< " type: " << typeid(myarray[j]).name() << endl;
		}
		cout << "-----------------------------" << endl;
	}
};
int main()
{
	// instantiate int_array object of class array<int> with size 2
	::array< int > int_array(2);
	// set value to a first element
	// call to array class member function to set array elements
	int_array.setArray(0, 3);
	// set value to a second element
	// NOTE: any attempt to set float to an int array will be translated to int value
	int_array.setArray(1, 3.4);

	// call to array class member function to display array elements
	int_array.getArray();

	// instantiate float_array object of class array<float> with size 3
	::array< float > float_array(3);

	// set value to a first element
	// call to array class member function to set array elements
	float_array.setArray(0, 3.4);
	// set value to a second element
	float_array.setArray(1, 2.8);

	// call to array class member function to display array elements
	float_array.getArray();

	// instantiate float_array object of class array<char> with size 5
	::array< char > char_array(5);

	// set value to a first element
	// call to array class member function to set array elements
	char_array.setArray(0, 'H');
	// set value to a other array elements
	char_array.setArray(1, 'E');
	char_array.setArray(2, 'L');
	char_array.setArray(3, 'L');
	char_array.setArray(4, 'O');

	char_array.getArray();

	return 0;
}
*/

/*
int main(void)
{
	string Student_info[2][10];
	Student_info[0][0] = "Eric";
	Student_info[1][0] = "boy";
	Student_info[0][1] = "Alice";
	Student_info[1][1] = "girl";
	for (int i = 0;i < 2;i++)
	{
		for (int j = 0;j < 2;j++)
		{
			if (j == 0)
			{
				cout << "Student: " << Student_info[j][i] << " ";
			}
			else if (j == 1)
			{
				cout << "Sex: " << Student_info[j][i] << endl;
			}
		}
	}
}
*/

/*
int main(void)
{
	int i = 10;
	int* i_pointer;//Create a pointer
	i_pointer = &i;//Set the pointer pointing to variable i
	cout << "i is: " << i << endl;
	cout << "The addrss of i is: " << &i << endl;
	cout << "i_pointer is: " << i_pointer << endl;
	cout << "What i_pointer pointing is: " << *i_pointer << endl;
	return 0;
}
*/

/*
int main(void)
{
	double object;
	double* object_pointer;//First usage of "*": Setting pointer
	object_pointer = &object;//First usage of "&": Use the address of an object
	object = 11.1;
	cout << "The object value of object_pointer pointing is: " << *object_pointer << endl;
	//Second usage of "*": Visiting the value of the object where pointer pointing at
	double& object_alia = object;//Second usage of "&": Creating a reference to an object
	cout << "The address of object is: " << &object << endl;
	cout << "The address of object_alia is: " << &object_alia << endl;
	cout << "The value of object_alia is: " << object_alia << endl;
	return 0;
}
*/

/*
int main(void)
{
	string A = "Have fun, Good luck";
	int B[6] = { 0,3,9,8,5,2 };
	string* A_pointer;
	A_pointer = &A;
	int* B_pointer;
	B_pointer = B;
	cout << "A_pointer is:" << *A_pointer << endl;
	//A_pointer++; Compiler error happened
	//String pointer only have one pointer pointing at the whole string;
	cout << "B_pointer is: " << *B_pointer << endl;
	cout << "B address is: " << B_pointer << endl;
	B_pointer++;//Pointer arithmetic
	cout << "B_pointer next is:" << *B_pointer << endl;
	cout << "B next address is: " << B_pointer << endl;
	cout << "The size of one int is: " << sizeof(B[0]) << endl;
	return 0;
}
*/

/*
class box
{
public:
	static int objectcount;//Creating static class member
	box()
	{
		objectcount++;
	}
	static int get_box_count()
	{
		return objectcount;
	}
};
int box::objectcount = 0;//Initial the box count value
int main(void)
{
	cout << "The number of boxes initialized are: " << box::get_box_count() << endl;
	//Usually we can visit the static class member via "::"
	box box_1;
	box box_2;
	cout << "The number of boxes are: " << box::get_box_count() << endl;
	//We can also use static member function via "::"
	//Static member function could only use static member variable,other
	//(Cont'd)static member function and other functions outside of the class
	return 0;
}
*/

/*
int main(void)
{
	cout << "The value of super is: " << super << endl;
	return 0;
}
*/

int main(void)
{
	double x[5]{ 1,2,3,4,5 };
	double y[5]{ 1,3,2,4,3 };
	int N{ 5 };
	MatPlot::MatPlotInit();
	MatPlot::plot(x, y, N);
	Sleep(3000);
	MatPlot::MatPlotClose();
	cout << "Finished" << endl;
	return 0;
}