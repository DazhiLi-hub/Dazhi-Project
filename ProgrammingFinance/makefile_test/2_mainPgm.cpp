/* Purposes:
   demonstrating downcasting and Runtime Type Information (RTTI)
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <typeinfo>
#include "Employee.h"
#include "SalariedEmployee.h"
#include "CommissionEmployee.h"
#include "BasePlusCommissionEmployee.h"
using namespace std;

int main() {
    // set floating-point output format
    cout << fixed << setprecision(2);
    vector < Employee * > employees(3);

    employees[0] = new SalariedEmployee("John", "Smith", "123-45-6789", 888);
    employees[1] = new CommissionEmployee("Mary", "Joe", "412-77-8888", 10000, .06);
    employees[2] = new BasePlusCommissionEmployee("Tom", "Campian", "412-77-4444", 5000, .04, 300);

    for (Employee *employeePtr : employees) {
        employeePtr->print();

        // attempt to downcast pointer
        // dynamic_cast operator, dynamically downcast at execution time
        // if successful, the object address is assigned to derivedPtr; otherwise, nullptr is assigned
        BasePlusCommissionEmployee *derivedPtr = dynamic_cast<BasePlusCommissionEmployee *>(employeePtr);

        // determine whether element points to a BasePlusCommissionEmployee
        if (derivedPtr != nullptr) {
            double oldBaseSalary = derivedPtr->getBaseSalary();
            cout << "old base salary: $" << oldBaseSalary << endl;
            derivedPtr->setBaseSalary(1.10 * oldBaseSalary);
            cout << "new base salary with 10% increase: $" << derivedPtr->getBaseSalary() << endl;
        } else {
            cout << "(Downcast not success, employeePtr pointing to BasePlusCommissionEmployee object)" << endl;
        }
        cout << "earned $" << employeePtr->earnings() << "\n\n";  // dynamic binding taking place
    }

    // typeid operator returns a reference to an object of class type_info
    // type_info member function name() returns a pointer-based string 
    // containing the typeid argument's type name
    for (const Employee *employeePtr : employees) {
        cout << "deleting object of " << typeid(*employeePtr).name() << endl;
        delete employeePtr;
    }

    return 0;
}
