// ErrorsTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ErrorRepository.h"
#include"MAPTag.h"
#include "IMLRepository.h"

int main()
{	
	ErrorRepository il;

	//std::cout << il.getScript() << std::endl;
	std::cout << il.cleanScript() << std::endl;
	//std::cout << il.numericParameters()<<std::endl;
	
	
}
