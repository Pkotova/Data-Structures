#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include"ErrorRepository.h"
class IMLRepository
{
private:
	std::string script;
	std::string file;
	std::string errors; // caught errors

public:
	void setFile(std::string _file);
	std::string& getFile();
	std::string getScript();
	bool check();
};

