/* SalariedEmployee class member function definitions
*/

#include <iostream>
#include <stdexcept>
#include "SalariedEmployee.h"
using namespace std;

SalariedEmployee::SalariedEmployee(const string &first, const string &last, 
        const string &ssn, const double &salary) : Employee(first, last, ssn) {
    setWeeklySalary(salary);
}

// set salary
void SalariedEmployee::setWeeklySalary(const double &salary) {
    if (salary >= 0.0) {
        weeklySalary = salary;
    } else {
        throw invalid_argument("SalariedEmployee::setWeeklySalary  Weekly salary must be >= 0.0");
    }
    return;
}
double SalariedEmployee::getWeeklySalary() const {
    return weeklySalary;
}

double SalariedEmployee::earnings() const {
    return getWeeklySalary();
}
// invoke the base class's print() using the scope resolution operator
// without the scope resoltion operator, the print call would cause infinite recursion
void SalariedEmployee::print() const {
    cout << "Salaried Employee: ";
    Employee::print();  // invoke the base class's print() using the scope resolution operator
    cout << "weekly salary: " << getWeeklySalary() << endl;
    return;
}
