#include "MAPTag.h"
#include "ErrorRepository.h"
ErrorRepository er; 
MAPTag::MAPTag() : Tag("MAP")
{
	this->setAttribute('5');
}

MAPTag::MAPTag(char _attribute) : Tag("MAP")
{
	this->setAttribute(_attribute);
}

void MAPTag::setAttribute(char _attribute)
{
	if (er.isDigit(_attribute))
	{
		this->attribute = _attribute;
	}
	else
	{
		std::cout << er.getByCode(110);
		std::cout<< "Attribute: " << _attribute << " Not correct!";
		exit(1);
	}
}

void MAPTag::setName(String* _name)
{
	
	this->name = *_name;
}

void MAPTag::setContent(Vector<double>* _content)
{
	this->content = *_content;
}

String MAPTag::getName()
{
	return this->name;
}

Vector<double>* MAPTag::getContent()
{
	return &this->content;
}

std::ostream& operator<<(std::ostream& out, MAPTag& _current)
{
	out <<"<"<< _current.name <<" \""<< _current.attribute<< " \">" << _current.content;
	return out;
}
