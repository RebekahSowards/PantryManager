#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <cctype> 
#include <vector>
#include "Food.h"
#include "Recipe.h"
#include "RecipeManager.h"
//A class for processing a text file of available recipes
//Loosely modeled after a class in a CS 236 project I did


using namespace std;
class RecipeParser{
private:
    RecipeManager * myRecipeManager;
    vector<string> myTokens;
    ifstream in;
    Recipe newRecipe;
    int tokenIt = 0;
    char c = 0x00;
    bool eof;
public:
    RecipeParser();
    RecipeParser(string filename, RecipeManager * setRecipeManager);
    ~RecipeParser();
    void scan();
    void readString();
    void readNumber();
    void parse();
    void addRecipe();
    void addFood();
};