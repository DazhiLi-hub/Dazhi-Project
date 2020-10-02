#include "randGen.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

/****
 rand() returns a pseudo-random number in the range of 0 to RAND_MAX
 after compile, the sequence in generating the random number is fixed,
 so for every run, rand() generates the same sequence of random number
 srand() comes to rescue for this problem
 srand() sets the starting point for rand(), the starting point needs only be seeded once,
 before calls to rand(), and the start of the program.  It should not be repeatedly seeded,
 or reseeded every time you wish to generate a new batch of pseudo-random numbers.  That means
 srand(time(null)) needs to be called once in a program life time.  time() returns a different
 value everytime, and hence the pseudo-random number vary for every program call.
 srand() sets the seed which is used by rand to generate random number.
*/

int main(int argc, char* argv[]) {
    // use current time as seed for random generator
    srand(time(NULL));
    RandGen rgObj;
    DebugPrint dbug;
    FindPi estmPiObj;

    dbug.setDebugLevel(2);
    dbug.print(3, "Debug level test 3" );
    dbug.print(4, "Debug level test 4");
    // double myEstm = estmPiObj.runEstimation(1000, 250);
    double myEstm = estmPiObj.runEstimation(1000, RAND_MAX);
    dbug.print(2, "The estimation of Pi is:" + std::to_string(myEstm));
    myEstm = estmPiObj.runEstimation(1000, 3000);
    dbug.print(2, "The estimation of Pi is:" + std::to_string(myEstm));
    dbug.print(2, "The default range of RandGen object is:" + std::to_string(rgObj.getRange()));
    dbug.print(2, "The default cntr of RandGen object is:" + std::to_string(rgObj.readCntr()));
    rgObj.setRange(1000);
    dbug.print(2, "The new range of RandGen object is:" + std::to_string(rgObj.getRange()));
    int* pointPtr=rgObj.genPoint();
    cout << "Creating a new point" << endl;
    cout << "The x value of new point is:" << pointPtr[0] << endl;
    cout << "The y value of new point is:" << pointPtr[1] << endl;
    dbug.print(2, "The distance between new point and origin is:" + std::to_string(rgObj.distance()));
    /*
    double dist = rgObj.distance();
    dbug.print(2, "dist=" + std::to_string(dist));
    dbug.print(1, "RandGen.cntr=" + std::to_string(rgObj.readCntr()));
    dist = rgObj.distance();
    dbug.print(2, "dist=" + std::to_string(dist));
    dbug.print(1, "RandGen.cntr=" + std::to_string(rgObj.readCntr()));
    cout << rgObj.getRange() << endl;

    if (argc < 3) {
        cout << "Too few argument for program to work!\n";
        cout << "Usage: " << argv[0] << " range_of_random_number number_of_random_number_needed\n" << endl;
    } else if (argc == 3) {
        cout << "random number generated in the range of 0 to RAND_MAX=" << RAND_MAX << ":\n";
        randGen(argv[1], argv[2]);
    } else if (argc == 4) {
        stringstream ss(argv[3]);
        ss >> debugLevel;
        randGen(argv[1], argv[2]);
    } else {
        cout << "Too many arguments for program to work!\n";
        cout << "Usage: " << argv[0] << " range_of_random_number number_of_random_number_needed\n" << endl;
    }
    */

    return 0;
}