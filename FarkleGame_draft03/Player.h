/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/6/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains header function declarations and defaults for a Player class
*/
#ifndef MILO_PLAYER_H
#define MILO_PLAYER_H

#include <string>

// This class contains basic variables and functions,
// a player in a game might need
class Player {
private:
	int number;
	int totalScore;
	int turn;
	bool hasEntered;
public:
	Player();
	Player(int number);

	void setNumber(int number);
	int getNumber();

	void setTotalScore(int score);
	int getTotalScore();

	void setHasEntered(bool hasEnteredP);
	bool getHasEntered();

	void setTurn(int turn);
	void incrementTurn();
	int getTurn();

	bool equals(Player& player);

	std::string toString();
};


#endif MILO_PLAYER_H