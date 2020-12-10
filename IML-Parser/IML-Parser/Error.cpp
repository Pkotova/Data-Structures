#include "Error.h"

void Error::setCode(int _code)
{
	this->code = _code;
}

void Error::setMessage(std::string& _message)
{
	this->message = _message;
}

int Error::getCode()
{
	return this->code;
}

std::string& Error::getMessage()
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
	is >> e.message;
	return is;
}

