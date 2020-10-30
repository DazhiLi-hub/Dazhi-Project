#ifndef ALL_H
#define ALL_H
#define PI 3.1415926
#include <iostream>
using namespace std;

class shape 
{
protected:
	double center_x;
};

class Two_Dimensional_Shape :public shape
{
protected:
	double center_y;
	double area;
public:
	void setCenter(double, double);
};

class Circle :public Two_Dimensional_Shape
{
private:
	double radius;
public:
	void setRadius(double);
	void getArea();
	friend ostream& operator<<(ostream& output,const Circle& A);
};

class Triangle :public Two_Dimensional_Shape
{
private:
	double length;
public:
	void setLength(double);
	void getArea();
	friend ostream& operator<<(ostream& output, const Triangle A);
};

class Three_Dimensional_Shape :public shape
{
protected:
	double center_y;
	double center_z;
	double area;
	double volume;
public:
	void setCenter(double, double, double);
};

class Sphere :public Three_Dimensional_Shape
{
private:
	double radius;
public:
	void setRadius(double);
	void getArea();
	void getVolume();
	friend ostream& operator<<(ostream& output, const Sphere A);
};

class Regular_Tetrahedron :public Three_Dimensional_Shape
{
private:
	double length;
public:
	void setLength(double);
	void getArea();
	void getVolume();
	friend ostream& operator<<(ostream& output, const Regular_Tetrahedron A);
};
#endif