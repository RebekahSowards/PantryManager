//If I come back to edit this program, I want to add more classes to the main function to make it more streamlined.

#include <iostream>
#include <vector>
#include "Parser.h"
#include "RecipeParser.h"
#include "Food.h"
#include "Recipe.h"
#include "Pantry.h"

void displayUnits() {
    cout << "1: ounce" << endl << 
        "2: pound" << endl << 
        "3: fluid ounce" << endl << 
        "4: cup" << endl << 
        "5: pint" << endl << 
        "6: quart" << endl << 
        "7: gallon" << endl << 
        "8: teaspoon" << endl <<
        "9: tablespoon" << endl <<
        "10: other" << endl <<
        "11: ";
}

string checkUnit(int userUnit) {
    switch (userUnit) {
    case 1:
        return "oz";
    case 2:
        return "lb";
    case 3:
        return "fl oz";
    case 4:
        return "cup";
    case 5:
        return "pt";
    case 6:
        return "qt";
    case 7:
        return "gal";
    case 8:
        return "tsp";
    case 9:
        return "tbsp";
    case 10:
        return "other";
    case 11:
        return "unit";
    default:
        return "0";
    }
}

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        return 1;
    }

    Pantry * myPantry = new Pantry();
    
    Parser * myParser = new Parser(argv[1], myPantry); //This constructor is the only time the class is used.
    
    RecipeManager * myRecipeManager = new RecipeManager(myPantry);
    
    RecipeParser * myRecipeParser = new RecipeParser(argv[2], myRecipeManager); //This constructor is the only time the class is used.
    
    //The food and recipes are processed from pantry.txt and recipe.txt by the parsing classes.
    //The parsers are modeled after a project from CS 236, if less complicated.
    
    
    cout << "Welcome to PantryManager!" << endl << 
            "Choose what you would like to do." << endl;
            
    int userChoice = 1;
    
    while (userChoice) { 
        //The user interface is simple and has very little way of checking to see if the input matches expected input.
        //This is because the program was built mostly for my own use.
        cout << "0: Close program" << endl <<
            "1: Add foods" << endl <<
            "2: Choose a recipe to make now" << endl <<
            "3: Plan a shopping trip" << endl <<
            "4: Report miscellaneous food consumption" << endl;
        cin >> userChoice;
        
        if (userChoice == 1) { 
//Adding a food
            cout << "Type \"0\" to add a food not included in the following list." << endl <<
                "Else type the number next to the food you would like to add more of." << endl;
            vector<string> pantryFoods = myPantry->getFoods();
            int numberOfFoods = pantryFoods.size();
            for (int i = 0; i < numberOfFoods; i++) {
                cout << i + 1 << ": " << pantryFoods[i] << endl;
            }
            int foodChoice;
            cin >> foodChoice;
            if (!foodChoice) { 
    //If the user enters 0 to add a brand new food
                string foodName;
                int unit;
                string unitString = "0";
                int calories = -1;
                double quantity;
                cout << "Please enter a food name: ";
                getline(cin, foodName);
                getline(cin, foodName);
                cout << "Please choose a unit: " << endl;
                while (unitString == "0") {
                    displayUnits();
                    cout << foodName << "(s)" << endl;
                    cin >> unit;
                    unitString = checkUnit(unit);
                    if (unitString == "other") {
                        cout << "Please enter an alternative unit: ";
                        cin >> unitString;
                    }
                }
                cout << "Please enter a quantity: ";
                cin >> quantity;
                cout << "Would you like to enter a calorie number? (calories/" << unitString << ")" << endl << "1: Yes" << endl << "0: No" << endl;
                bool cal;
                cin >> cal;
                if (cal) {
                    cout << "Please enter a calorie number: ";
                    cin >> calories;
                }
                myPantry->addFood(Food(unitString, foodName, quantity, calories));
                cout << "Added " << quantity << " " << unitString << "(s)." << endl;
            }
            else { 
    //If the user enters a food number to add some unit of an existing food
                cout << "Add how many " << myPantry->myFoods[pantryFoods[foodChoice-1]].getUnit() << "(s)?" << endl;
                int quantity;
                cin >> quantity;
                myPantry->myFoods[pantryFoods[foodChoice-1]].addItems(quantity);
                cout << "Added " << quantity << " " << myPantry->myFoods[pantryFoods[foodChoice-1]].getUnit() << "(s)." << endl;
            }
            cout << "Continue using PantryManager?" << endl << "1: Yes" << endl << "0: No" << endl;
            cin >> userChoice;
        }
        if (userChoice == 2) {
//Making a recipe
            vector<string> recipeTitles = myRecipeManager->checkRecipes();
            int numberOfRecipes = recipeTitles.size();
            cout << "You have ingredients for " << numberOfRecipes << " recipes(s) saved in PantryManager:" << endl;
    //Displays recipes with matching ingredients, if none, asks the user if they want to go shopping
            if (numberOfRecipes == 0) {
                cout << "Would you like to plan a shopping trip?" << endl << "1: Yes" << endl << "0: No" << endl;
                cin >> userChoice;
                if (userChoice) {
                    userChoice = 3;
                }
                else {
                    userChoice = 2;
                }
            }
            else {
                for (int i = 0; i < numberOfRecipes; i++) {
                    cout << i + 1 << ": " << recipeTitles[i] << endl;
                }                
                cout << "Make a recipe?" << endl << "(Enter recipe number or \"0\" for \"No\")" << endl;
                int recipeChoice;
                cin >> recipeChoice; 
                if (recipeChoice) {
    //User chooses a recipe, the ingredient totals from the recipe are subtracted from the pantry
                    myRecipeManager->makeRecipe(recipeTitles[recipeChoice - 1]);
                    cout << "Your ingredient usage has been reported!" << endl;
                }
                cout << "Continue using PantryManager?" << endl << "1: Yes" << endl << "0: No" << endl;
                cin >> userChoice;
            }
        }
        if (userChoice == 3) {
//Plan a shopping trip
            cout << "Let's plan your shopping trip! Select a number to add a recipe!" << endl;
            vector<string> recipeTitles = myRecipeManager->getTitles();
            set<string> recipeList;
            int numberOfRecipes = recipeTitles.size();
            int recipeChoice = 1;
            while(recipeChoice) {
    //When user enters "0" the shopping list is created from the chosen recipes and the ingredients not available in the pantry
                cout << "0: Done adding recipes" << endl;
                for (int i = 0; i < numberOfRecipes; i++) {
                    cout << i + 1 << ": " << recipeTitles[i] << endl;   
                }
                cin >> recipeChoice;
                if(recipeChoice) {
                    recipeList.insert(recipeTitles[recipeChoice - 1]);
                    cout << "Added " << recipeTitles[recipeChoice - 1] << endl;
                }
            }
            myRecipeManager->shoppingList(recipeList);
    //The shopping list is printed to a .txt file
            cout << "Shopping list printed to \"shopping.txt\"" << endl;
            cout << "Continue using PantryManager?" << endl << "1: Yes" << endl << "0: No" << endl;
            cin >> userChoice;
        }
        if (userChoice == 4) {
//To keep pantry numbers up to date, a miscellaneous consumption option
            cout << "Type \"0\" to cancel." << endl <<
                "Else type the number next to the food you ate." << endl;
            vector<string> pantryFoods = myPantry->getFoods();
            int numberOfFoods = pantryFoods.size();
            for (int i = 0; i < numberOfFoods; i++) {
                cout << i + 1 << ": " << pantryFoods[i] << endl;
            }
            int foodChoice;
            cin >> foodChoice;
            if (foodChoice) {
                cout << "Ate how many " << myPantry->myFoods[pantryFoods[foodChoice-1]].getUnit() << "s?" << endl;
                int quantity;
                cin >> quantity;
                myPantry->myFoods[pantryFoods[foodChoice-1]].useItems(quantity);
                cout << "Removed " << quantity << " " << myPantry->myFoods[pantryFoods[foodChoice-1]].getUnit() << "(s)." << endl;
            }
            cout << "Continue using PantryManager?" << endl << "1: Yes" << endl << "0: No" << endl;
            cin >> userChoice;
        }
    }
    
    //delete all "new" objects from the top of the program
    delete myPantry;
    delete myParser;
    delete myRecipeManager;
    delete myRecipeParser;
    return 0;
}