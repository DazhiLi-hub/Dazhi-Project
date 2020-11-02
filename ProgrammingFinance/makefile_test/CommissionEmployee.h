/* CommissionEmployee class deried from Employee
*/


#ifndef COMMISSION_H
#define COMMISSION_H

#include <string>
#include "Employee.h"

class CommissionEmployee : public Employee {
    double grossSales;
    double commissionRate;
public:
    CommissionEmployee(const std::string &, const std::string &, const std::string &, 
                       const double & =0.0, const double & =0.0);
    virtual ~CommissionEmployee() {}

    //set function
    void setGrossSales(const double &);
    void setCommissionRate(const double &);
    //get function
    double getGrossSales() const;
    double getCommissionRate() const;

    // keyword virtual signals intent to override
    virtual double earnings() const override;
    virtual void print() const override;
};


#endif