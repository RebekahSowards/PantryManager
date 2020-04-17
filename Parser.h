#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <vector>
#include "Food.h"
#include "Pantry.h"
//A class for processing a text file of foods in the pantry
//Loosely modeled after a class in a CS 236 project I did

using namespace std;
class Parser{
private:
	vector<string> myTokens;
	Pantry * myPantry;
	ifstream in;
	int tokenIt = 0;
	char c = 0x00;
public:
	Parser();
	Parser(string filename, Pantry * setPantry);
	~Parser();
	void scan();
	void readString();
	void readNumber();
	void parse();
	void addFood();
};

