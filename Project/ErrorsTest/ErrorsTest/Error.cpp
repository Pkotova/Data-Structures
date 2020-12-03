#include "Error.h"
#include <string>  
static int sNextId = 100;
double Error::generateNextCode()
{
	return sNextId += 0.1;
}

void Error::setCode(int _code)
{
	this->code = _code;
}

void Error::setMessage(String& message)
{
	this->message = message;
}

Error::Error()
{
	this->code = 111;
	this->message = ":Default Error!";
}

int Error::getCode()
{
	return this->code;
}

String& Error::getMessage()
{
	return this->message;
}

void Error::printError() const
{
	std::cout << this->code;
	std::cout << this->message << std::endl;
}
std::ostream& operator<< (std::ostream& os, const Error& s)
{
	os << s.code << s.message << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Error& e)
{
	is >> e.code;
	is>>e.message;
	return is;
}