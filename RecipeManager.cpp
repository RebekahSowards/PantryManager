#include "RecipeManager.h"

RecipeManager::RecipeManager(Pantry * setPantry) {
    myPantry = setPantry;
}

RecipeManager::~RecipeManager() {
    //Writes the stored recipes to "recipe.txt"
    //"recipe.txt" is formatted so that it can be read by RecipeParser
    ofstream writeRecipes;
    writeRecipes.open("recipe.txt");
    for (map<string, Recipe>::iterator it = recipes.begin(); it != recipes.end(); it++) {
        writeRecipes << it->second.printString();
    }
    writeRecipes.close();
}

void RecipeManager::addRecipe(Recipe newRecipe) {
    recipes[newRecipe.getTitle()] = newRecipe;
}

Recipe RecipeManager::getRecipe(string recipeTitle) {
    return recipes[recipeTitle];
}

vector<string> RecipeManager::getTitles() {
    //This is called in main to plan a shopping trip
    vector<string> recipeTitles;
    for (map<string, Recipe>::iterator it = recipes.begin(); it != recipes.end(); it++) {
        recipeTitles.push_back(it->first);
    }
    return recipeTitles;
}

vector<string> RecipeManager::checkRecipes() {
    //This is called in main in "make a recipe now"
    vector<string> ingredientsAvailable;
    for (map<string, Recipe>::iterator it = recipes.begin(); it != recipes.end(); it++) {
        if (it->second.ingredientCheck(*myPantry).size() == 0) {
            ingredientsAvailable.push_back(it->first);
        }
    }
    return ingredientsAvailable;
}

set<string> RecipeManager::needIngredients() {
    //This was used in a previous version of main, but I didn't delete it
    set<string> ingredientsNeeded;
    for (map<string, Recipe>::iterator it = recipes.begin(); it != recipes.end(); it++) {
        vector<string> recipeIngredients;
        recipeIngredients = it->second.ingredientCheck(*myPantry);
        int ingredientsNum = recipeIngredients.size();
        for (int i = 0; i < ingredientsNum; i++) {
            ingredientsNeeded.insert(recipeIngredients[i]);
        }
    }
    return ingredientsNeeded;
}

void RecipeManager::shoppingList(set<string> shoppingRecipes) {
    //Evaluates the recipes chosen by the user, determines what ingredients are needed, and prints them to "shopping.txt"
    map<string, Food> shoppingList;
    ofstream shopping;
    shopping.open("shopping.txt");
    shopping << "This is your shopping list.\nBuy at least the quantity shown to make the recipes you selected:" << endl;
    for (string myTitle : shoppingRecipes) {
        shopping << myTitle << endl;
        map<string, Food> tempList;
        tempList = recipes[myTitle].whatToBuy(*myPantry);
        for (map<string, Food>::iterator iter = tempList.begin(); iter != tempList.end(); iter++) {
            map<string, Food>::iterator point = shoppingList.find(iter->first);
            if (point == shoppingList.end()) {
                shoppingList[iter->first] = iter->second;
            }
            else {
                point->second.addItems(iter->second.getQuantity());
            }
        }
    }

    for (map<string, Food>::iterator list = shoppingList.begin(); list != shoppingList.end(); list++) {
        int amount = myPantry->checkFoodQuantity(list->second.getQuantity(), list->second.getName());
        if (amount) {
            shopping << list->second.getName() << " " << to_string(amount) << " ";
            string unit = list->second.getUnit();
            if (unit == list->second.getName()) {
                shopping << "-";
            }
            else {
                shopping << unit;
            }
            shopping << endl;
        }
    }
    shopping.close();
}

void RecipeManager::makeRecipe(string title) {
    //Calls a function of the same name in the Recipe class which modifies food amounts in the Pantry class
    recipes[title].makeRecipe(myPantry);
}