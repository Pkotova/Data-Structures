#pragma once
#include"Error.h"
#include"LinkedList.h"
#include "String.h"
#include"IMLRepository.h"
#include<string>
class ErrorRepository
{
private: 
	std::string script;
	
public:
	string getScript() ;
	LinkedList<Error>* read();
	void printByCode(int code);
	Error& getByCode(int code);
	int countOpenSymbol(); // <
	int countCloseSymbol(); // >
	string removeSpaces();
	LinkedList<string>& splitString();
	LinkedList<string>& halfSplit();
	bool isDigit(char symbol); 
	bool isDigit(string symbol);
	bool hasEnoughOpenCloseSymbols();
	bool unhandledTag();
	bool isMissingTag();
	bool missinAttribute();
	bool isValidMAPTag(string mapTag);
	bool isValidSRTTag(string mapTag);
	bool isMapTag(string tag);
	bool isSTRTag(string tag);
	bool check();
};

