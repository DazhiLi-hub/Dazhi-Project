#ifndef TWODATPACKAGE_H
#define TWODAYPACKAGE_H
#include "package.h"
class TwodayPackage :public Package
{
private:
	double flat_fee_per_ounce=2;
	const string type = "Two Day Delivery";
public:
	TwodayPackage(string, string, string, string, string
		, string, string, string, string, string,double=2);
	virtual double calculateCost() override;
	void set_flat_fee_per_ounce(double);
	double get_falt_fee_per_ounce();
	virtual string get_type();
};
#endif
