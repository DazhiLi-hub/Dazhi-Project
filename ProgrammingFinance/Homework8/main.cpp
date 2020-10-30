#include "All.h"

void Display_menu(char& choice)
{
	cout << "Please choose a shape or 0 to exit: "<<endl;
	cout << "1. Circle" << endl;
	cout << "2. Triangle" << endl;
	cout << "3. Sphere" << endl;
	cout << "4. Regular Tetrahedron" << endl;
	cout << "0. Exit" << endl;
	cout << "Your choice: ";
	cin >> choice;
}

int main(void)
{
	char choice='1';
	while (choice != '0')
	{
		Display_menu(choice);
		double x, y, z;
		switch (choice)
		{
		case '0':
			cout << "System exit" << endl;
			break;
		case '1':
			Circle true_circle;
			cout << "Please enter the center of the circle (x-coordinate and then y-coordinate):" << endl;
			cin >> x >> y;
			true_circle.setCenter(x, y);
			cout << "Please enter the radius of the circle:" << endl;
			double r;
			cin >> r;
			if (r > 0)
			{
				true_circle.setRadius(r);
				true_circle.getArea();
				cout << true_circle;
			}
			else
			{
				cerr << "Invalid input, please try again" << endl;
			}
			break;
		case '2':
			Triangle true_triangle;
			cout << "Please enter the center of the triangle (x-coordinate and then y-coordinate):" << endl;
			cin >> x >> y;
			true_triangle.setCenter(x, y);
			cout << "Please enter the edge length of the triangle:" << endl;
			double l;
			cin >> l;
			if (l > 0)
			{
				true_triangle.setLength(l);
				true_triangle.getArea();
				cout << true_triangle;
			}
			else
			{
				cerr << "Invalid input, please try again" << endl;
			}
			break;
		case '3':
			Sphere true_sphere;
			double r_sphere;
			cout << "Please enter the center of the sphere (x-coordinate, y-coordinate, then z-coordinate):" << endl;
			cin >> x >> y >> z;
			true_sphere.setCenter(x, y, z);
			cout << "Please enter the radius of the sphere:" << endl;
			cin >> r_sphere;
			if (r_sphere > 0)
			{
				true_sphere.setRadius(r_sphere);
				true_sphere.getArea();
				true_sphere.getVolume();
				cout << true_sphere;
			}
			else
			{
				cerr << "Invalid input, please try again" << endl;
			}
			break;
		case '4':
			Regular_Tetrahedron true_tetrahedron;
			double l_tetrahedron;
			cout << "Please enter the center of the regular tetrahedron (x-coordinate, y-coordinate, then z-coordinate):" << endl;
			cin >> x >> y >> z;
			true_tetrahedron.setCenter(x, y, z);
			cout << "Please enter the edge length of the regular tetrahedron:" << endl;
			cin >> l_tetrahedron;
			if (l_tetrahedron > 0)
			{
				true_tetrahedron.setLength(l_tetrahedron);
				true_tetrahedron.getArea();
				true_tetrahedron.getVolume();
				cout << true_tetrahedron;
			}
			else
			{
				cerr << "Invalid input, please try again" << endl;
			}
			break;
		default:
			cerr << "Invalid input,please try again" << endl;
			break;
		}
	}
	return 0;
}