#include "package.h"
#include "TwoDayPackage.h"
#include "OvernightPackage.h"
#include<iostream>
#include<vector>
using namespace std;

void Display_Package_Info(Package* Pk_ptr)
{
	cout << endl << "Sender:" << endl;
	cout << Pk_ptr->get_Sender_info().name << endl;
	cout << Pk_ptr->get_Sender_info().address << endl;
	cout << Pk_ptr->get_Sender_info().city
		<< ", " << Pk_ptr->get_Sender_info().state
		<< " " << Pk_ptr->get_Sender_info().ZIP << endl;
	cout << endl << "Recipient:" << endl;
	cout << Pk_ptr->get_Recipient_info().name << endl;
	cout << Pk_ptr->get_Recipient_info().address << endl;
	cout << Pk_ptr->get_Recipient_info().city
		<< ", " << Pk_ptr->get_Recipient_info().state
		<< " " << Pk_ptr->get_Recipient_info().ZIP << endl;
	cout << endl << "Weight of package: " << Pk_ptr->get_weight() 
		<< " ounces" << endl;
	cout << "Type of delivery: " << Pk_ptr->get_type() << endl;
	cout << "Cost of Package: $" << Pk_ptr->calculateCost() << endl;
}

void Display_menu()
{
	cout << "0: Finish" << endl;
	cout << "1:Regular Delivery" << endl;
	cout << "2:Two Day Delivery" << endl;
	cout << "3:Overnight Delivery" << endl;
	cout << "Your choice:";
	return;
}

bool is_positive(double value)
{
	if (value <= 0)
	{
		cerr << "Please try to enter a positive value" << endl;
		return false;
	}
	return true;
}

int main()
{
	char choice;
	cout << "Would you like using the example data?(y/n);" << endl;
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		Package A("Woody Allen", "34 St. 5 Ave.", "New York", "NY", "10009", 
			"Jhon Smith", "2 Davidson Road", "Piscataway", "NJ", "08854");
		A.set_weight(10);
		TwodayPackage B("Aha Millen", "23 Boware road", "Asoblue", "MI", "60154",
			"Araon Wade", "1 Davidson Road", "Piscataway", "NJ", "08854");
		B.set_weight(5);
		OvernightPackage C("Sab Vettel", "6 Broaw road", "Samilate", "CA", "51410",
			"Louis Ham", "44 Race road", "Abolue", "AZ", "65211");
		C.set_weight(2);
		cout << "Package delivery services program" << endl << endl;

		cout << "Cost per ounce for a package:  $" << 
			A.get_cost_per_ounce()
			<< "/ounce" << endl;

		cout << "Additional cost for two-day delivery:  $" <<
			B.get_falt_fee_per_ounce()
			<< "/ounce" << endl;

		cout << "Additional cost for overnight delivery:  $" <<
			C.get_falt_fee_per_ounce()
			<< "/ounce" << endl;
		//Creating a vetor of Package pointers
		vector<Package*> packages;
		packages.push_back(&A);
		packages.push_back(&B);
		packages.push_back(&C);
		double sum=0;
		for (int i = 0;i < 3;i++)
		{
			cout << endl << "Package " << i + 1 << ":" << endl;
			Display_Package_Info(packages[i]);
			sum += packages[i]->calculateCost();
		}
		cout << endl << "Total cost of all the packages: $" << sum << endl;
	}
	else if (choice == 'n' || choice == 'N')
	{
		double cost_per_once, flat_rate_twoday, flat_rate_overnight;
		cout << "Please determine the cost first!" << endl;
		cout << "Cost per ounce for all packages: ";
		cin >> cost_per_once;
		if (!is_positive(cost_per_once))
			return -1;
		cout << "Flat fee per ounce for two day delivery package: ";
		cin >> flat_rate_twoday;
		if (!is_positive(flat_rate_twoday))
			return -1;
		cout << "Flat fee per ounce for overnight delivery package: ";
		cin >> flat_rate_overnight;
		if (!is_positive(flat_rate_overnight))
			return -1;
		cout << "Please choose each kind of package delievery at lease once!" << endl;
		cout << "Please add one kind of package, use 0 for finish" << endl;
		int package_type=1,count=0,type1_cnt=0,type2_cnt=0,type3_cnt=0;
		double weight;
		string sname, saddress, scity, sstate, szip,
			rname, raddress, rcity, rstate, rzip;
		vector<Package*> packages;
		while (package_type != 0)
		{
			Display_menu();
			cin >> package_type;
			if (package_type<0||package_type>3)
			{
				cerr << "Invalid input,please try agagin" << endl;
				continue;
			}
			if (package_type == 0)
			{
				if (type1_cnt == 0 || type2_cnt == 0 || type3_cnt == 0)
				{
					cerr << "You have at least one type of delivery method not added" << endl;
					cerr << "Please try again" << endl;
					package_type = 1;
				}
				continue;
			}
			cout << "Sender name: ";
			cin >> sname;
			cout << "Sender address: ";
			cin >> saddress;
			cout << "Sender city:";
			cin >> scity;
			cout << "Sender state:";
			cin >> sstate;
			cout << "Sender zip:";
			cin >> szip;
			cout << "Recipient name: ";
			cin >> rname;
			cout << "Recipient address: ";
			cin >> raddress;
			cout << "Recipient city:";
			cin >> rcity;
			cout << "Recipient state:";
			cin >> rstate;
			cout << "Recipient zip:";
			cin >> rzip;
			cout << "The weight of package:";
			cin >> weight;
			while (weight <= 0)
			{
				cerr << "Please enter a postive value for weight" << endl;
				cerr << "Please try again" << endl;
				cout << "The weight of package:";
				cin >> weight;
			}
			switch (package_type)
			{
			case 1:
			{
				packages.push_back(new Package(sname,saddress,scity,sstate,szip
				,rname,raddress,rcity,rstate,rzip));
				packages[count]->set_weight(weight);
				packages[count]->set_cost_per_ounce(cost_per_once);
				type1_cnt++;
				count++;
				break;
			}
			case 2:
			{
				packages.push_back(new TwodayPackage(sname, saddress, scity, sstate, szip
					, rname, raddress, rcity, rstate, rzip,flat_rate_twoday));
				packages[count]->set_weight(weight);
				packages[count]->set_cost_per_ounce(cost_per_once);
				type2_cnt++;
				count++;
				break;
			}
			case 3:
			{
				packages.push_back(new OvernightPackage(sname, saddress, scity, sstate, szip
					, rname, raddress, rcity, rstate, rzip, flat_rate_overnight));
				packages[count]->set_weight(weight);
				packages[count]->set_cost_per_ounce(cost_per_once);
				type3_cnt++;
				count++;
				break;
			}
			default:
			{
				break;
			}
			}
		}
		cout << "Package delivery services program" << endl << endl;

		cout << "Cost per ounce for a package:  $" <<
			cost_per_once
			<< "/ounce" << endl;

		cout << "Additional cost for two-day delivery:  $" <<
			flat_rate_twoday
			<< "/ounce" << endl;

		cout << "Additional cost for overnight delivery:  $" <<
			flat_rate_overnight
			<< "/ounce" << endl;
		double sum = 0;
		for (int i = 0;i < count;i++)
		{
			cout << endl << "Package " << i + 1 << ":" << endl;
			Display_Package_Info(packages[i]);
			sum += packages[i]->calculateCost();
			delete packages[i];
		}
		cout << endl << "Total cost of all the packages: $" << sum << endl;
	}
	else
	{
		cerr << "Invalid input, please try again" << endl;
		return -1;
	}
	return 0;
}