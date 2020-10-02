#include "randGen.h"
#include <math.h>

using namespace std;

int DebugPrint::debugLevel = 1;

void DebugPrint::setDebugLevel(int dl)
{
	debugLevel = dl;
}

int DebugPrint::getDebugLevel()
{
	return debugLevel;
}

void DebugPrint::print(int dL, std::string statement)
{
	if (dL < debugLevel) {
		return;
	}
	if (dL == 1) {
		std::cout << GREEN << "DEBUG: " << statement << RESET << std::endl;
	}
	else if (dL == 2) {
		std::cout << BOLDCYAN << "INFO: " << statement << RESET << std::endl;
	}
	else if (dL == 3) {
		std::cout << YELLOW << "WARNING: " << statement << RESET << std::endl;
	}
	else if (dL == 4) {
		std::cout << MAGENTA << "ERROR: " << statement << RESET << std::endl;
	}
	else if (dL == 5) {
		std::cout << BOLDRED << "FATAL: " << statement << RESET << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Sepecified debug level: " << dL << " is not defined in debugPrint function\n";
		exit(EXIT_FAILURE);
	}
}

RandGen::RandGen(int rng , int ctr )
{
	range = rng;
	cntr = ctr;
}

int RandGen::getRange()
{
	return range;
}

void RandGen::setRange(int rng)
{
	range = rng;
	return;
}

int RandGen::readCntr()
{
	return cntr;
}

int* RandGen::genPoint()
{
	int* pointPtr = point;
	point[0] = rand() % range;
	point[1] = rand() % range;
	cntr++;
	return pointPtr;
}

double RandGen::distance()
{
	double distance = sqrt(pow(point[0], 2)+pow(point[1],2));
	return distance;
}

FindPi::FindPi()
{

}

void FindPi::setEstmResults(double estmResults)
{
	estimatedResults = estmResults;
}

double FindPi::getEstmResults()
{
	return estimatedResults;
}

double FindPi::runEstimation(int itr, int randLimit)
{
	double count=0;
	double distance;
	RandGen rndPoint(randLimit,0);
	for (int i = 0;i < itr;i++)
	{
		rndPoint.genPoint();
		distance=rndPoint.distance();
		if (distance < rndPoint.getRange())
		{
			count++;
		}
	}
	double pi = 4 * (count / double(rndPoint.readCntr()));
	return pi;
}
