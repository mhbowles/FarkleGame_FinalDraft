/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/6/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains function definitions for the ValidatedUserInput class
*/
#include <iostream>
#include <string>
#include <limits>
#include "ValidatedUserInput.h"

// declare helper functions
void discardRemainingChars();
void handleInvalidInput();
bool checkRangeInclusive(double num, double min, double max);
bool checkRangeExclusive(double num, double min, double max);
bool checkValidChar(char choice, char validChars[]);

//-------------------------------------------------------------
//				PUBLIC FUNCTION DEFINITIONS (all static)
//-------------------------------------------------------------

/*
* Gets a valid double from the console and returns it
* @param	prompt			text to display before input, default: empty string
* @param	min				low bound of valid input range, default: double minumum size
* @param	max				high bound of valid input range, default: double maximum size
* @param	isInclusive		determines if validity is inclusive of bounds or not,
							default: inclusive
* @returns	A valid double within the given bounds.
*/
double ValidatedUserInput::getDouble(std::string prompt, double min, double max, bool isInclusive) {
	double num = 0.0;
	bool isValid = false;
	while (!isValid) {
		std::cout << prompt;
		if (!(std::cin >> num)) {	// if the input stream errors, handle it
			handleInvalidInput();
		}
		else {
			discardRemainingChars();
			if (isInclusive) {
				isValid = checkRangeInclusive(num, min, max);
			}
			else {
				isValid = checkRangeExclusive(num, min, max);
			}
		}
	}
	return num;
}

/*
* Gets a valid integer from the console and returns it
* @param	prompt			- text to display before input (default: empty string)
* @param	min				- low bound of valid input range (default: integer minimum size)
* @param	max				- high bound of valid input range (default: integer maximum size)
* @param	isInclusive		- determines if validity is inclusive of bounds or not
							  (default: inclusive)
* @returns	A valid integer within the given bounds.
*/
int ValidatedUserInput::getInt(std::string prompt, int min, int max, bool isInclusive) {
	int num = 0;
	bool isValid = false;
	while (!isValid) {
		std::cout << prompt;
		if (!(std::cin >> num)) {	// if the input stream errors, handle it
			handleInvalidInput();
		}
		else {
			discardRemainingChars();
			if (isInclusive) {
				isValid = checkRangeInclusive(num, min, max);
			}
			else {
				isValid = checkRangeExclusive(num, min, max);
			}
		}
	}
	return num;
}

/*
* Gets a valid character from the console and returns it.
* @param	prompt				- text to display before input
* @param	validChars[]		- a list of valid characters that can be returned
* @param	isInsensitive		- case sensitivity for checking if valid (default: insensitive)
* @returns	A valid character of given case sensitivity
*/
char ValidatedUserInput::getChar(std::string prompt, char validChars[], bool isInsensitive) {
	char choice = 'n';
	bool isValid = false;
	while (!isValid) {
		std::cout << prompt;
		std::cin >> choice;
		discardRemainingChars();
		if (isInsensitive) {
			// make user character choice lowercase
			choice = tolower(choice);

			// make valid character list lowercase
			for (int i = 0; i < sizeof(validChars); i++) {
				validChars[i] = tolower(validChars[i]);
			}
		}
		isValid = checkValidChar(choice, validChars);
	}
	return choice;
}

/*
* Gets a valid string from the console and returns it.
* @param	prompt				- text to display before input (default: no text)
* @param	isInsensitive		- returns input in lowercase if true, unchanged if false,
*								  (default: insensitive)
* @returns	A valid string of given case sensitivity
*/
std::string ValidatedUserInput::getString(std::string prompt, bool isInsensitive) {
	std::string choice = "";
	std::cout << prompt;
	std::cin >> choice;
	discardRemainingChars();
	if (isInsensitive) {
		//make string choice lowercase
		for (char& c : choice) {
			c = tolower(c);
		}
	}
	return choice;
}

//-------------------------------------------------------------
//				HELPER FUNCTION DEFINITIONS
//-------------------------------------------------------------

// clears input buffer of all characters
void discardRemainingChars() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// displays an invalid input message and resets cin object to a good state
void handleInvalidInput() {
	std::cout << "Error. Invalid input. Try again.\n\n";
	std::cin.clear();			// clear the failure flag
	discardRemainingChars();
}

// checks character choice agains the valid character array
// returns whether character is in array - displays error if not
bool checkValidChar(char choice, char validChars[]) {
	bool isInArray = false;
	for (int i = 0; i < sizeof(validChars); i++) {
		if (choice == validChars[i]) {
			isInArray = true;
			break;
		}
	}
	if (!isInArray) {
		std::cout << "Error. Invalid character. Try again.\n\n";
	}
	return isInArray;
}

// checks if given number is within given range - bounds are inclusive
// returns whether number is in range - displays detailed error if not
bool checkRangeInclusive(double num, double min, double max) {
	bool isInRange = false;
	if (num < min) {
		std::cout << "Error. Number must be " << min << " or greater. Try again.\n\n";
	}
	else if (num > max) {
		std::cout << "Error. Number must be " << max << " or less. Try again.\n\n";
	}
	else {
		isInRange = true;
	}
	return isInRange;
}

// checks if the given number is within the given range - bounds are exclusive
// returns whether number is in range - displays detailed error if not
bool checkRangeExclusive(double num, double min, double max) {
	bool isInRange = false;
	if (num <= min) {
		std::cout << "Error. Number must greater than "
			<< min << ". Try again.\n\n";
	}
	else if (num >= max) {
		std::cout << "Error. Number must be less than "
			<< max << ". Try again.\n\n";
	}
	else {
		isInRange = true;
	}
	return isInRange;
}