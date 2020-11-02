/* BasePlusCommissionEmployee member-function definitions
 */

#include <iostream>
#include <stdexcept>
#include "BasePlusCommissionEmployee.h"
using namespace std;


// constructor, destructor, copy constructor, assignment operator
// overloaded operators of the base class, friend functions of the base class
// are not inherited over to derived class
BasePlusCommissionEmployee::BasePlusCommissionEmployee(
    const string &first,
    const string &last,
    const string &ssn,
    const double &sales,
    const double &rate,
    const double &salary
): CommissionEmployee(first, last, ssn, sales, rate) {   // explicitly call base class constructor,
    setBaseSalary(salary);
}

void BasePlusCommissionEmployee::setBaseSalary(const double &salary) {
    if (salary >= 0.0) {
        this->baseSalary = salary;
    } else {
        throw invalid_argument("BasePlusCommissionEmployee::setBaseSalary base salary must be >= 0.0");
    }
    return;
}

double BasePlusCommissionEmployee::getBaseSalary() const {
    return this->baseSalary;
}

// call the base-class member functions, 
// try not to access the class data directly,
// avoid duplicating the code and reduce code-maintenance problem
double BasePlusCommissionEmployee::earnings() const {
    return getBaseSalary() + CommissionEmployee::earnings();
}

// derived class cannot access the base class's private data
void BasePlusCommissionEmployee::print() const {
    cout << "base-salaried ";
    CommissionEmployee::print();
    cout << "base salary: " << getBaseSalary() << endl;
    return;
}
