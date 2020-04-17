#pragma once
#include <iostream>
#include <string>
//A class for information about a food: what it's called and how much we have.
//In a recipe, quantity becomes how much we need.
//I haven't done much yet with calories, but the structure to add calorie counting functions is mostly in place.

using namespace std; 
class Food{
private:
	string unit;
	string name;
	double quantity;
	int caloriePer;

public:
	Food();
	Food(string setUnit, string setName, double setQuant, int setCal);
	~Food();
	string printString();
	void setUnit(string setUnit);
	string getUnit();
	void setName(string newName);
	string getName();
	void setQuantity(double newQuant);
	double getQuantity();
	void setCal(int newCal);
	int getCal();
	void addItems(double howMany);
	void useItems(double howMany);
};