#pragma once
#include <iostream>
#include <string>

class Error
{
private:
	int code;
	std::string message;
public:

	void setCode(int _code);
	void setMessage(std::string& _message);

	int getCode();
	std::string& getMessage();
	void printError() const;

	friend std::ostream& operator<< (std::ostream& os, const Error& e);
	friend std::istream& operator>> (std::istream& is, Error& e);
};


