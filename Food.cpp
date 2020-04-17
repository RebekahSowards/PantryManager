#include "Food.h"

Food::Food() {

}

Food::Food(string setUnit, string setName, double setQuant, int setCal) {
	//The parser includes spaces for multi-word food names, so we remove them from the end when we create the object.
	while (setUnit.back() == ' ') {
		setUnit.pop_back();
	}
	unit = setUnit;
	while (setName.back() == ' ') {
		setName.pop_back();
	}
	name = setName;
	quantity = setQuant;
	caloriePer = setCal;
}

Food::~Food() {

}

string Food::printString() {
	//This function is for printing to recipe.txt or pantry.txt. It does not include formatting for shopping.txt.
	string returnString = name;
	returnString += " ";
	returnString += to_string(quantity);
	returnString += " ";
	returnString += unit;
	if (caloriePer != -1) {
		returnString += " ";
		returnString += to_string(caloriePer);
	}
	return returnString;
}

//Various getters and setters
void Food::setUnit(string setUnit) {
	unit = setUnit;
}

string Food::getUnit() {
	if (unit == "-") {
		return name;
	}
	return unit;
}

void Food::setName(string newName) {
	name = newName;
}

string Food::getName() {
	return name;
}

void Food::setQuantity(double newQuant) {
	quantity = newQuant;
}

double Food::getQuantity() {
	return quantity;
}

void Food::setCal(int newCal) {
	caloriePer = newCal;
}

int Food::getCal() {
	return caloriePer;
}

//For consumption or purchases, also used to total the food needed on the shopping list.
void Food::addItems(double howMany) {
	quantity += howMany;
}

void Food::useItems(double howMany) {
	quantity -= howMany;
}