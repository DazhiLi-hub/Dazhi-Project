#ifndef PACKAGE_H
#define PACKAGE_H
#include<string>
#include<iostream>
using namespace std;
struct member_info {
	string name;
	string address;
	string city;
	string state;
	string ZIP;
};
class Package 
{
protected:
	member_info sender;
	member_info recipient;
	double weight=0;
	double cost_per_ounce=0.5;
	const string type = "Regular Delivery";
public:
	Package(string, string, string, string, string, 
		string, string, string, string, string);
	virtual double calculateCost();
	member_info get_Sender_info();
	member_info get_Recipient_info();
	void set_weight(double);
	void set_cost_per_ounce(double);
	double get_weight();
	double get_cost_per_ounce();
	virtual string get_type();
};

#endif 
