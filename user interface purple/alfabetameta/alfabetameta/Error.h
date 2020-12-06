#pragma once
#include<string>
#include<iostream>
using namespace std;
class Error
{
private:
	int code;
	string message;
	double generateNextCode();
public:
	Error();
	int getCode();
	string& getMessage();
	void printError()const;
	void setCode(int _code);
	void setMessage(string& message);
	friend std::ostream& operator<< (std::ostream& os, const Error& e);
	friend std::istream& operator>> (std::istream& is, Error& e);
};

