/* No definition is given for pure virtual function
*/

#include <iostream>
#include "Employee.h"
using namespace std;

Employee::Employee(const string &first, const string &last, const string &ssn)
                    : firstName(first), lastName(last), SSN(ssn) {}
void Employee::setFirstName(const string &first) {
    firstName = first;
    return;
}
void Employee::setLastName(const string &last) {
    lastName = last;
    return;
}
void Employee::setSSN(const string &ssn) {
    SSN = ssn;
    return;
}

string Employee::getFirstName() const {
    return firstName;
}
string Employee::getLastName() const {
    return lastName;
}
string Employee::getSSN() const {
    return SSN;
}

void Employee::print() const {
    cout << getFirstName() << ' ' << getLastName() << "\nSSN: " << getSSN() << endl;
}
