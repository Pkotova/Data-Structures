#include "ErrorRepository.h"
#include <fstream>
IMLRepository il;

ErrorRepository::ErrorRepository()
{
	this->script = il.getScript();
	this->errors = "";
}

LinkedList<Error>* ErrorRepository::errorList()
{
	std::fstream file;
	LinkedList<Error>* result = new LinkedList<Error>();
	std::string message;
	int code = 0;
	Error* temp = nullptr;
	char buffer[200];
	file.open("errors.txt");
	if (!file)
	{
		std::cout << "Error: file could not be opened" << std::endl;
		//exit(1);
	}
	std::string msg = "message";
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

std::string ErrorRepository::returnByCode(int _code)
{
	std::string error;
	for (size_t i = 0; i < errorList()->Size(); ++i)
	{
		if (errorList()->getElementAt(i).getCode() == _code)
		{
			error += std::to_string(errorList()->getElementAt(i).getCode());
			error += errorList()->getElementAt(i).getMessage();
		}
	}
	return error + '\n' ;
}

std::string ErrorRepository::getScript()
{
	
	return this->script;
}

int ErrorRepository::countOpenSymbols()
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

int ErrorRepository::countCloseSymbols()
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

bool ErrorRepository::isValidSRTTag(std::string tag)
{
	std::regex rev("(SRT-REV)");
	std::regex asc("(SRT-ORD)(\")(ASC)(\")");
	std::regex dsc("(SRT-ORD)(\")(DSC)(\")");
	std::regex dst("(SRT-DST)");
	std::regex slc("(SRT-SLC)((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	return  (regex_match(tag, asc) ||
		regex_match(tag, dsc) ||
		regex_match(tag, slc) ||
		regex_match(tag, dst) ||
		regex_match(tag, rev))
		? true :  false;
}

bool ErrorRepository::isValidMAPTag(std::string tag)
{
	std::regex inc("(MAP-INC)((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	std::regex mlt("(MAP-MLT)((\"(-?(\\d)+(\\.)?(\\d)*)\"))");
	return (std::regex_match(tag, inc) || std::regex_match(tag, mlt)) ?  true : false;
}

bool ErrorRepository::missingSymbol()
// is missing = yes if is missing , = false if is not missing
{
	return (countCloseSymbols() == countOpenSymbols()) ? false : true;
}

bool ErrorRepository::isDigit(std::string data)
{
	auto result = double();
	auto i = std::istringstream(data);

	i >> result;

	return !i.fail() && i.eof();
}

bool ErrorRepository::isDigit(char symbol)
{
	return (symbol >= '0' && symbol <= '9');
}

bool ErrorRepository::isSupportedTag(std::string tag)
{
	if (tag == "MAP-INC"  || tag == "MAP-MLT"  ||
		tag == "AGG-SUM"  || tag == "AGG-PRO"  ||
		tag == "AGG-AVG"  || tag == "AGG-FST"  ||
		tag == "AGG-LST"  || tag == "SRT-REV"  ||
		tag == "SRT-ORD"  || tag == "SRT-SLC"  ||
		tag == "SRT-DST"  || tag == "/MAP-INC" ||
		tag == "/MAP-MLT" || tag == "/AGG-SUM" ||
		tag == "/AGG-PRO" || tag == "/AGG-AVG" ||
		tag == "/AGG-FST" || tag == "/AGG-LST" ||
		tag == "/SRT-REV" || tag == "/SRT-ORD" ||
		tag == "/SRT-SLC" || tag == "/SRT-DST" ||
		tag == "ASC"      || tag == "DSC"      ||
		isDigit(tag))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool ErrorRepository::isSyntaxClear() // if all of the code is supported
{
	bool result = true;
	LinkedList<std::string> info = fullSplit();

	size_t size = info.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (isSupportedTag(info.getElementAt(i)) == false)
		{
			std::cout << info.getElementAt(i) << ": ";
			errors += returnByCode(103);
			return false;
		}
	}
	return true;
}

bool ErrorRepository::isMissingTag() // if is missing opening or closing tag returns true, 
// if it has all tags it returns false
{
	LinkedList<std::string> info = fullSplit();
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
	if (countTags / 2 > countSlash)
	{
		//missing closing
		//printByCode(102);
		errors += returnByCode(102);
		//exit(102);
	}
	else if (countTags / 2 < countSlash)
	{
		//missing opening
		//printByCode(100);
		errors += returnByCode(100);
		//exit(100);
	}
	else
	{
		return false;
	}
	return true;
}

bool ErrorRepository::numericParameters()
{
	LinkedList<std::string> parameters = getAllData();

	int size = parameters.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (!isDigit(parameters.getElementAt(i)))
		{
			std::cout << parameters.getElementAt(i) << std::endl;
			errors += returnByCode(122);
			return false;
		}

	}
	return true;
}

bool ErrorRepository::isMissingAttribute() // If is missing return true
{
	LinkedList<std::string> info = halfSplit(); // example for line MAP-INC"-1"
	for (size_t i = 0; i < info.Size(); i++)
		{
			if ((isValidAGGTag(info.getElementAt(i)) == false && isValidMAPTag(info.getElementAt(i)) == false 
				&& isValidSRTTag(info.getElementAt(i)) == false) && (isDigit(info.getElementAt(i)) == false &&
				info.getElementAt(i)[0] != '/'))
			{
				std::cout << info.getElementAt(i) << " ";
				errors += returnByCode(120);
				return true;
			}
		}

	return false;
}

int ErrorRepository::countErrors()
{
	int counter = 0;
	for (size_t i = 0; i < errors.size(); i++)
	{
		if (errors[i] =='\n')
		{
			counter++;
		}
	}
	return counter;
}

std::string ErrorRepository::cleanScript()
{
	std::cout << "****************\n";
	isSyntaxClear();
	isMissingTag();
	numericParameters();
	isMissingAttribute();
	if (errors != "")
	{
		std::cout<< this->errors;
		system("Color 06");
		std::cout << "\033[31m" << "Build: 0 succeeded "<<countErrors()<< " failed" << "\033[0m" << std::endl;
	}
	else
	{
		std::cout << "\033[32m" << "Build: 1 succeeded, 0 failed" << "\033[0m" << std::endl;
		return this->script;
	}
	std::cout << "****************\n\n";
	exit(120);
}

LinkedList<std::string>& ErrorRepository::getAllData()
{
	LinkedList<std::string>* data = new LinkedList<std::string>();
	LinkedList<std::string> info = halfSplit();
	//info.print();

	int size = info.Size();
	for (size_t i = 0; i < size; i++)
	{
		if (isDigit(info.getElementAt(i)[0]))
		{
			data->addEnd(info.getElementAt(i));
		}
	}
	return *data;
}

bool ErrorRepository::isValidAGGTag(std::string tag)
{
	std::regex sum("(AGG-SUM)");
	std::regex pro("(AGG-PRO)");
	std::regex avg("(AGG-AVG)");
	std::regex fst("(AGG-FST)");
	std::regex lst("(AGG-LST)");
	return (std::regex_match(tag, sum) 
		|| std::regex_match(tag, pro)
		|| std::regex_match(tag, avg) 
		|| std::regex_match(tag, fst) 
		|| std::regex_match(tag, lst)) ? true : false;
}

std::string ErrorRepository::clearSpaces()
{
	std::string removeSpaces = getScript();
	removeSpaces.erase(remove(removeSpaces.begin(), removeSpaces.end(), ' '), removeSpaces.end());
	return removeSpaces;
}

LinkedList<std::string>& ErrorRepository::fullSplit()
{
	LinkedList<std::string>* tags = new LinkedList<std::string>();
	std::string script = getScript();
	int i = 0;
	if (!missingSymbol()) // if there is no missing </> symbol
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
		if (countCloseSymbols() > countOpenSymbols())
		{
			errors += returnByCode(101);
			system("Color 06");
			std::cout << returnByCode(101);
			std::cout << "\033[31m" << "Build: 0 succeeded " << countErrors() << " failed" << "\033[0m" << std::endl;
			//exit(101);
		}
		else
		{
			errors += returnByCode(104);
			system("Color 06");
			std::cout << returnByCode(104);
			std::cout << "\033[31m" << "Build: 0 succeeded " << countErrors() << " failed" << "\033[0m" << std::endl;
			//exit(104);
		}
	}
	if (tags->isEmpty())
	{
		exit(120);
	}
}

LinkedList<std::string>& ErrorRepository::halfSplit()
{
	LinkedList<std::string>* tags = new LinkedList<std::string>();
	std::string script = clearSpaces();
	int i = 0;
	if (!missingSymbol())
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
		if (countCloseSymbols() > countOpenSymbols())
		{
			errors += returnByCode(101);
			system("Color 06");
			std::cout << returnByCode(101);
			std::cout << "\033[31m" << "Build: 0 succeeded " << countErrors() << " failed" << "\033[0m" << std::endl;
			//exit(101);
		}
		else
		{
			errors += returnByCode(104);
			system("Color 06");
			std::cout << returnByCode(104);
			std::cout << "\033[31m" << "Build: 0 succeeded " << countErrors() << " failed" << "\033[0m" << std::endl;
			//exit(104);

		}
	}
	if (tags->isEmpty())
	{
		exit(120);
	}
}

