// ErrorsTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ErrorRepository.h"
#include"MAPTag.h"
#include "IMLRepository.h"

int main()
{	
	ErrorRepository il;
	//std::cout << il.removeSpaces();
	//std::cout << il.isValidSRTTag("SRT-ORD\"ASC\"");
	std::cout << il.missinAttribute();

	
}
