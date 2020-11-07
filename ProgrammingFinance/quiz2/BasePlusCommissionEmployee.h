/* BasePluseCommissionEmployee class derived from CommissionEmployee
*/

#ifndef BASEPLUS_H
#define BASEPLUS_H

#include <string>
#include "CommissionEmployee.h"

class BasePlusCommissionEmployee : public CommissionEmployee {
    double baseSalary;
public:

    BasePlusCommissionEmployee(const std::string&, const std::string&, const std::string&,
        const double& = 0.0, const double& = 0.0, const double& = 0.0);
    virtual ~BasePlusCommissionEmployee() {}

    //set function
    void setBaseSalary(const double&);
    //get function
    double getBaseSalary() const;

    // keyword virtual signals intent to override
    virtual double earnings() const override;  // calculate earnings and modify nothing but return the calculation results
    virtual void print() const override;  // print CommissionEmployee objec, also update nothing but print
    virtual std::string whoami() const override;
};

#endif
