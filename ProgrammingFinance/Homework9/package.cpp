#include"package.h"

Package::Package(string sname, string saddress, string scity, string sstate, string szip,
	string rname, string raddress, string rcity, string rstate, string rzip)
{
	sender.name = sname;
	sender.address = saddress;
	sender.city = scity;
	sender.state = sstate;
	sender.ZIP = szip;
	recipient.name = rname;
	recipient.address = raddress;
	recipient.city = rcity;
	recipient.state = rstate;
	recipient.ZIP = rzip;
}

double Package::calculateCost()
{
	return weight * cost_per_ounce;
}

member_info Package::get_Sender_info()
{
	return this->sender;
}

member_info Package::get_Recipient_info()
{
	return this->recipient;
}

void Package::set_weight(double weight)
{
	if (weight <= 0)
	{
		throw invalid_argument("Please use a weight larger than 0");
	}
	else
	{
		this->weight = weight;
	}
	return;
}
void Package::set_cost_per_ounce(double cpo)
{
	if (cpo <= 0)
	{
		throw invalid_argument("Please use cost per ounce larger than 0");
	}
	else
	{
		this->cost_per_ounce = cpo;
	}
	return;
}
double Package::get_weight()
{
	return weight;
}
double Package::get_cost_per_ounce()
{
	return cost_per_ounce;
}

string Package::get_type()
{
	return this->type;
}