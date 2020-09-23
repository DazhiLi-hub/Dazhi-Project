#include<iostream>
#include<sstream>
#include<string>
#include<iomanip>

using namespace std;
//Creating a numer to receive user's input
int choice;
//Creating a class to store matrix information
class TD_Matrix
{
public:
	int row;
	int column;
	int** value;
	bool exist;
	TD_Matrix(int** mtx,int rows, int columns,bool exists);
};

TD_Matrix::TD_Matrix(int** mtx,int rows, int columns,bool exists)
{
	value = mtx;
	row = rows;
	column = columns;
	exist = exists;
}

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

/*This function will generate a random martrix based on user's input
The return type is class TD_Matrix 
If user's matrix is larger than 10 x 10, function will through out a failed generated matrix
If user's input does not fit matrix sizez, function will through out a failed generated matrix
This function will print user's input as a matrix on the screen */

TD_Matrix Gen_random_martrix()
{
	int row, column;
	//Create a failed generated martrix to be returned when matrix not generated
	int** failed=0;
	int failed_row = 0, failed_column = 0;
	TD_Matrix failed_one(failed, failed_row, failed_column, false);
	cout << "Please enter the number of row: ";
	cin >> row;
	if (row > 10)
	{
		cerr << "Please enter a matrix smaller than 10 x 10" << endl;
		return failed_one;
	}
	cout << "Please enter the number of column: ";
	cin >> column;
	if (column > 10)
	{
		cerr << "Please enter a matrix no larger than 10 x 10" << endl;
		return failed_one;
	}
	int* *mtx=new int*[row];
	for (int i = 0;i < row;i++)
	{
		mtx[i] = new int[column];
	}
	cout << "Please enter the values of elements:(Use space as interval, enter to continue)" << endl;
	//Creating a string for user to input
	string tmp="\n";
	getline(cin, tmp);
	//Empty the cache while using cin and getline
	getline(cin, tmp);
	//ss for counting the number of elements, ss_input for transfering values to the matrix
	stringstream ss(tmp),ss_input(tmp);
	int num,count=0;
	while (ss >> num)
	{
		count++;
	}
	//Judge if user's input is smaller or larger than the matrix size
	if (count < row * column)
	{
		cerr << "Your input is smaller than your expected matrix size, please try agagin" << endl;
		return failed_one;
	}
	else if (count > row * column)
	{
		cerr << "Your input is larger than your expected matrix size, please try agagin" << endl;
		return failed_one;
	}
	//If  the element number and matrix size are correct, give value to the matrix
	else
	{
		//reset count to 0
		count = 0;
		while (ss_input >> num)
		{
			mtx[count / column][count % column] = num;
			count++;
		}
	}
	TD_Matrix matrix(mtx, row, column,true);
	cout << "Your input is:" << endl;
	/* Naive way to get user input
	for (int i = 0;i < row ; i++)
	{
		for (int j = 0;j < column;j++)
		{
			cin >> mtx[i][j];
		}
	}
	*/
	for (int i = 0;i < row; i++)
	{
		for (int j = 0;j < column;j++)
		{
			cout <<setw(8)<< mtx[i][j];
		}
		cout << endl;
	}
	return matrix;
}

/*This function will delete group member of TD_Matrix
The group member name is value, which store the matrix
it need to be deleted because it is created on heap*/

int Delete_Matrix(TD_Matrix A)
{
	//Release memory in heap
	for (int j = 0;j < A.row;j++)
	{
		delete[] A.value[j];
	}
	delete[] A.value;
	return 0;
}

int Addition(TD_Matrix A, TD_Matrix B)
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

int Subtraction(TD_Matrix A, TD_Matrix B)
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

int Multiplication(TD_Matrix A, TD_Matrix B)
{
	//Judge if multiplication could be executed
	if (A.column != B.row)
	{
		cerr << "The columns of the 1st_matrix does not match the row of the 2nd_matrix";
		cerr <<	", operation cannot be executed" << endl;
		return -1;
	}
	//Do multiplication
	int** mtx = new int* [A.row];
	for (int i = 0;i < A.row;i++)
	{
		mtx[i] = new int[B.column];
	}
	TD_Matrix C(mtx, A.row, B.column, true);
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
	Delete_Matrix(C);
	return 0;
}

int Transpose(TD_Matrix A)
{
	int** mtx = new int* [A.column];
	for (int i = 0;i < A.column;i++)
	{
		mtx[i] = new int[A.row];
	}
	TD_Matrix B(mtx, A.column, A.row, true);
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
	Delete_Matrix(B);
	return 0;
}

int Determinant(TD_Matrix A)
{
	if (A.row != 3 || A.column != 3)
	{
		cerr << "Matrix is not 3 x 3, operation closed" << endl;
		return -1;
	}
	int sum_1,sum_2,det;
	sum_1 = A.value[0][0] * A.value[1][1] * A.value[2][2] + A.value[0][1] * A.value[1][2] * A.value[2][0] + A.value[0][2] * A.value[1][0] * A.value[2][1];
	sum_2 = A.value[0][2] * A.value[1][1] * A.value[2][0] + A.value[0][1] * A.value[1][0] * A.value[2][2] + A.value[0][0] * A.value[1][2] * A.value[2][1];
	det = sum_1 - sum_2;
	cout << "The result is:" << endl;
	cout << "Det|Your Matrix|=" << det << endl;
	return 0;
}

int Inverse(TD_Matrix A)
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
			TD_Matrix matrix_1=Gen_random_martrix();
			//If user gives invalid inputs which will not generate a matrix
			//Program will directly return back to the menu
			if (!matrix_1.exist)
			{
				break;
			}
			TD_Matrix matrix_2 = Gen_random_martrix();
			if (!matrix_2.exist)
			{
				break;
			}
			Addition(matrix_1,matrix_2);
			//Release memory
			Delete_Matrix(matrix_1);
			Delete_Matrix(matrix_2);
			break;
		}
		case 2: {
			TD_Matrix matrix_1 = Gen_random_martrix();
			if (!matrix_1.exist)
			{
				break;
			}
			TD_Matrix matrix_2 = Gen_random_martrix();
			if (!matrix_2.exist)
			{
				break;
			}
			Subtraction(matrix_1,matrix_2);
			Delete_Matrix(matrix_1);
			Delete_Matrix(matrix_2);
			break;
		}
		case 3: {
			TD_Matrix matrix_1 = Gen_random_martrix();
			if (!matrix_1.exist)
			{
				break;
			}
			TD_Matrix matrix_2 = Gen_random_martrix();
			if (!matrix_2.exist)
			{
				break;
			}
			int matrix_multiplication;
			bool exchange=false;
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
				Multiplication(matrix_2, matrix_1);
			}
			else
			{
				Multiplication(matrix_1, matrix_2);
			}
			Delete_Matrix(matrix_1);
			Delete_Matrix(matrix_2);
			break;
		}
		case 4: {
			TD_Matrix matrix_1 = Gen_random_martrix();
			if (!matrix_1.exist)
			{
				break;
			}
			Transpose(matrix_1);
			Delete_Matrix(matrix_1);
			break;
		}
		case 5: {
			cout << "In this oeperation, only 3 x 3 matrix would be acceptable" << endl;
			cout << "Otherwise, matrix larger or smaller will not be executed!" << endl;
			TD_Matrix matrix_1 = Gen_random_martrix();
			Determinant(matrix_1);
			break;
		}
		case 6: {
			cout << "In this oeperation, only 3 x 3 matrix would be acceptable" << endl;
			cout << "Otherwise, matrix larger or smaller will not be executed!" << endl;
			TD_Matrix matrix_1 = Gen_random_martrix();
			Inverse(matrix_1);
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