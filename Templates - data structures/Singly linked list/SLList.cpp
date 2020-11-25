#include "SLList.h"

void SLList::copy(const SLList& rhs)
{
	//Node* newBox = new Node(rhs.first->data);
	//this->first = newBox;
	this->first = new Node(rhs.first->data);

	Node* copy = rhs.first; //указател, който ще итерира по списъка rhs
	Node* cur = this->first; //указател, който ще итерира по текущия списък (this)

	//Node* tempBox = nullptr;
	while (copy->next != nullptr)
	{
		//tempBox = new Node(copy->next->data);
		//cur->next = tempBox;
		cur->next = new Node(copy->next->data);
		copy = copy->next;
		cur = cur->next;
	}

}
void SLList::clear()
{
	Node* temp = nullptr;
	while (first != nullptr)
	{
		temp = new Node(first->data);
		first = first->next;
		delete temp;
	}
	this->first = nullptr;
}

SLList::SLList()
{
	this->first = nullptr;
}

SLList::SLList(const SLList& rhs)
{
	this->copy(rhs);
}

SLList& SLList::operator=(const SLList& rhs)
{
	if (this != &rhs)
	{
		this->clear();
		this->copy(rhs);
	}

	return *this;
}

SLList::~SLList()
{
	this->clear();
}