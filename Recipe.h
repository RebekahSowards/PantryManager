#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <set>
#include <map>
#include <vector>
#include "Pantry.h"
#include "Food.h"
//A class for information contained in a recipe
//Does some other things that RecipeManager needs it to do



using namespace std;

class Recipe{
private:
    map<string, Food> ingredients;
    string title;
    int requiredTime;
    
public:
    Recipe();
    Recipe(string setTitle, int setTime);
    ~Recipe();
    string getTitle();
    string printString();
    void addFood(Food newIngredient);
    vector<string> ingredientCheck(Pantry myPantry);
    map<string, Food> whatToBuy(Pantry myPantry);
    void makeRecipe(Pantry * myPantry);
};