/* SalariedEmployee class derived from Employee
   Placing the virtual keyword before earnings(), print() is redundant but for clarity to have it declared
   they are defined virtual in base class Employee, so they remain virtual 
   throughout the class hierarchy.
   Explicitly declaring such functions virtual at every level of the hierarchy promptes program clarity
*/

#ifndef SALARIED_H
#define SALARIED_H

#include <string>
#include "Employee.h"

class SalariedEmployee : public Employee {
    double weeklySalary;
public:
    SalariedEmployee(const std::string &, const std::string &, const std::string &, const double & =0.0);
    virtual ~SalariedEmployee() {}

    void setWeeklySalary(const double &);
    double getWeeklySalary() const;

    virtual double earnings() const override;
    virtual void print() const override;
};

#endif