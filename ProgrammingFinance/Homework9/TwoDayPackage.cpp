#include "TwoDayPackage.h"

TwodayPackage::TwodayPackage(string sname, string saddress, string scity,
	string sstate, string szip, string rname, string raddress,
	string rcity, string rstate, string rzip,double flat_rate)
	:Package(sname, saddress, scity, sstate, szip,
		rname, raddress, rcity, rstate, rzip)
{
	flat_fee_per_ounce = flat_rate;
}

double TwodayPackage::calculateCost()
{
	return (cost_per_ounce + flat_fee_per_ounce) * weight;
}

void TwodayPackage::set_flat_fee_per_ounce(double flat_rate)
{
	if (flat_rate > 0)
	{
		this->flat_fee_per_ounce = flat_rate;
	}
	else
	{
		throw invalid_argument("Please use a flat fee per ounce larger than 0");
	}
	return;
}
double TwodayPackage::get_falt_fee_per_ounce()
{
	return this->flat_fee_per_ounce;
}

string TwodayPackage::get_type()
{
	return this->type;
}