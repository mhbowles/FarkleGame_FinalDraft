/*
* Author:		Milo Bowles
* Email:		milo.bowles@snhu.edu
* Date:			12/6/2023
* Class:		IT-312 Software Devel w/C++
* Assignment:	7-1 Final Project - Farkle Game
* 
* Contains header function declarations and defaults
* for the ValidatedUserInput class
*/
#ifndef MILO_CONSOLE_H
#define MILO_CONSOLE_H

#include <string>
#include <limits>

/*
* This class contains static functions to validate user input of various types
*/
class ValidatedUserInput {
public:
	ValidatedUserInput();	// define default constructor

	// declare static functions
	static double getDouble(std::string prompt = "",
		double min = std::numeric_limits<double>::min(),	
		double max = std::numeric_limits<double>::max(),	
		bool isInclusive = true);
	static int getInt(std::string prompt = "",
		int min = std::numeric_limits<int>::min(),
		int max = std::numeric_limits<int>::max(),
		bool isInclusive = true);							
	static char getChar(std::string prompt, char validChars[],
		bool isInsensitive = true);		
	static std::string getString(std::string prompt = "", bool isInsensitive = true);
};

#endif MILO_CONSOLE_H