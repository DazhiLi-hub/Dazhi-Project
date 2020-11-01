#ifndef STRINGARRAY_H
#define STRINGARRAY_H

#include <iostream>

class StringArray {
    size_t size;
    char* ptr;
public:
    explicit StringArray(int = 8);  // default constructor

    // copy constructor
    // the argument to a copy constructor should be a const reference 
    // to allow a const object to be copied
    StringArray(const StringArray&);  // why default copy constructor won't work?
    ~StringArray();  // destructor
    size_t getSize() const;

    // enables cascaded Array assignments, x = y = z;
    // does y = z first, y.operator=(z) returns const Array & for 
    // x = y to continue, that invokes x.operator=(y)
    // the return type const Array & prevents (x = y) = z;
    // z cannot be assigned to the const Array & that is returned by (x = y)
    const StringArray& operator=(const StringArray&);  //assignment operator

    bool operator==(const StringArray&) const;  // equality operator

    // reuse operator==
    // allows teh compiler to inline the definition of operator!=
    bool operator!=(const StringArray& right) const {
        return !(*this == right);
    }
    char& operator[](int);

    //a program can invoke only the const member functions for a const object
    char operator[](int) const;
    friend std::ostream& operator<<(std::ostream&, const StringArray&);
    friend std::istream& operator>>(std::istream&, StringArray&);
};


#endif
