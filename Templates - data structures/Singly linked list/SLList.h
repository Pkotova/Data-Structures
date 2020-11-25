#pragma once
#pragma once

//имплементация на едносвързан списък

class SLList
{
private:
	struct Node
	{
		int data;
		Node* next;

		Node(const int& data, Node* next = nullptr)
		{
			this->data = data;
			this->next = next;
		}
	};

	Node* first;
	//size_t size; - когато ни интересува броя на възлите в списъка

	void copy(const SLList&);

	void clear();

public:
	SLList();

	SLList(const SLList&);

	SLList& operator=(const SLList&);

	~SLList();
};
