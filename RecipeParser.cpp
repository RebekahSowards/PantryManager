#include "RecipeParser.h"

RecipeParser::RecipeParser() {
    
}

RecipeParser::RecipeParser(string filename, RecipeManager * setRecipeManager) {
    //The constructor does all the heavy lifting of program flow for this class
    in.open(filename);
    myRecipeManager = setRecipeManager;
    scan();
    parse();
}

RecipeParser::~RecipeParser() {
    //The destructor closes the filestream
    in.close();
}

void RecipeParser::scan() {
    //Looks at every character until the end of the file
    c = in.get();
    bool singleEndLine = false;
    while (!eof) {
        switch (c) {
        case '\n' :
            c = in.get();
            if (singleEndLine) {
                //There is a line break between recipes handled in this if statement
                myTokens.push_back("EOR");
                singleEndLine = false;
            }
            else {
                singleEndLine = true;
            }
            break;
        case -1 : //end of file
            eof = true;
            myTokens.push_back("EOF");
            break;
        case '-' : //A non-unit marker (eg: eggs are just eggs, you don't have a cup of eggs)
            myTokens.push_back("-");
            c = in.get();
            break;
        default:
            singleEndLine = false;
            if (isspace(c)) { //keeps the program going
                c = in.get();
                break;
            }
            if (isalpha(c)) { //passes to a function to read strings, which includes spaces (as in "Flour Tortilla")
                readString();
                break;
            }
            if (isdigit(c) || c == '.') { //passes to a function to read doubles
                readNumber();
                break;
            }
        }
    }
}

void RecipeParser::readString() { //for recipe name, food names, and units
    string str;
    while (isalpha(c) || c == ' ') {
        str += c;
        c = in.get();
    }
    myTokens.push_back(str);
}

void RecipeParser::readNumber() { //for cook time, quantity, and calories (someday)
    string num;
    while (isdigit(c) || c == '.') {
        num += c;
        c = in.get();
        
    }
    myTokens.push_back(num);
}

void RecipeParser::parse() { //runs through the tokens
    while (myTokens[tokenIt] != "EOF") {
        addRecipe();
    }
}

void RecipeParser::addRecipe() { //goes until it hits "EOR" (end of recipe)
    string title;
    int cookTime = 0;
    title = myTokens[tokenIt];
    tokenIt++;
    cookTime = stoi(myTokens[tokenIt]);
    tokenIt++;
    newRecipe = Recipe(title, cookTime);
    while (myTokens[tokenIt] != "EOR" && myTokens[tokenIt] != "EOF") {
        addFood();
    }
    myRecipeManager->addRecipe(newRecipe);
    if (myTokens[tokenIt] == "EOR") {
        tokenIt++;
    }
}

void RecipeParser::addFood() { //adds food to the current recipe
    string name;
    double quantity = 0;
    int caloriePer = -1;
    string unit;
    name = myTokens[tokenIt];
    tokenIt++;
    quantity = stod(myTokens[tokenIt]);
    tokenIt++;
    unit = myTokens[tokenIt];
    tokenIt++;
    if (isdigit(myTokens[tokenIt][0])) {
        caloriePer = stoi(myTokens[tokenIt]);
        tokenIt++;
    }
    Food newFood = Food(unit, name, quantity, caloriePer);
    newRecipe.addFood(newFood);
}