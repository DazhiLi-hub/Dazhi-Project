/* Abstract base class Employee declares the "interface" to the hierarchy
     - declare the set of member functions that a program can invoke on all employee objects
     - regardless of the way earnings are calculated, employee information is printed,
       each employee has
       first name
       last name
       social security number
       and all the get/set functions for the 3 data members
     - declare earnings() as pure virtual function
     - declare print() as virtual function, print information common to all classes,
       it is called and overridden in the derived class

     - a program can use abstract base class Employee pointers to invoke function earnings()
       polymorphically for any type of employee
*/

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
    std::string firstName;
    std::string lastName;
    std::string SSN;
public:
    Employee(const std::string&, const std::string&, const std::string&);
    virtual ~Employee() {};

    // set functions
    void setFirstName(const std::string&);
    void setLastName(const std::string&);
    void setSSN(const std::string&);
    // get functions
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getSSN() const;

    virtual double earnings() const = 0;  // pure virtual function
    virtual void print() const;
    virtual std::string whoami() const;
};

#endif
