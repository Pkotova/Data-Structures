#pragma once
#include "String.h"
class IMLRepository
{
private:
	String script;
	char file[30];
public:
	void setFile(const char file[30]);
	void setScript(String script);
	string getScript();
};

