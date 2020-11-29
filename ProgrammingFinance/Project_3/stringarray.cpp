/*
*/

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "stringarray.h"
using namespace std;

StringArray::StringArray(int arraySize) :
    size(arraySize > 0 ? arraySize : throw invalid_argument("Array size must be greater than 0")),
    ptr(new char[size]) {
    for (size_t i = 0; i < size; ++i) {
        ptr[i] = ' ';
    }
}

StringArray::StringArray(const StringArray& array2Copy) : size(array2Copy.size), ptr(new char[size]) {
    for (size_t i = 0; i < size; ++i) {
        ptr[i] = array2Copy.ptr[i];
    }
    cout << "(Array::Array(const Array &) Copy Constructor invoked) " << endl;
}

StringArray::~StringArray() {
    delete[] ptr;
}

size_t StringArray::getSize() const {
    return size;
}

// overloaded assignment operator
// const return avoids: (a1 = a2) = a3; // enforce the return is r-value
// ensure executing sequence: a2 = a3; a1 = a2;
const StringArray& StringArray::operator=(const StringArray& right) {
    // make sure l-value has the same size of r-value
    if (&right != this) {   // avoid self-assignment
        if (size != right.size) {
            delete[] ptr;
            size = right.size;
            ptr = new char[size];
        }
        for (size_t i = 0; i < size; ++i) {
            ptr[i] = right.ptr[i];
        }
    }
    cout << "(&Array::operator=() invoked) " << endl;

    return *this;
}

bool StringArray::operator==(const StringArray& right) const {
    if (size != right.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (ptr[i] != right.ptr[i]) {
            return false;
        }
    }
    return true;
}

// subscrip operator, checks Array boundary
// returns a reference of int to enable l-value assignment
char& StringArray::operator[](int subscript) {
    if (subscript < 0 || subscript >= size) {
        throw out_of_range("String l-value: Subscript out of range") ;
    }
    else {
        cout << "(&StringArray::operator[] l-value called) " << endl;
    }
    return ptr[subscript];
}

char StringArray::operator[](int subscript) const {
    if (subscript < 0 || subscript >= size) {
        throw out_of_range("Array r-value: Subscript out of range");
    }
    else {
        cout << "(Array::operator[] r-value called) "<<endl;
    }
    return ptr[subscript];
}

istream& operator>>(istream& input, StringArray& a) {
    for (size_t i = 0; i < a.size; ++i) {
        input >> a.ptr[i];
    }
    return input;  // enable cin >> array1 >> b >> array2
}

ostream& operator<<(ostream& output, const StringArray& a) {
    for (size_t i = 0; i < a.size; ++i) {
        output <<  a.ptr[i];
    }
    output << endl;
    return output;
}
