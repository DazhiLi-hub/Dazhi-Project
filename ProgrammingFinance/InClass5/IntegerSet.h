#ifndef INTEGER_SET_H
#define INTEGER_SET_H

class IntegerSet
{
public:
	IntegerSet(); // constructor
	void inputSet(); // read values from user
	IntegerSet UnionOfSets(IntegerSet B);
	IntegerSet IntersectionOfSets(IntegerSet B);
	void printSet() const;

private:
	int set[101]; // range of 0 - 100

	// determines a valid entry to the set
	int validEntry(int x) const
	{
		return (x >= 0 && x <= 100);
	} // end function validEntry
};

#endif
