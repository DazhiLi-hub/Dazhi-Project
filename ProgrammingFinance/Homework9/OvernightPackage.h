#ifndef OVERNIGHTPACKAGE_H
#define OVERNIGHTPACKAGE_H
#include "package.h"
class OvernightPackage :public Package
{
private:
	double flat_fee_per_ounce = 5;
	const string type = "Overnight Delivery";
public:
	OvernightPackage(string, string, string, string, string
		, string, string, string, string, string, double = 5);
	virtual double calculateCost() override;
	void set_flat_fee_per_ounce(double);
	double get_falt_fee_per_ounce();
	virtual string get_type();
};
#endif
