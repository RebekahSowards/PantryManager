#include "Pantry.h"

Pantry::Pantry() {
    
}

Pantry::~Pantry() {
    //When the class is deleted, it writes its updated contents to the file "pantry.txt"
    //"pantry.txt" is formatted so that it can be used in the constructor for the parser class
    ofstream writePantry;
    writePantry.open("pantry.txt");
    for (map<string, Food>::iterator it = myFoods.begin(); it != myFoods.end(); it++) {
        writePantry << it->second.printString() << endl;
    }
    writePantry.close();
}

void Pantry::addFood(Food newFood) {
    string name = newFood.getName();
    myFoods[name] = newFood;
}

bool Pantry::checkFood(double quantity, string food) {
    //This function is used by RecipeManager to check to see if a recipe is viable
    if (myFoods.count(food)) {
        if (myFoods[food].getQuantity() >= quantity) {
            return true;
        }
    }
    return false;
}

double Pantry::checkFoodQuantity(double quantity, string food) {
    //This function is used by Recipe Manager to get shopping list totals
    if (myFoods.count(food)) {
        if (quantity - myFoods[food].getQuantity() > 0) {
            return quantity - myFoods[food].getQuantity();
        }
        else return 0;
    }
    return quantity;
}

vector<string> Pantry::getFoods() {
    //This function returns a list of names of all available foods
    vector<string> food;
    for (map<string,Food>::iterator it = myFoods.begin(); it != myFoods.end(); it++) {
        food.push_back(it->first);
    }
    return food;
}