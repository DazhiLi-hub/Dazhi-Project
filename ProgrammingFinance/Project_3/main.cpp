#include <iostream>
#include <stdexcept>
#include <limits>
#include "stringarray.h"
using namespace std;

void Continue(void)
{
    cout << "(Press Enter to Continue)";
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    try
    {
        cout << "Trying create a sring arary A(-1)" << endl;
        StringArray A(-1);
    }
    catch (invalid_argument &emsg)
    {
        cout << "Exception Caught: " << emsg.what() << endl;
    }
    Continue();
    StringArray StrAry1(5);  //call the default constructor
    StringArray StrAry2;     // 8 elements array by default

    // overloaded ostream operator 
    cout << "Size of intAry1 is " << StrAry1.getSize() << '\n' << StrAry1 << endl;
    cout << "Size of intAry2 is " << StrAry2.getSize() << '\n' << StrAry2 << endl;

    // overloaded iostream operators 
    cout << "Enter 5 word length string to StringArray1:(eg.happy)\n";
    cin >> StrAry1 ;
    cout << endl;
    cout << "intAry1 contains:\n" << StrAry1 << endl;
    cout << "intAry2 contains:\n" << StrAry2 << endl;
    Continue();

    cout << "Enter 8 word length string to StringArray2:(eg.birthday)\n";
    cin >> StrAry2;
    cout << endl;
    cout << "intAry1 contains:\n" << StrAry1 << endl;
    cout << "intAry2 contains:\n" << StrAry2 << endl;
    Continue();

    // overloaded inequality operator
    // compiler invokes member function intAry1.operator!=(intAry2)
    cout << "Testing if StringArray1 equals to StringArray2..." << endl;
    if (StrAry1 != StrAry2) {
        cout << "intAry1 and intAry2 are not equal\n" << endl;
    }
    Continue();
    cout << "Tring copy constructor..." << endl;
    StringArray intAry3(StrAry1);  //invokes copy contructor
    cout << "Size of intAry3 is " << intAry3.getSize() << '\n' << intAry3 << endl;
    Continue();
    // overloaded assignment operator
    // compiler invokes member function "operator=" with the call
    // intAry1.operator=(intAry2)
    cout << "Trying set StringArray1 = StringArray2" << endl;
    StrAry1 = StrAry2;
    cout << "intAry1 contains:\n" << StrAry1 << endl;
    cout << "intAry2 contains:\n" << StrAry2 << endl;
    Continue();
    // overloaded equality operator
    // compiler invokes member function intAry1.operator==(intAry2)
    cout << "Testing if StringArray 1 equals to StringArray2 now..." << endl;
    if (StrAry1 == StrAry2) {
        cout << "intAry1 and intAry2 are equal\n" << endl;
    }
    Continue();
    // overloaded [] operator for r-value
    // compiler invokes intAry1.operator[](2)
    cout << "Specifically visit the third character in StringArray1" << endl;
    cout << "StrAry1[2] = " << StrAry1[2] << endl;
    Continue();
    // overloaded [] operator for l-value
    cout << "Setting StringArray1[2]='c' ..." << endl;
    StrAry1[2] = 'c';
    cout << endl;
    cout << "StrAry1[2] = " << StrAry1[2] << endl << endl;
    Continue();

    cout << "Setting StringArray1[2]=StringArray3[0] ..." << endl;
    StrAry1[2] = intAry3[0];
    cout << endl;
    cout << "StrAry1[2] = " << StrAry1[2] << endl;
    Continue();

    try {
        cout << "\nAssign 'f' to StrAry1[19]\n";
        StrAry1[19] = 'f';
    }
    catch (out_of_range& emsg) {
        cout << "Exception Caught: " << emsg.what() << endl;
    }
    cout << endl;
    Continue();

    //a program can invoke only the const member functions for a const object
    cout << "Creating const instance StringArray4 equals to StringArray1" << endl;
    const StringArray StrAry4 = StrAry1;
    cout << "\n\n";
    cout << "const Array StrAry4, StrAry4[2] = " << StrAry4[2] << endl;

    cout << "\nNice work, bye bye ...\n";

    return 0;
}