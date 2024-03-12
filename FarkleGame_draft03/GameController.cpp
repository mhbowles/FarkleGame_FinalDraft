/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/6/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains function definitions for GameController class,
* and static variables to determine certain game conditions
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include "GameController.h"
#include "Dice.h"
#include "LinkedList.h"
#include "Player.h"
#include "ValidatedUserInput.h"

using namespace std;

// helper function declarations
bool checkIfPointDiceToHold(vector<Die> dice);
void pressEnterToContinue();

//-------------------------------------------------------
//				PUBLIC FUNCTIONS
//-------------------------------------------------------

// conditions for entering and winning the Farkle game
static int enteringScore = 500;
static int winningScore = 10000;

/*
* Initializes GameController variables to game defaults
*/
GameController::GameController() {
	players = LinkedList<Player>();
	winner = NULL;		// no winner at initialization
	turnScore = 0;
	activeDice = 6;
	isTurnOver = false;
	isGameOver = false;
	hasRerolled = false;
	dice = Dice();
}

/*
* Prepares the game to be played and then starts
* Read rules, fills player linked list, then begins the game loop
*/
void GameController::prepAndStartsGame() {
	readRules();

	// add a valid number of players to the players list
	string prompt = "Number of players: ";
	int numPlayers = ValidatedUserInput::getInt(prompt, 2, 
												numeric_limits<int>::max());
	for (int i = 0; i < numPlayers; i++) {
		int playerNum = i + 1;
		Player player = Player(playerNum);
		players.addToEnd(player);
	}

	// and here. We. Go.
	startGame();
}

//-------------------------------------------------------
//				PRIVATE FUNCTIONS
//-------------------------------------------------------

/*
* Runs the main game loop of player turns, and winning
*/
void GameController::startGame() {

	//start with the first player in the players list
	Node<Player>* playerNode = players.getLast()->next;
	do {
		Player& player = playerNode->data;
		takeTurn(player);

		//check for winner - if so, start final turn
		if (player.getTotalScore() >= winningScore) {
			takeLastChanceTurns(player);
		}

		//turn moves to next player
		playerNode = playerNode->next;
	} while (!isGameOver);

	cout << "Player " << winner->getNumber() << " wins!\n\n";
	cout << "Game over. Thank you for playing!\n";
}

/*
* Writes the Farkle game rules from the rule file
*/
void GameController::readRules() {

	string fileName = "farkle_rules.txt";

	ifstream inFile;
	inFile.open(fileName);
	if (inFile) {		// if file opened successfully

		// print each line of the file to console
		string line;
		while (getline(inFile, line)) {

			cout << line << "\n";

		}
		// pause for input to let the viewer read the rules
		pressEnterToContinue();
	}
	else {				// file didn't open - error message
		cout << "Error opening file. Goodbye.\n\n";
	}

}

/*
* Starts a new turn for the passed player
* Continues to roll the dice until the user stops rolling
* @param	player		- a reference to the player whose turn it is
*/
void GameController::takeTurn(Player& player) {
	
	// initialize variables for the start of the turn
	isTurnOver	= false;
	hasRerolled = false;
	activeDice	= 6;
	turnScore	= 0;

	// display player number, turn and total score
	system("cls");
	cout << player.toString() << "\n";

	// continue to roll dice, or stop, based on user input
	string prompt = "Roll dice? (y/n): ";
	char validChars[] = "yn";
	char choice;
	while (!isTurnOver) {

		if (activeDice == 0) {
			stopRolling(player);	// stop if there are no active dice
		}
		else if (!player.getHasEntered()) {
			rollDice(player);		// roll if player hasn't entered
		}
		else {
			// otherwise, ask player to roll or stop
			choice = ValidatedUserInput::getChar(prompt, validChars);
			switch (choice) {
			case 'y':
				rollDice(player);
				break;
			case 'n':
				stopRolling(player);
				break;
			}
		}
	}
	// print turn results
	int wCol1 = 15;
	int wCol2 = 7;
	cout << "\nTurn Results\n"
		 << left << setw(wCol1) << "Turn score: " 
		 << right << setw(wCol2) << turnScore << "\n"
		 << left << setw(wCol1) << "Total score: " 
		 << right << setw(wCol2) << player.getTotalScore() << "\n\n";
	
	pressEnterToContinue();

	// increment player turn by 1
	player.incrementTurn();
}

/*
* Each player in the game, other than the winner, gets a final turn
* to see if they can top the winning score. 
* @param	potentialWinner		- the winner of the game before last chances
*/
void GameController::takeLastChanceTurns(Player& potentialWinner) {

	// the potential winner becomes the winner for now
	winner = &potentialWinner;

	cout << "Player " << potentialWinner.getNumber()
		 << " is about to win with " << potentialWinner.getTotalScore()
		 << " points.\nLast chance to pull ahead.\n";
	
	pressEnterToContinue();

	// traverse the list once
	Node<Player>* playerNode = players.getLast()->next;
	do {
		// every player but the potential winner gets a last chance turn
		Player player = playerNode->data;
		if (!player.equals(potentialWinner)) {
			
			takeTurn(player);

			// if player scores higher than the current winner, becomes the new winner
			if (player.getTotalScore() > winner->getTotalScore()) {
				winner = &player;
			}
		}
		// move to next player
		playerNode = playerNode->next;
	} while (playerNode != players.getLast()->next);

	// this is the final turn - so end the game
	isGameOver = true;
}

/*
* Rolls all active dice, then Prints and scores roll results
* @param	player		- a reference to the player whose turn it is
*/
void GameController::rollDice(Player& player) {
	dice.setDie(activeDice);	// make sure only the active dice are rolled
	dice.rollAll();
	cout << dice.toString();
	vector<Die> rollResults = dice.getDice();
	scoreDice(player, rollResults);
}

/*
* Ends the players turn
* Adds the turn score to the player total score - if they have entered game
* Discards player turn score if they haven't entered the game
* @param	player		- a reference to the player whose turn it is
*/
void GameController::stopRolling(Player& player) {
	
	// discard player turn score if they have not entered game
	if (!player.getHasEntered() && turnScore != 0) {
		turnScore = 0;
	}
	// total the players turn score if they have one.
	if (turnScore != 0) {
		int totalScore = player.getTotalScore();
		int newTotal = totalScore + turnScore;
		player.setTotalScore(newTotal);
	}
	isTurnOver = true;
}

/*
* Scores point dice and updates turn score based on player results.
* @param	player		- a reference to the player whose turn it is
* @param	rollResults	- a list of all the die rolled by the player
*/
void GameController::scoreDice(Player& player, std::vector<Die>& rollResults) {
	
	// list of the die the player has chosen to score
	// every die is scored by default
	vector<Die> diceToScore = rollResults;

	// determine whether to hold dice based on user input
	string prompt = "Hold any dice? (y/n): ";
	char validChars[] = "YN";
	char choice = ValidatedUserInput::getChar(prompt, validChars);
	if (choice == 'y') {
		holdDice(diceToScore);
	}

	// counts each face value into an array of all possible face values
	int faceValueCounts[6] = { 0 };
	for (Die die : diceToScore) {
		int faceValue = die.getValue();
		int faceValueIdx = faceValue - 1;
		faceValueCounts[faceValueIdx] += 1;
	}

	// point dice counter
	int pointDice = 0;

	// count and score all point dice of each face value
	// (1s, 5s, or three of a kinds)
	for (int i = 0; i < 6; i++) {

		int faceValue = i + 1;

		// score any three of a kind
		if (faceValueCounts[i] >= 3) {
			
			// identify if there is one three of a kind, or two
			int numThreeOfAKinds = faceValueCounts[i] / 3;

			pointDice += (3 * numThreeOfAKinds);
			
			// score each three of a kind
			for (int j = 0; j < numThreeOfAKinds; j++) {

				if (faceValue == 1) {
					cout << "3 1s - Three eyed snake!\n";
					turnScore += 1000;
				}
				else {
					cout << "3 " << faceValue << "s - Three of a kind!\n";
					turnScore += faceValue * 100;
				}
			}
		}

		// score any 1s and 5s - that aren't three of a kind
		if (faceValue == 1) {
			
			// display all ones - with three of a kinds
			cout << faceValueCounts[i] << " 1s.\n";

			// score any that aren't three of a kind
			int remainders = faceValueCounts[i] % 3;
			pointDice += remainders;
			turnScore += remainders * 100;
			
			
		}
		else if (faceValue == 5) {
			
			// display all fives - with three of a kinds
			cout << faceValueCounts[i] << " 5s.\n";

			// score any that aren't three of a kind
			int remainders = faceValueCounts[i] % 3;
			pointDice += remainders;
			turnScore += remainders * 50;
		}
		
	}

	// remove any point dice scored from the active dice (to roll)
	activeDice -= pointDice;
	cout << "Turn score: " << turnScore << "\n\n";
	checkIfPlayerCanEnter(player);

	// check for farkle, or reroll, or no dice to roll
	if (pointDice == 0) {
		farkle(player);
	}
	else if (pointDice == 6 && !hasRerolled) {
		reroll(player);
	}
	else if (activeDice == 0) {
		stopRolling(player);
	}
}

/*
* Removes dice to be rolled again from the list of dice to score,
* and displays new dice to be scored - based on user selection
* Keeps holding dice until the user says otherwise
* @param	diceToScore	- the dice that will be scored and set aside
*/
void GameController::holdDice(vector<Die>& diceToScore) {
	char choice = 'y';
	while (choice == 'y') {
		
		bool arePointDiceToHold = checkIfPointDiceToHold(diceToScore);

		if (!arePointDiceToHold) {
			cout << "No point dice to hold.\n";
			choice = 'n';
		}
		else {
			stringstream stringstream;
			stringstream << "Which die to hold? (1-" << diceToScore.size() << "): ";
			string promptDieToHold = stringstream.str();
			int dieToHold = ValidatedUserInput::getInt(promptDieToHold, 1, diceToScore.size());
			int dieToHoldIdx = dieToHold - 1;

			// remove the given die number
			diceToScore.erase(diceToScore.begin() + dieToHoldIdx);

			// display dice - updated with removal
			for (Die die : diceToScore) {
				cout << die.getValue() << " ";
			}
			cout << "\n";

			char validChars[] = "yn";
			choice = ValidatedUserInput::getChar("Hold any more dice? (y/n): ", validChars);
		}
	}
}

/*
* Discards turn score, displays a farkle message, and stops rolling
* @param	player		- a reference to the player whose turn it is
*/
void GameController::farkle(Player& player) {
	turnScore = 0;
	cout << "No point dice. FARKLE. Turn score discarded.\n";
	stopRolling(player);
}

/*
* Takes an extra roll of six dice before the user can choose to stop
* @param	player		- a reference to the player whose turn it is
*/
void GameController::reroll(Player& player) {
	cout << "6 point die. REROLL.\n\n";
	activeDice = 6;
	hasRerolled = true;
	rollDice(player);
}

/*
* Checks if the player can enter the game - enter them if so
* @param	player		- a reference to the player whose turn it is
*/
void GameController::checkIfPlayerCanEnter(Player& player) {
	if (turnScore >= enteringScore && !player.getHasEntered()) {
		player.setHasEntered(true);
		cout << "You've entered the game!\n\n";
	}
}

//-------------------------------------------------------
//				HELPER FUNCTIONS
//-------------------------------------------------------

// pauses game until user presses enter
void pressEnterToContinue() {
	cout << "Press enter to continue: ";
	cin.get();
	system("cls");
}

// Checks if there are point dice availible to hold in the given array
// Returns true if there is 1 or more, false if 1 or less
bool checkIfPointDiceToHold(vector<Die> dice) {

	int pointDice = 0;

	// counts number of each face value into an array
	int faceValuesArray[6] = { 0 };
	for (Die die : dice) {
		int faceValue = die.getValue();
		int faceValueIdx = faceValue - 1;
		faceValuesArray[faceValueIdx]++;
	}

	// counts point dice based off face values
	for (int i = 0; i < 6; i++) {

		int faceValue = i + 1;
		switch (faceValue) {
		case 1:
		case 5:
			pointDice += faceValuesArray[i];
			break;
		default:
			if (faceValuesArray[i] >= 3) {
				// in this case, count three of a kind as one point dice
				int numThreeOfAKinds = faceValuesArray[i] / 3;
				pointDice += numThreeOfAKinds;	
			}
			break;
		}

	}
	return (pointDice > 1);
}