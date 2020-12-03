#pragma once
#include"String.h"
#include"Vector.h"
class Tag
{
protected:
	String name;
	Vector<double> content;
public:
	Tag();
	Tag(String _name);
	Tag(String _name, Vector<double> _content);

	virtual void setName(String* _name);
	virtual void setContent(Vector<double>* _content);

	virtual String getName();
	virtual Vector<double>* getContent();

};

