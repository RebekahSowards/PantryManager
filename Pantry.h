#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Food.h"
//A class for storing food objects
//Could recipe inherit from pantry if we come back to this project?


using namespace std;
class Pantry{
private:

public:
	Pantry();
	~Pantry();
	void addFood(Food newFood);
	bool checkFood(double quantity, string food);
	double checkFoodQuantity(double quantity, string food);
	vector<string> getFoods();
	
	//not ideal, but I didn't have time to change it back to private
	map<string, Food> myFoods;
};