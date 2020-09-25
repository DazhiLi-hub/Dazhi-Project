#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sstream>

using namespace std;

enum Status { CONTINUE, WON, LOST };
unsigned int rollDice();
int GetInt();
Status PlayGame();

int main(int argc, char*argv[])
{
	unsigned int Num_plays;
	unsigned int Num_wins = 0;
	unsigned int Num_Loss = 0;
    srand(static_cast<unsigned int>(time(0)));
	Status gameStatus = CONTINUE; // can contain CONTINUE, WON or LOST
    if (argc == 2)
    {
        stringstream ss(argv[1]);
        ss >> Num_plays;
        if (Num_plays <= 0)
        {
            cerr << "Please input a positive integer" << endl;
            return -1;
        }
    }
    else
    {
        Num_plays = GetInt();
    }
    if (Num_plays == -1)
    {
        return -1;
    }
    for (int i = 0; i < Num_plays;i++)
    {
        gameStatus=PlayGame();
        if (gameStatus == WON)
            Num_wins++;
        else if (gameStatus == LOST)
            Num_Loss++;
        else
            cerr << "Program error" << endl;
    }
    cout << "The total number of wins is " << Num_wins << endl;
    cout << "The total number of lost is " << Num_Loss << endl;
    return 0;
}

unsigned int rollDice()
{
    unsigned int die1 = 1 + rand() % 6;
    unsigned int die2 = 1 + rand() % 6;
    unsigned int sum = die1 + die2;
    cout << "Player rolled " << die1 << "+" << die2
        << "=" << sum << endl;
    return sum;
}

int GetInt()
{
    int num_plays;
    cout << "Please specify the number of plays you want: ";
    while (cin >> num_plays)
    {
        if (num_plays > 0)
            break;
        else
            cerr << "Please input a positive integer" << endl;
        return -1;
    }
    return num_plays;
}

Status PlayGame()
{
    unsigned int myPoint = 0;// point if no win or loss on first roll
    Status Inside_Status = CONTINUE;
    unsigned int sumOfDice = rollDice();
    switch (sumOfDice)
    {
    //WINS
    case 7:
    case 11:
        Inside_Status = WON;
        break;
    //LOSES
    case 2:
    case 3:
    case 12:
        Inside_Status = LOST;
        break;
    default://did not win or lose, so remember point
        Inside_Status = CONTINUE;//game is not over
        myPoint = sumOfDice;//remember the point
        cout << "Point is:" << myPoint << endl;
        break;//option at end of switch
    }//end Switch
    while (CONTINUE == Inside_Status) 
    {
        sumOfDice = rollDice(); 
        // determine game status
        if (sumOfDice == myPoint)
            Inside_Status = WON;
        else
            if (sumOfDice == 7)
                Inside_Status = LOST;
    }

    if (WON == Inside_Status)
    {
        cout << "Player wins" << endl;
        cout << "\n";
        return WON;
    }
    else
    {
        cout << "Player loses" << endl;
        cout << "\n";
        return LOST;
    }
}