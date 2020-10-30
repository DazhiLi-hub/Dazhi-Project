#include "All.h"
#include<math.h>
void Two_Dimensional_Shape :: setCenter(double x, double y)
{
	center_x = x;
	center_y = y;
	return;
}

void Circle::setRadius(double r)
{
	radius = r;
	return;
}

void Circle::getArea()
{
	area = PI * pow(radius, 2);
	return;
}

ostream& operator<<(ostream& output, const Circle& A)
{
	output << "The circle with radius " << A.radius << " that is located at "
		<< "( " << A.center_x << "," << A.center_y << " ) has:" << endl
		<< "An area of: " << A.area << endl;
	return output;
}

void Triangle::setLength(double l)
{
	length = l;
	return;
}

void Triangle::getArea()
{
	area = sqrt(3) / double(4) * pow(length, 2);
	return;
}

ostream& operator<<(ostream& output, const Triangle A)
{
	output << "The equilateral triangle with length " << A.length << " that is located at "
		<< "( " << A.center_x << "," << A.center_y << " ) has:" << endl
		<< "An area of: " << A.area << endl;
	return output;
}

void Three_Dimensional_Shape::setCenter(double x, double y, double z)
{
	center_x = x;
	center_y = y;
	center_z = z;
	return;
}

void Sphere::setRadius(double r)
{
	radius = r;
	return;
}

void Sphere::getArea()
{
	area = double(4) * PI * pow(radius, 2);
	return;
}

void Sphere::getVolume()
{
	volume = double(4) / double(3) * PI * pow(radius, 3);
	return;
}

ostream& operator<<(ostream& output, const Sphere A)
{
	cout << "The sphere with radius " << A.radius << " at location ( "
		<< A.center_x << "," << A.center_y << "," << A.center_z << " ) has:" << endl
		<< "Surface area of: " << A.area << endl
		<< "Volume of: " << A.volume << endl;
	return output;
}

void Regular_Tetrahedron::setLength(double l)
{
	length = l;
	return;
}

void Regular_Tetrahedron::getArea()
{
	area = sqrt(3) * pow(length, 2);
	return;
}

void Regular_Tetrahedron::getVolume()
{
	volume = sqrt(2) / double(12) * pow(length, 3);
	return;
}

ostream& operator<<(ostream& output, const Regular_Tetrahedron A)
{
	cout << "The regular tetrahedron with edge length " << A.length << " at location ( "
		<< A.center_x << "," << A.center_y << "," << A.center_z << " ) has:" << endl
		<< "Surface area of: " << A.area << endl
		<< "Volume of: " << A.volume << endl;
	return output;
}