#include <iostream>

template<class T>
struct DLLNode
{
	T data;
	DLLNode<T>* next;
	DLLNode<T>* prev;

	DLLNode(const T& _data, DLLNode<T>* _next, DLLNode<T>* _prev)
	{
		data = _data;
		next = _next;
		prev = _prev;
	}
};
template<class T>
void print(DLLNode<T>* list)
{
	while (list != nullptr)
	{
		std::cout << list->data << " ";
		list = list->next;
	}
}

template<class T>
void push_back(DLLNode<T>*& first, const T& elem)
{

	if (first == nullptr)
	{
		first = new DLLNode<T>(elem, nullptr, nullptr);
		return;
	}

	DLLNode<T>* current = first;

	while (current->next != nullptr)
	{
		current = current->next;
	}

	current->next = new DLLNode<T>(elem, nullptr, current);
}
/*

    Чрез директно използване на възлите на двусвързан списък:
    -напишете функция, която обединява два списъка като поставя между тях #

	Пример: T->H->I->N->K      S->M->I->L->E
	Решение: T->H->I->N->K->#->S->M->I->L->E
*/
template<class T>
void mergeList(DLLNode<T>*& firstList, DLLNode<T>*& secondList)
{
// текущия елемент е равен на първия елемент на първия лист
	DLLNode<T>* cur = firstList;
// искаме да добавим нов node, който е да е #

	DLLNode<char>* newNode = new DLLNode<char>('#', nullptr, nullptr);
// докато първия лист не е празен
	while (cur->next != nullptr)
	{
// намираме последния елемент на първия лист
		cur = cur->next;
	}
// след това добавяме # след последния елемент на първия лист
	cur->next = newNode;
// текущия елемент вече е #
	newNode->prev = cur;
// следващия елемент след # вече е първия елемент на втория лист 
	newNode->next = secondList;

	secondList->prev = newNode;
	secondList = nullptr;
}

/*
	Чрез директно използване на възлите на двусвързан списък, 
	при последователно повторение на три елемента в списъка, 
	премахнете първия от поредицата повтарящи се.
*/
template<class T>
void removeFirst(DLLNode<T>*& first) 
{
	if (first == nullptr)
	{
		return;
	}
	DLLNode<T>* cur = first;
	int count = 0;

	while (cur->next != nullptr)
	{
		if (cur->next->data == cur->data)
		{
			++count;
			if (count == 2)
			{
				DLLNode<T>* removeNode = new DLLNode<T>(cur->prev->data,nullptr,nullptr);
				cur->prev->prev->next = cur;
				cur->prev = cur->prev->prev;

				delete removeNode;
				count = 0;
				continue;
			}
		}
		cur = cur->next;
	}
}


int main()
{
	DLLNode<char>* ddlist = nullptr;

	push_back(ddlist, '6');
	push_back(ddlist, '1');
	push_back(ddlist, '1');
	push_back(ddlist, '1');
	push_back(ddlist, '9');

	removeFirst(ddlist);
	print(ddlist);
}


