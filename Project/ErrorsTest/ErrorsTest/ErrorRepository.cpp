#include "ErrorRepository.h"
#include<iostream>
#include<fstream>
#include<string>
#include <regex>
#include <sstream>
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
	this->script = il.getScript(); // RETURN SCRIPT IN ONE LINE
	return this->script;
}

void ErrorRepository::printByCode(int code)
{
	for (size_t i = 0; i < read()->Size(); ++i)
	{
		if (read()->getElementAt(i).getCode() == code)
		{
			//system("Color 04");
			std::cout << "Error: ";
			std::cout << read()->getElementAt(i);
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

string ErrorRepository::removeSpaces()
{
	string removeSpaces = getScript();
	removeSpaces.erase(remove(removeSpaces.begin(), removeSpaces.end(), ' '), removeSpaces.end());
	return removeSpaces;
}

LinkedList<string>& ErrorRepository::splitString()
{
	LinkedList<string>* tags = new LinkedList<string>();
	std::string script = getScript();
	int i = 0;
	if (hasEnoughOpenCloseSymbols())
	{
		std::regex words_regex("[^\\s<>\":;!?]+");
		auto words_begin = std::sregex_iterator(script.begin(), script.end(), words_regex);
		auto words_end = std::sregex_iterator();

		for (std::sregex_iterator i = words_begin; i != words_end; ++i)
			tags->addEnd((*i).str());// << '\n';
		return *tags;
	}
	else
	{
		if (countCloseSymbol() > countOpenSymbol())
		{
			printByCode(101);
			exit(101);
		}
		else
		{
			printByCode(104);
			exit(104);

		}
	}
	
}

LinkedList<string>& ErrorRepository::halfSplit()
{

	LinkedList<string>* tags = new LinkedList<string>();
	std::string script = removeSpaces();
	int i = 0;
	if (hasEnoughOpenCloseSymbols())
	{
		std::regex words_regex("[^\<>:;!?]+");
		auto words_begin = std::sregex_iterator(script.begin(), script.end(), words_regex);
		auto words_end = std::sregex_iterator();

		for (std::sregex_iterator i = words_begin; i != words_end; ++i)
			tags->addEnd((*i).str());// << '\n';
		return *tags;
	}
	else
	{
		if (countCloseSymbol() > countOpenSymbol())
		{
			printByCode(101);
			exit(101);
		}
		else
		{
			printByCode(104);
			exit(104);

		}
	}

}

bool ErrorRepository::isDigit(char symbol)
{
	return (symbol >= '0' && symbol <= '9');
}

bool ErrorRepository::isDigit(string symbol)
{
	auto result = double();
	auto i = std::istringstream(symbol);

	i >> result;

	return !i.fail() && i.eof();
}

bool ErrorRepository::hasEnoughOpenCloseSymbols()
{
	return (countCloseSymbol() == countOpenSymbol());
}

bool ErrorRepository::unhandledTag()
{
	bool result = true;
	LinkedList<string> info = splitString();

	int size = info.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (info.getElementAt(i) == "MAP-INC" ||
			info.getElementAt(i) == "MAP-MLT" ||
			info.getElementAt(i) == "AGG-SUM" ||
			info.getElementAt(i) == "AGG-PRO" ||
			info.getElementAt(i) == "AGG-AVG" ||
			info.getElementAt(i) == "AGG-FST" ||
			info.getElementAt(i) == "AGG-LST" ||
			info.getElementAt(i) == "SRT-REV" ||
			info.getElementAt(i) == "SRT-ORD" ||
			info.getElementAt(i) == "SRT-SLC" ||
			info.getElementAt(i) == "SRT-DST" ||
			info.getElementAt(i) == "/MAP-INC" ||
			info.getElementAt(i) == "/MAP-MLT" ||
			info.getElementAt(i) == "/AGG-SUM" ||
			info.getElementAt(i) == "/AGG-PRO" ||
			info.getElementAt(i) == "/AGG-AVG" ||
			info.getElementAt(i) == "/AGG-FST" ||
			info.getElementAt(i) == "/AGG-LST" ||
			info.getElementAt(i) == "/SRT-REV" ||
			info.getElementAt(i) == "/SRT-ORD" ||
			info.getElementAt(i) == "/SRT-SLC" ||
			info.getElementAt(i) == "/SRT-DST" ||
			info.getElementAt(i) == "ASC"	   ||
			info.getElementAt(i) == "DSC"	   ||
			isDigit(info.getElementAt(i)))
		{
			
		}
		else
		{
			std::cout << info.getElementAt(i) << ": ";
			printByCode(103);
			exit(103);
		}
	}
}

bool ErrorRepository::isMissingTag()
{
	LinkedList<string> info = splitString();
	int countTags = 0;
	int countSlash = 0;
	int size = info.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (!isDigit(info.getElementAt(i)) && 
			info.getElementAt(i) != "ASC" &&
			info.getElementAt(i) != "DSC")
		{
			countTags++;
		}
		if (info.getElementAt(i)[0] == '/')
		{
			countSlash++;
		}
	}
	if (countTags / 2 == countSlash)
	{
		//return true;
	}
	else if (countTags / 2 > countSlash)
	{
		//missing closing
		printByCode(102);
		exit(102);
	}
	else
	{
		//missing opening
		printByCode(100);
		exit(100);
	}
	
}

bool ErrorRepository::missinAttribute() //TODO
{
	
	LinkedList<string> info = halfSplit();
	LinkedList<string> sc = splitString();
	//info.print();
	//sc.print();
	int size = info.Size();
	for (size_t i = 0; i < size; i++)
	{
		if ((isMapTag(sc.getElementAt(i)) && !isValidMAPTag(info.getElementAt(i))))
		{
			if (!unhandledTag())
			{
				std::cout << info.getElementAt(i) << " ";
				printByCode(120);
				std::cout << " or ";
				printByCode(105);
				exit(105);
			}
		}
		else if ((isSTRTag(sc.getElementAt(i)) && !isValidSRTTag(info.getElementAt(i))))
		{
			std::cout << info.getElementAt(i) << " ";
			printByCode(120);
			std::cout << " or ";
			printByCode(105);
			exit(105);
		}

	}
	return true;
}

bool ErrorRepository::isValidMAPTag(string mapTag)
{
	regex inc("(MAP-INC)((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	regex mlt("(MAP-MLT)((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	if (regex_match(mapTag, inc) || regex_match(mapTag, mlt))
		return true;
	return false;
}

bool ErrorRepository::isValidSRTTag(string mapTag)
{
//	std::cout << mapTag << std::endl;
	regex asc("(SRT-ORD)(\")(ASC)(\")");
	regex dsc("(SRT-ORD)(\")(DSC)(\")");
	regex slc("(SRT-SLC)((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	if (regex_match(mapTag, asc) || 
		regex_match(mapTag, dsc) || 
		regex_match(mapTag, slc))
		return true;
	return false;
}

bool ErrorRepository::isMapTag(string tag)
{
	return tag == "MAP-INC" || tag == "MAP-MLT";
}

bool ErrorRepository::isSTRTag(string tag)
{
	 return tag == "SRT-REV" || tag == "SRT-ORD" || tag == "SRT-SLC" || tag == "SRT-DST";
}

LinkedList<string>& ErrorRepository::getAllData()
{
	LinkedList<string>* data = new LinkedList<string>();
	LinkedList<string> info = halfSplit();
	int size = info.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (i % 2 != 0 && info.getElementAt(i)[0] != '/')
		{
			data->addEnd(info.getElementAt(i));
		}
	}

	return *data;
}

bool ErrorRepository::numericParameters()
{
	LinkedList<string> parameters = getAllData();
	int size = parameters.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (!isDigit(parameters.getElementAt(i)))
		{
			std::cout << parameters.getElementAt(i) << std::endl;
			printByCode(112);
			exit(122);
			return false;
		}
		
	}

}

bool ErrorRepository::check()
{
	unhandledTag();
	isMissingTag();
	numericParameters();
	missinAttribute();

	return true;
}
string ErrorRepository::cleanScript()
{
	std::string script = getScript();
	if (check())
	{
		return script;
	}
}

