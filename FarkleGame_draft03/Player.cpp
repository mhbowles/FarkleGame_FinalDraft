/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/7/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains the function definitions for a Player class
*/
#include <stdexcept>
#include <sstream>
#include "Dice.h"
#include "Player.h"

using namespace std;

//-------------------------------------------------------
//				PUBLIC FUNCTIONS
//-------------------------------------------------------

// Default Player constructor, sets variable defaults
// marks player number as -1 (constructed with no number)
Player::Player() {
	number = -1; 
	setTotalScore(0);
	setTurn(1);
	hasEntered = false;
}

// Constructor for player, sets number as passed, 
// and defaults for the other variables
Player::Player(int number) {
	setNumber(number);
	setTotalScore(0);
	setTurn(1);
	hasEntered = false;
}

void Player::setNumber(int numberP) {
	if (numberP < 1) {
		throw invalid_argument("Number must 1 or greater.");
	}
	number = numberP;
}

int Player::getNumber() {
	return number;
}

void Player::setTotalScore(int score) {
	if (score < 0) {
		throw invalid_argument("Score must be positive.");
	}
	totalScore = score;
}

int Player::getTotalScore() {
	return totalScore;
}

void Player::setHasEntered(bool hasEnteredP) {
	hasEntered = hasEnteredP;
}

bool Player::getHasEntered() {
	return hasEntered;
}

void Player::setTurn(int turnP) {
	if (turnP < 0) {
		throw invalid_argument("Score must be positive");
	}
	turn = turnP;
}

// increments player turn by 1
void Player::incrementTurn() {
	turn++;
}

int Player::getTurn() {
	return turn;
}

// returns whether or not the passed player is equal to this one,
// equality based on the turn, number, and total score of each players
bool Player::equals(Player& player) {
	bool isEqual = false;
	if (player.getTurn() == this->turn
		&& player.getNumber() == this->number
		&& player.getTotalScore() == this->totalScore) {
		
		isEqual = true;
	}
	return isEqual;
}

// returns formatted string of the Player variables
string Player::toString() {
	string enteredGame = hasEntered ? "(Entered)" : "(Not Entered)";
	ostringstream sstream;
	sstream << enteredGame << "\n"
			<< "Player: " << number << "  "
			<< "Turn: " << turn << "  "
			<< "Total Score: " << totalScore << "\n";
	return sstream.str();
}