#include "randGen.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

int main(void)
{
	srand(time(NULL));
	DebugPrint dbug;
	dbug.setDebugLevel(2);
	dbug.print(2, "debug level 2 working properly" );
	RandGen rgObj(RAND_MAX,0);
	int rng=rgObj.getRange;
	return 0;
}