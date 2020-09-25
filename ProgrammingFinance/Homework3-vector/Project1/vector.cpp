#include<iostream>
#include<sstream>
#include<string>
#include<iomanip>
#include<vector>

using namespace std;
//Creating a numer to receive user's input
int choice;

//Display menu function
void DisplayMenu(void)
{
	cout << "Menu" << endl;
	cout << " Choice 1: Addition" << endl;
	cout << " Choice 2: Subtraction" << endl;
	cout << " Choice 3: Multiplication" << endl;
	cout << " Choice 4: Transpose" << endl;
	cout << " Choice 5: Determinant" << endl;
	cout << " Choice 6: Inverse" << endl;
	cout << " Choice 7: Quit" << endl;
	cout << " Enter your choice:";
	cin >> choice;
}

//Creating a class of two dimention vector
class TD_Vector{
public:
	vector<vector<int> >value;
	int row;
	int column;
	bool exist;
	TD_Vector(vector<vector<int> > vv, int rows, int columns, int exists);
	int get_Transpose(TD_Vector A);
	int get_Determinant(TD_Vector A);
	int get_Inverse(TD_Vector A);
};

TD_Vector::TD_Vector(vector<vector<int> > vv, int rows, int columns, int exists)
{
	value = vv;
	row = rows;
	column = columns;
	exist = exists;
}

TD_Vector Gen_random_vector()
{
	int row, column;
	//Create a failed generated TD_vector for wrong user's input
	vector<vector<int> > failed(0, vector <int>(0));
	TD_Vector failed_one(failed, 0, 0, false);
	//Ask user to input and judge if the TD_vector is smaller than 10 x 10
	cout << "Please enter the number of row: ";
	cin >> row;
	if (row > 10)
	{
		cerr << "Please enter a 2D vector smaller than 10 x 10" << endl;
		return failed_one;
	}
	cout << "Please enter the number of column: ";
	cin >> column;
	if (column > 10)
	{
		cerr << "Please enter a 2D vector no larger than 10 x 10" << endl;
		return failed_one;
	}
	vector<vector<int> > vv(row, vector<int>(column));
	cout << "Please enter the values of elements:(Use space as interval, enter to continue)" << endl;
	//Creating a string for user to input
	string tmp = "\n";
	getline(cin, tmp);
	//Empty the cache while using cin and getline
	getline(cin, tmp);
	//ss for counting the number of elements, ss_input for transfering values to the 2D vector
	stringstream ss(tmp), ss_input(tmp);
	int num, count = 0;
	while (ss >> num)
	{
		count++;
	}
	//Judge if user's input is smaller or larger than the 2D vector size
	if (count < row * column)
	{
		cerr << "Your input is smaller than your expected 2D vector size, please try agagin" << endl;
		return failed_one;
	}
	else if (count > row * column)
	{
		cerr << "Your input is larger than your expected 2D vector size, please try agagin" << endl;
		return failed_one;
	}
	//If  the element number and 2D vector size are correct, give value to the 2D vector
	else
	{
		//reset count to 0
		count = 0;
		while (ss_input >> num)
		{
			vv[count / column][count % column] = num;
			count++;
		}
	}
	TD_Vector Good_one(vv, row, column, true);
	cout << "Your input is:" << endl;
	for (int i = 0;i < Good_one.row; i++)
	{
		for (int j = 0;j < Good_one.column;j++)
		{
			cout << setw(8) << Good_one.value[i][j];
		}
		cout << endl;
	}
	return Good_one;
}

int Addition(TD_Vector A, TD_Vector B)
{
	//Judge if the operation could be executed
	if (A.row != B.row || A.column != B.column)
	{
		cerr << "Two matrix are not in the same size, operation cannot be executed!" << endl;
		return -1;
	}
	//If matrix size are the same, do the addition operation
	for (int i = 0;i < A.row;i++)
	{
		for (int j = 0;j < A.column;j++)
		{
			A.value[i][j] += B.value[i][j];
		}
	}
	//Print the result
	cout << "The result is:" << endl;
	for (int i = 0;i < A.row; i++)
	{
		for (int j = 0;j < A.column;j++)
		{
			cout << setw(8) << A.value[i][j];
		}
		cout << endl;
	}
	return 0;
}

int Subtraction(TD_Vector A, TD_Vector B)
{
	if (A.row != B.row || A.column != B.column)
	{
		cerr << "Two matrix are not in the same size, operation cannot be executed!" << endl;
		return -1;
	}
	for (int i = 0;i < A.row;i++)
	{
		for (int j = 0;j < A.column;j++)
		{
			A.value[i][j] -= B.value[i][j];
		}
	}
	cout << "The result is:" << endl;
	for (int i = 0;i < A.row; i++)
	{
		for (int j = 0;j < A.column;j++)
		{
			cout << setw(8) << A.value[i][j];
		}
		cout << endl;
	}
	return 0;
}

int Multiplication(TD_Vector A, TD_Vector B)
{
	//Judge if multiplication could be executed
	if (A.column != B.row)
	{
		cerr << "The columns of the 1st_matrix does not match the row of the 2nd_matrix";
		cerr << ", operation cannot be executed" << endl;
		return -1;
	}
	//Do multiplication
	vector<vector<int> > vv(A.row, vector<int>(B.column));
	TD_Vector C(vv, A.row, B.column, true);
	for (int i = 0;i < C.row;i++)
	{
		for (int j = 0; j < C.column;j++)
		{
			C.value[i][j] = 0;
			for (int k = 0; k < A.column;k++)
			{
				C.value[i][j] += A.value[i][k] * B.value[k][j];
			}
		}
	}
	//Print the result
	cout << "The result is:" << endl;
	for (int i = 0;i < C.row; i++)
	{
		for (int j = 0;j < C.column;j++)
		{
			cout << setw(8) << C.value[i][j];
		}
		cout << endl;
	}
	return 0;
}

int TD_Vector::get_Transpose(TD_Vector A)
{
	vector<vector<int> > vv(A.column, vector<int>(A.row));
	TD_Vector B(vv, A.column, A.row, true);
	//Do transpose
	for (int i = 0;i < B.row;i++)
	{
		for (int j = 0;j < B.column;j++)
		{
			B.value[i][j] = A.value[j][i];
		}
	}
	//Print result
	cout << "The result is:" << endl;
	for (int i = 0;i < B.row; i++)
	{
		for (int j = 0;j < B.column;j++)
		{
			cout << setw(8) << B.value[i][j];
		}
		cout << endl;
	}
	return 0;
}

int TD_Vector::get_Determinant(TD_Vector A)
{
	if (A.row != 3 || A.column != 3)
	{
		cerr << "Matrix is not 3 x 3, operation closed" << endl;
		return -1;
	}
	int sum_1, sum_2, det;
	sum_1 = A.value[0][0] * A.value[1][1] * A.value[2][2] + A.value[0][1] * A.value[1][2] * A.value[2][0] + A.value[0][2] * A.value[1][0] * A.value[2][1];
	sum_2 = A.value[0][2] * A.value[1][1] * A.value[2][0] + A.value[0][1] * A.value[1][0] * A.value[2][2] + A.value[0][0] * A.value[1][2] * A.value[2][1];
	det = sum_1 - sum_2;
	cout << "The result is:" << endl;
	cout << "Det|Your Matrix|=" << det << endl;
	return 0;
}

int TD_Vector::get_Inverse(TD_Vector A)
{
	if (A.row != 3 || A.column != 3)
	{
		cerr << "Matrix is not 3 x 3, operation closed" << endl;
		return -1;
	}
	int sum_1, sum_2, det;
	sum_1 = A.value[0][0] * A.value[1][1] * A.value[2][2] + A.value[0][1] * A.value[1][2] * A.value[2][0] + A.value[0][2] * A.value[1][0] * A.value[2][1];
	sum_2 = A.value[0][2] * A.value[1][1] * A.value[2][0] + A.value[0][1] * A.value[1][0] * A.value[2][2] + A.value[0][0] * A.value[1][2] * A.value[2][1];
	det = sum_1 - sum_2;
	//Judge if the matrix could be inversed
	if (det == 0)
	{
		cerr << "The determinant of your matrix is 0, this cannot be inversed" << endl;
		return -1;
	}
	//Creating the inversed matrix
	float B[3][3];
	//Calculating the inversed matrix
	B[0][0] = A.value[1][1] * A.value[2][2] - A.value[1][2] * A.value[2][1];
	B[0][1] = A.value[0][2] * A.value[2][1] - A.value[0][1] * A.value[2][2];
	B[0][2] = A.value[0][1] * A.value[1][2] - A.value[0][2] * A.value[1][1];
	B[1][0] = A.value[1][2] * A.value[2][0] - A.value[1][0] * A.value[2][2];
	B[1][1] = A.value[0][0] * A.value[2][2] - A.value[0][2] * A.value[2][0];
	B[1][2] = A.value[1][0] * A.value[0][2] - A.value[0][0] * A.value[1][2];
	B[2][0] = A.value[1][0] * A.value[2][1] - A.value[1][1] * A.value[2][0];
	B[2][1] = A.value[0][1] * A.value[2][0] - A.value[0][0] * A.value[2][1];
	B[2][2] = A.value[0][0] * A.value[1][1] - A.value[1][0] * A.value[0][1];
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			B[i][j] = B[i][j] / float(det);
		}
	}
	//Print result
	cout << "The result is:" << endl;
	for (int i = 0;i < 3; i++)
	{
		for (int j = 0;j < 3;j++)
		{
			cout << setw(8) << B[i][j];
		}
		cout << endl;
	}
	return 0;
}

int main(void)
{
	while (choice != 7)
	{
		DisplayMenu();
		switch (choice)
		{
		case 1: {
			TD_Vector vector_1 = Gen_random_vector();
			//If user gives invalid inputs which will not generate a matrix
			//Program will directly return back to the menu
			if (!vector_1.exist)
			{
				break;
			}
			TD_Vector vector_2 = Gen_random_vector();
			if (!vector_2.exist)
			{
				break;
			}
			Addition(vector_1, vector_2);
			break;
		}
		case 2: {
			TD_Vector vector_1 = Gen_random_vector();
			if (!vector_1.exist)
			{
				break;
			}
			TD_Vector vector_2 = Gen_random_vector();
			if (!vector_2.exist)
			{
				break;
			}
			Subtraction(vector_1, vector_2);
			break;
		}
		case 3: {
			TD_Vector vector_1 = Gen_random_vector();
			if (!vector_1.exist)
			{
				break;
			}
			TD_Vector vector_2 = Gen_random_vector();
			if (!vector_2.exist)
			{
				break;
			}
			int matrix_multiplication;
			bool exchange = false;
			cout << "Do you want the 1st_matrix * 2nd_matrix or 2nd_matrix * 1st_matrix ?" << endl;
			cout << "(1 for A * B, 2 for B * A, please input 1 or 2 for your decision):";
			while (cin >> matrix_multiplication)
			{
				if (matrix_multiplication == 1)
				{
					exchange = false;
					break;
				}
				else if (matrix_multiplication == 2)
				{
					exchange = true;
					break;
				}
				else
				{
					cerr << "Invalid input, please try again here:";
				}
			}
			if (exchange)
			{
				Multiplication(vector_2, vector_1);
			}
			else
			{
				Multiplication(vector_1, vector_2);
			}
			break;
		}
		case 4: {
			TD_Vector vector_1 = Gen_random_vector();
			if (!vector_1.exist)
			{
				break;
			}
			vector_1.get_Transpose(vector_1);
			break;
		}
		case 5: {
			cout << "In this oeperation, only 3 x 3 matrix would be acceptable" << endl;
			cout << "Otherwise, matrix larger or smaller will not be executed!" << endl;
			TD_Vector vector_1 = Gen_random_vector();
			vector_1.get_Determinant(vector_1);
			break;
		}
		case 6: {
			cout << "In this oeperation, only 3 x 3 matrix would be acceptable" << endl;
			cout << "Otherwise, matrix larger or smaller will not be executed!" << endl;
			TD_Vector vector_1 = Gen_random_vector();
			vector_1.get_Inverse(vector_1);
			break;
		}
		case 7: {
			return 0;
		}
		default:
			cerr << "Invalid input, please try again (Input between 1 to 7)" << endl;
			break;
		}
	}
	return 0;
}