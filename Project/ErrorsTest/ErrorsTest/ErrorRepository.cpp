#include "ErrorRepository.h"
#include<iostream>
#include<fstream>
#include<string>
LinkedList<Error>* ErrorRepository::read()
{
	ifstream file;
	LinkedList<Error>* result = new LinkedList<Error>();
	std::string message;
	int code; 
	Error*  temp = nullptr;
	char buffer[200];
	file.open("errors.txt");
	if (!file)
	{
		cout << "Error: file could not be opened" << endl;
		exit(1);
	}
	String msg = "message";
	while (!file.eof())
	{
		temp = new Error();
		file.getline(buffer, 200);
		temp->setCode(atoi(buffer));
		file.getline(buffer, 200);
		msg = buffer;
		temp->setMessage(msg);
		result->addEnd(*temp);
	}
	file.close();
	return result;
}

string ErrorRepository::getScript() 
{
	IMLRepository il;
	this->script = il.getScript();
	return this->script;
}

void ErrorRepository::printByCode(int code)
{
	for (size_t i = 0; i < read()->Size(); ++i)
	{
		if (read()->getElementAt(i).getCode() == code)
		{
			std::cout << "Error: ";
			std::cout << read()->getElementAt(i) << std::endl;
			break;
		}	
	}
}

Error& ErrorRepository::getByCode(int code)
{
	for (size_t i = 0; i < read()->Size(); ++i)
	{
		if (read()->getElementAt(i).getCode() == code)
		{
			std::cout << "Error: ";
			return read()->getElementAt(i);
		}
	}
}

int ErrorRepository::countOpenSymbol()
{
	int counter = 0;
	int i = 0;
	while (this->getScript()[i] != '\0')
	{
		if (this->getScript()[i] == '<')
		{
			counter++;
		}
		i++;
	}
	return counter;
}

int ErrorRepository::countCloseSymbol()
{
	int counter = 0;
	int i = 0;

	while (this->getScript()[i] != '\0')
	{
		if (this->getScript()[i] == '>')
		{
			counter++;
		}
		i++;
	}
	return counter;
}

LinkedList<string>& ErrorRepository::splitString()
{
	//<SRT-ORD "ASC">8 1 3<MAP-INC "1">4 12 55<AGG-AVG>4 8</AGG-AVG></MAP-INC>22</SRT-ORD>
	LinkedList<string>* tags = new LinkedList<string>();
	if (hasEnoughOpenCloseSymbols())
	{
		return *tags;
	}
	else
	{
		if (countCloseSymbol() > countOpenSymbol())
		{
			printByCode(101);
			exit(2);
		}
		else
		{
			printByCode(104);
			exit(2);

		}
	}
	
}

bool ErrorRepository::isDigit(char symbol)
{
	return (symbol >= '0' && symbol <= '9');
}

bool ErrorRepository::hasEnoughOpenCloseSymbols()
{
	return (countCloseSymbol() == countOpenSymbol());
}
