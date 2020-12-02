#pragma once
#include"Error.h"
#include"LinkedList.h"
#include "String.h"
class ErrorRepository
{
private: 
	String file;
public:
	LinkedList<Error>* read();
	void printByCode(int code);
};

