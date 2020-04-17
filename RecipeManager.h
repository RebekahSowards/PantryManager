#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <set>
#include <map> 
#include <vector>
#include "Recipe.h"
#include "Food.h"
//A class for storing recipes and managing the pantry as it relates to the recipes
//Also makes a shopping list

using namespace std;

class RecipeManager{
private:
    Pantry * myPantry;
    map<string, Recipe> recipes;
    
public:
    RecipeManager(Pantry * setPantry);
    ~RecipeManager();
    void addRecipe(Recipe newRecipe);
    Recipe getRecipe(string recipeTitle);
    vector<string> getTitles();
    vector<string> checkRecipes();
    set<string> needIngredients();
    void shoppingList(set<string> shoppingRecipes);
    void makeRecipe(string title);
};