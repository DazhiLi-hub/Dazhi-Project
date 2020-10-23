#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<iostream>
using namespace std;

class Polynomial
{
private:
	int coefficient[13];
	int size;
	void auto_size();
public:
	Polynomial();
	~Polynomial();
	void setCoe(int, int);
	int getCoe(int);
	int getSize();
	void setSize(int);
	friend ostream& operator<<(ostream& ouput, const Polynomial P);
	void operator=(const Polynomial P);
	Polynomial operator+(Polynomial P);
	void operator+=(Polynomial P);
	Polynomial operator-(Polynomial P);
	void operator-=(Polynomial P);
	Polynomial operator*(Polynomial P);
	void operator*=(Polynomial P);
};
#endif