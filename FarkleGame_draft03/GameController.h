/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/6/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains header declarations for GameController class
*/
#ifndef MILO_GAMECONT_H
#define MILO_GAMECONT_H

#include <string>
#include <vector>
#include "Player.h"
#include "Dice.h"
#include "LinkedList.h"

class GameController {

private:
	LinkedList<Player> players;
	Player* winner;
	Dice dice;
	int	 turnScore;
	int	 activeDice;
	bool isTurnOver;
	bool isGameOver;
	bool hasRerolled;

	void startGame();
	void readRules();
	void takeTurn(Player& player);
	void takeLastChanceTurns(Player& winner);
	void rollDice(Player& player);
	void stopRolling(Player& player);
	void scoreDice(Player& player, std::vector<Die>& rollResults);
	void holdDice(std::vector<Die>& diceToScore);
	void farkle(Player& player);
	void reroll(Player& player);
	void checkIfPlayerCanEnter(Player& player);

public:
	GameController();
	void prepAndStartsGame();
};

#endif MILO_GAMECONT_H

