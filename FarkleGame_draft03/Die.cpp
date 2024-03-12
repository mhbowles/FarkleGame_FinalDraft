/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/6/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains function definitions for the Die class
*/
#include <cstdlib>
#include <ctime>
#include "Die.h"

using namespace std;

//-------------------------------------------------------
//				PUBLIC FUNCTIONS
//-------------------------------------------------------

Die::Die() {
	srand(time(nullptr));
	value = 1;
}

int Die::getValue() {
	return value;
}

// rolls the dice to a random value 1-6
void Die::roll() {
	int randNum = rand() % 6; //random number 0-5
	value = randNum += 1; //random number 1-6
}
