#pragma once
#include"String.h"
class Error
{
private:
	int code;
	String message;
	double generateNextCode();
public:
	Error();
	int getCode();
	String& getMessage();
	void printError()const;
	void setCode(int _code);
	void setMessage(String& message);
	friend std::ostream& operator<< (std::ostream& os, const Error& e);
	friend std::istream& operator>> (std::istream& is, Error& e);
};

