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
	String meage = "message";
	while (!file.eof())
	{
		temp = new Error();
		file.getline(buffer, 200);
		temp->setCode(atoi(buffer));
		file.getline(buffer, 200);
		meage = buffer;
		temp->setMessage(meage);
		result->addEnd(*temp);
	}
	file.close();
	return result;
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
