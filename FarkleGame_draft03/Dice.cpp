/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/6/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains function definitions for the Dice class
*/
#include <sstream>
#include <cstdlib>
#include <vector>
#include "Dice.h"

using namespace std;

//-------------------------------------------------------
//				PRIVATE FUNCTIONS
//-------------------------------------------------------

/*
* Adds the given die to the list of dice
* @param	die		- the die to add to the list of dice
*/
void Dice::addDie(Die die) {
	dice.push_back(die);
}

//-------------------------------------------------------
//				PUBLIC FUNCTIONS
//-------------------------------------------------------

/*
* Default constructor clears list of dice
*/
Dice::Dice() {
	dice.clear();
}

/*
* Fills list of dice with the given number of dice
* @param	numDie		
			- the number of dice to fill the array with
*/
void Dice::setDie(int numDie) {
	dice.clear();
	for (int i = 0; i < numDie; i++) {
		addDie(Die());
	}
}

/*
* Rolls all the die in the list of dice
*/
void Dice::rollAll() {
	for (Die& die : dice) {
		die.roll();
	}
}

/*
* Retrieves list of dice
* @returns	list of dice
*/
vector<Die> Dice::getDice() {
	return dice;
}

/*
* Retrieves a string of all the die in the list of dice
* @returns	string of die in the list of dice
*/
string Dice::toString() {

	ostringstream sstream;
	for (Die& die : dice) {
		sstream << die.getValue() << ' ';
	}
	sstream << '\n';
	return sstream.str();
}
