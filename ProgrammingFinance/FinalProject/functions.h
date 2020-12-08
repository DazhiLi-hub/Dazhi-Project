#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

int clear_ALL();

int Display_Portfolio_menu();

int Display_Bank_menu();

struct stock
{
	string name;
	float price_per_share;
};

vector<stock> Stock_files_import(string PATH);

int random_gen();

const stock Find_Stock_Symbol(vector<stock>& A, string searched_one);

void write_history(string event_type, string company_symbol, int num_shares,
	float price_per_shares);
#endif
