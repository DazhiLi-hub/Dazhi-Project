/* CommissionEmployee class member-function definitions
 */

#include <iostream>
#include <stdexcept>
#include "CommissionEmployee.h"
using namespace std;

CommissionEmployee::CommissionEmployee(
    const string& first,
    const string& last,
    const string& ssn,
    const double& sales,
    const double& rate
) : Employee(first, last, ssn) {
    setGrossSales(sales);
    setCommissionRate(rate);
}

void CommissionEmployee::setGrossSales(const double& sales) {
    if (sales >= 0.0) {
        this->grossSales = sales;
    }
    else {
        throw invalid_argument("CommissionEmployee::setGrossSales Gross sales must be >= 0.0");
    }
    return;
}
void CommissionEmployee::setCommissionRate(const double& rate) {
    if (rate >= 0.0 && rate < 1.0) {
        this->commissionRate = rate;
    }
    else {
        throw invalid_argument("CommissionEmployee::setGrossSales Commission rate must be >= 0.0 and < 1.0");
    }
    return;
}

double CommissionEmployee::getGrossSales() const {
    return this->grossSales;
}
double CommissionEmployee::getCommissionRate() const {
    return this->commissionRate;
}

// override pure virtual function earnings in Employee
double CommissionEmployee::earnings() const {
    return getCommissionRate() * getGrossSales();
}
void CommissionEmployee::print() const {
    cout << "commission employee: ";
    Employee::print();
    cout << "gross sales: " << getGrossSales()
        << "\ncommission rate: " << getCommissionRate() << endl;
    return;
}

string CommissionEmployee::whoami() const
{
    return "CommissionEmployee";
}