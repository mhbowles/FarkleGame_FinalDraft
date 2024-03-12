/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/6/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains header declarations for the Die class
*/
#ifndef MILO_DIE_H
#define MILO_DIE_H

/*
* Class to randomly roll a six sided die
*/
class Die {

private:
	int value;
public:
	Die();
	int getValue();
	void roll();
};

#endif MILO_DIE_H