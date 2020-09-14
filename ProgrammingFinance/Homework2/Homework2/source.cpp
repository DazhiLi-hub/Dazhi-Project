#include <iostream>
#include <fstream>
#include<ctime>
#include<climits>
#include<math.h>

using std::ofstream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
int random_num;


int main(void) 
{
	cout << "Please enter a positive integer to show how many points you want to generate: ";
	cin >> random_num;
	if (random_num <= 0)
	{
		cerr << "Invalid input, System aborted, Error code -1" << endl;
	}
	int x, y;
	//calculating radius
	int radius = RAND_MAX;
	int diagonal = sqrt(2) * radius;
	int shaded_count=0;
	//Giving seed to rand function
	srand(time(0));
	//writing files to txt
	ofstream file;
	file.open("myfile.txt");
	for (int i = 0;i < random_num;i++)
	{
		x = rand();
		y = rand();
		file << x << "," << y << "\n";
		int distance = sqrt(pow(x, 2) + pow(y, 2));
		//Judge if the point is in the circle
		if (distance <= radius)
		{
			shaded_count++;
		}
	}
	double pi = 4 * (double(shaded_count)/ double(random_num));
	cout << "The estimated pi is: " << pi << endl;
	return 0;
	/*
	ofstream file;
	//opens the file myfile.txt
	file.open("myfile.txt");
	//for loop to write the values to the file
	for (int i = 0;i < 100;i++) {
		file << i << "," << i + 5 << "\n";
	}
	cout << "Printed numbers to file myfile.txt\n";
	*/
}