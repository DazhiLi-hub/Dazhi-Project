/* Processing Employee derived-class objects individually
   and polymorphically using dynamic binding.
   Even though Employee is an abstract class, the "is a" relationship still valid
   the compiler cannot know which concrete class's functions to call through baseClassPtr
   all virtual function calls to print() and earnings() are resolved at runtime with dynamic binding
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "SalariedEmployee.h"
#include "CommissionEmployee.h"
#include "BasePlusCommissionEmployee.h"
using namespace std;

void virtualViaPointer(const Employee * const);
void virtualViaReference(const Employee &);

int main() {
    // set floating-point output format
    cout << fixed << setprecision(2);

    SalariedEmployee salariedEmployee("John", "Smith", "123-45-6789", 888);
    CommissionEmployee commissionEmployee("Mary", "Joe", "412-77-8888", 10000, .06);
    BasePlusCommissionEmployee basePlusCommissionEmployee("Tom", "Campian", "412-77-4444", 5000, .04, 300);

    // static binding is using name handles, happens at compile time
    cout << "Employees processed individually using static binding:\n\n";
    salariedEmployee.print();
    cout << "earned $" << salariedEmployee.earnings() << "\n\n";
    commissionEmployee.print();
    cout << "earned $" << commissionEmployee.earnings() << "\n\n";
    basePlusCommissionEmployee.print();
    cout << "earned $" << basePlusCommissionEmployee.earnings() << "\n\n";

    cout << "Employees processed polymorphically via dynamic binding:\n\n";
    vector< Employee * > employees(3);  //create vector of three base-class pointers
    employees[0] = &salariedEmployee;
    employees[1] = &commissionEmployee;
    employees[2] = &basePlusCommissionEmployee;

    cout << "Virtual function calls made off base-class pointers:\n\n";
    // range-based for loop, c++11 feature, -std=c++11 commandline opetion to compile
    for (const Employee *employeePtr : employees) {
        virtualViaPointer(employeePtr);
    }
    cout << "Virtual function calls made off base-class references:\n\n";
    for (const Employee *employeePtr : employees) {
        virtualViaReference(*employeePtr);
    }

    return 0;
}

// virtualViaPointer receives in parameter baseClassPtr, the address stored in an 'employees' element
// uses baseClassPtr to invoke virtual functions print() and earnings() according to the object type
// the function only knowns about base-class type Employee
void virtualViaPointer( const Employee * const baseClassPtr) {
    baseClassPtr->print();
    cout << "earned $" << baseClassPtr->earnings() << "\n\n";
}

// virtualViaReference receives in its parameter baseCassRef (of type const Employee &)
// a reference to the object obtained by dereferencing the pointer stored in each 'employees' element
// polymorphic processing occurs with base-class references as well
void virtualViaReference( const Employee &baseClassRef) {
    baseClassRef.print();
    cout << "earned $" << baseClassRef.earnings() << "\n\n";
}
