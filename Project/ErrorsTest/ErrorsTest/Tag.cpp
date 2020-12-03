#include "Tag.h"
#include"ErrorRepository.h"
Tag::Tag()
{
	name = "<default tag>";
	content.push_back(0);
}
Tag::Tag(String _name)
{
	this->setName(&_name);
	content.push_back(0);
}
Tag::Tag(String _name, Vector<double> _content)
{
	this->setName(&_name);
	this->setContent(&_content);
}

void Tag::setName(String* _name)
{
	this->name = *_name;
}

void Tag::setContent(Vector<double>* _content)
{
	this->content = *_content;
}

String Tag::getName()
{
	return this->name;
}

Vector<double>* Tag::getContent()
{
	return &this->content;
}

