#include<iostream>
#include<fstream>

using namespace std;
//Creating candidate list
string candidates_name[5] = { "Alice","Betty","Cindy","Danny","Ellen" };

int main()
{
	//Creating 2 arrays, one for voters' results and other one for candidates' results
	int voters[20];
	int candidates[5] = {0,0,0,0,0};
	//Using a char to judge if user want to input manually
	char judge;
	cout << "Do you want to input manuallu? [y/n]: ";
	cin >> judge;
	//manually input 
	if (judge == 'y'||judge=='Y')
	{
		cout << "You are in manually voting process now" << endl;
		cout << "Please votes 1 for Alice, 2 for Betty, 3 for Cindy, 4 for Danny, 5 for Ellen" << endl;
		for (int i = 0;i < 20;i++)
		{
			cout << "Please enter student " << i + 1 << "'s voting result:";
			int tmp;
			cin >> tmp;
			if (tmp >= 1 && tmp <= 5)
			{
				voters[i] = tmp;
			}
			else
			{
				cerr << "Invalid input ,please try enter a number between 1 and 5" << endl;
				i--;
			}
		}
	}
	//reading prepared voting result from file
	else if (judge == 'n'|| judge=='N')
	{
		cout << "You are in automatically voting process now" << endl;
		cout << "Voting results could be viewed in voters.txt under the same directory" << endl;
		ifstream file("voters.txt");
		int i = 0;
		while (!file.eof())
		{
			file >> voters[i++];
		}
		file.close();
	}
	//error message
	else
	{
		cerr << "Invalid input, system aborted" << endl;
		cerr << "Error code:-1" << endl;
		return -1;
	}
	//Calculating the votes for the candidates
	for (int i = 0;i < 20 ;i++)
	{
		candidates[voters[i] - 1]++;
	}
	//Setting a number to find the highest votes
	int highest_vote = 0;
	//Finding the index of the highest voted candidate
	int highest_candidate;
	//Finding if there are two highest voted candidates
	int highest_count = 0;
	for (int i = 0;i < 5;i++)
	{
		if (candidates[i] >= highest_vote)
		{
			highest_vote = candidates[i];
			highest_candidate = i;
		}
	}
	//Do another loop to find if there are two winners
	for (int i = 0;i < 5;i++)
	{
		cout << "Candidate " << i + 1 << ": " << candidates_name[i] << " has been voted for " << candidates[i] << endl;
		if (candidates[i] == highest_vote)
		{
			highest_count++;
		}
	}
	if (highest_count == 1)
	{
		cout << "The winner is candidate " << highest_candidate+1 << ": " << candidates_name[highest_candidate] << endl;
	}
	else
	{
		cout << "There is no winner this round" << endl;
	}
	return 0;
}
