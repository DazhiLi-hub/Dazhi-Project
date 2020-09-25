// Fig. 6.11: fig06_11.cpp
// Craps simulation.
#include <iostream>
#include <cstdlib> // contains prototypes for functions srand and rand
#include<ctime>
using namespace std;
unsigned int rollDice(); // rolls dice, calculates and displays sum
int main()
{
    // enumeration with constants that represent the game status
    enum Status { CONTINUE, WON, LOST }; // all caps in constants
    // randomize random number generator using current time
    srand(static_cast<unsigned int>(time(0)));
    unsigned int myPoint = 0;// point if no win or loss on first roll
    Status gameStatus = CONTINUE; // can contain CONTINUE, WON or LOST
    unsigned int sumOfDice = rollDice(); // first roll of the dice
    // determine game status and point (if needed) based on first roll
    switch (sumOfDice)
    {
    case 7://win with 7 on first roll
    case 11://win with 11 on first roll
        gameStatus = WON;
        break;
    case 2://lose with 2 on first roll
    case 3://lose with 3 on first roll
    case 12://lose with 12 on first roll
        gameStatus = LOST;
        break;
    default://did not win or lose, so remember point
        gameStatus = CONTINUE;//game is not over
        myPoint = sumOfDice;//remember the point
        cout << "Point is:" << myPoint << endl;
        break;//option at end of switch
    }//end Switch

    // while game is not complete
    while (CONTINUE == gameStatus) // not WON or LOST
    {
        sumOfDice = rollDice(); // roll dice again
        // determine game status
        if (sumOfDice == myPoint)//win by making point
            gameStatus = WON;
        else
            if (sumOfDice == 7)//lose by rolling 7 before point
                gameStatus = LOST;
    }//end while

    //Display won or lost message
    if (WON == gameStatus)
        cout << "Player wins" << endl;
    else
        cout << "Player loses" << endl;
}//end main

//roll dice, calculate sum and display results
unsigned int rollDice()
{
    //pick random die value
    unsigned int die1 = 1 + rand() % 6;//first die roll
    unsigned int die2 = 1 + rand() % 6;//second die roll

    unsigned int sum = die1 + die2;//compute sum of die values

    //display results of this roll
    cout << "Player rolled " << die1 << "+" << die2
        << "=" << sum << endl;
    return sum;//end function rollDice
}//end function rollDice