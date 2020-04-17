#include "Recipe.h"

Recipe::Recipe() {
    
}

Recipe::Recipe(string setTitle, int setTime) {
    while (setTitle.back() == ' ') {
		setTitle.pop_back();
	}
    title = setTitle;
    requiredTime = setTime;
}

Recipe::~Recipe() {
    
}

string Recipe::getTitle() {
    return title;    
}

string Recipe::printString() {
    //This function is for printing to recipe.txt
    string returnString = title;
    returnString += " ";
    returnString += to_string(requiredTime);
    returnString += "\n";
    for (map<string, Food>::iterator it = ingredients.begin(); it != ingredients.end(); it++) {
        returnString += it->second.printString();
        returnString += "\n";
    }
    returnString += "\n";
    return returnString;
}

void Recipe::addFood(Food newIngredient) {
    ingredients[newIngredient.getName()] = newIngredient;
}

vector<string> Recipe::ingredientCheck(Pantry myPantry) {
    //Called by RecipeManager::checkRecipes
    vector<string> nonIngredients;
    for (map<string,Food>::iterator it = ingredients.begin(); it != ingredients.end(); it++) {
        if (!myPantry.checkFood(it->second.getQuantity(), it->second.getName())) {
            nonIngredients.push_back(it->second.getName());
        }
    }
    return nonIngredients;
}

map<string, Food> Recipe::whatToBuy(Pantry myPantry) {
    //This does almost the same thing as ingredientCheck, but is used in RecipeManager::shoppingList
    map<string, Food> thingsToBuy;
    for (map<string,Food>::iterator it = ingredients.begin(); it != ingredients.end(); it++) {
        thingsToBuy[it->second.getName()] = it->second;
    }
    return thingsToBuy;
}

void Recipe::makeRecipe(Pantry * myPantry) {
    //Removes items used in the recipe from the pantry
    //Can call through RecipeManager::makeRecipe
    for (map<string, Food>::iterator it = ingredients.begin(); it != ingredients.end(); it++) {
        myPantry->myFoods[it->first].useItems(it->second.getQuantity());
    }
}