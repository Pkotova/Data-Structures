#pragma once
#include <string>
#include<iostream>
using namespace std;
class IMLRepository
{
private:
	string script;
	string  file;
public:
	void setFile(string filename);
	string getFile()const;
	void setScript(string script);
	string getScript();
	string getOriginalScript();
};

