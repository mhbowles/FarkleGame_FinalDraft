/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/6/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains header declarations for the Dice class
*/
#ifndef MILO_DICE_H
#define MILO_DICE_H

#include <string>
#include <vector>
#include "Die.h"

/*
* Class to manipulate and roll several dice at once
*/
class Dice {

private:
	std::vector<Die> dice;

	void addDie(Die die);

public:
	Dice();
	void setDie(int numDie);
	void rollAll();
	std::vector<Die> getDice();
	std::string toString();
};

#endif MILO_DICE_H