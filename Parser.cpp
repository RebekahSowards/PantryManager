#include "Parser.h"

Parser::Parser() {

}

Parser::Parser(string filename, Pantry * setPantry) {
	//The constructor does all the heavy lifting of program flow for this class
	in.open(filename);
	myPantry = setPantry;
	scan();
	parse();
}

Parser::~Parser() {
	//The destructor closes the filestream
	in.close();
}

void Parser::scan() {
	//Looks at every character until the end of the file
	c = in.get();
	bool eof = false;
	while (!eof) {
		switch (c) {
		case '\n' :
			c = in.get();
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

void Parser::readString() { //for food names and units
	string str;
	while (isalpha(c) || c == ' ') {
		str += c;
		c = in.get();

	}
	myTokens.push_back(str);
}

void Parser::readNumber() { //for quantity and also for calories (someday)
	string num;
	while (isdigit(c) || c == '.') {
		num += c;
		c = in.get();

	}
	myTokens.push_back(num);
}

void Parser::parse() { //runs through the tokens
	while (myTokens[tokenIt] != "EOF") {
		addFood();
	}
}

void Parser::addFood() { //adds food to the pantry pointer passed into the constructor
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
	myPantry->addFood(newFood);
}