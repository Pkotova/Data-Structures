#pragma once
#include"Error.h"
#include"LinkedList.h"
#include "IMLRepository.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>

class ErrorRepository
{
private:
	std::string script;
	std::string errors; // caught errors

public:
	ErrorRepository();
	LinkedList<Error>* errorList();
	std::string returnByCode(int _code);
	std::string getScript();

	std::string clearSpaces();
	LinkedList<std::string>& fullSplit();
	LinkedList<std::string>& halfSplit();

	int countOpenSymbols(); // count <
	int countCloseSymbols(); // count >

	bool isDigit(std::string data);
	bool isDigit(char symbol);
	bool isSupportedTag(std::string tag);
	bool isSyntaxClear();

	LinkedList<std::string>& getAllData();
	bool isValidAGGTag(std::string tag);
	bool isValidSRTTag(std::string tag);
	bool isValidMAPTag(std::string tag);

	bool missingSymbol(); // check if < or > is missing
	bool isMissingTag(); // opening or closing 
	bool numericParameters(); // check if tag parameters are numberic 
	bool isMissingAttribute(); // or more attributes 

	int countErrors();
	std::string cleanScript();
};

