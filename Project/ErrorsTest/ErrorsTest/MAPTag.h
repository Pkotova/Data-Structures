#pragma once
#include"Tag.h";
#include "String.h"
class MAPTag :  private Tag
{
private:
	char attribute;
public:
	MAPTag();
	MAPTag(char _attribute);
	
	void setAttribute(char _attribute);
	char getAttrubute();
	double getN(); // attribute to double!

	void setName(String* _name);
	void setContent(Vector<double>* _content);

	String getName();
	Vector<double>* getContent();
    friend std::ostream& operator<<(std::ostream& out, MAPTag& _current);
};

