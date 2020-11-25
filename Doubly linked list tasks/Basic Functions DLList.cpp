#include <iostream>
template<class T>
struct Node
{
	T data;
	Node* next;
	Node* prev;

	Node(T data, Node* next = nullptr, Node* prev = nullptr)
	{
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
};

// добавяне на елементи в началото на списъка
template<class T>
void push_front(Node<T>*& first, T data)
{
	Node<T>* newNode = new Node<T>(data); // Създаваме си нов възел с подадената стойност
// създали сме нова кутийка която има data, указател към предишния 
// указател към следващия елемент
	if (first != nullptr)
	{
// пренасочваме указателите така че: 
// указателя към следващия елемент да бъде насочен към първия елемент на листа
		newNode->next = first;
// а предишния елемент на първия елемент да бъде новия елемент
		first->prev = newNode;
	}
// присвояваме стойността
	first = newNode;
}

// добавяне на елементи в края на списъка
template<class T>
void push_back(Node<T>*& first, T data)
{
	Node<T>* newNode = new Node<T>(data); // Създаваме си нов възел с подадената стойност

	if (first == nullptr) // ако подадения лист е празен
	{
		first = newNode; // да добавим новия елемент като първи елемент на списъка
	}
	else
	{
		// иначе създаваме нов указател, който да ни помага да обхождаме листа
		Node<T>* current = first;
		// докато не сме стигнали края на листа го обхождаме
		while (current->next != nullptr) // Стигаме до последния елемент от списъка
		{
			current = current->next;
		}
		// след като излезем от цикъла ние вече сме достигнали последния елемент 
		// и в current пазим последния елемент
		// след това просто пренасочваме указателите
		current->next = newNode; 
		newNode->prev = current;
	}
}

// Добавяне на елемент преди конкретен елемент, подаден по неговата стойност
template<class T>
void push_before_certain(Node<T>*& first, T newData, T data)
{
// проверяваме дали подадения лист не е празен
	if (first == nullptr)
	{
		return;
	}
// ако не е празен, създаваме нов възел, който има стойност новата стойност, която искаме да добавим
	Node<T>* newNode = new Node(newData);
	Node<T>* current = first;

	while (current != nullptr && current->data != data) // Стигаме до елемента, преди който искаме да добавим
	{
		current = current->next;
	}

	if (current->prev == nullptr) // Ако искаме да добавим елемент в началото на списъка
	{
		newNode->next = current;
		current->prev = newNode;
		first = newNode;
	}
	else
	{
		newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;
	}
}

//изтриване на първи елемент
template<class T>
void pop_first(Node<T>*& first)
{
	// проверяваме дали листа не е празен
	if (first == nullptr)
	{
		return;
	}
	// ако не е празен, запазваме указателя между първи и втори елемент
	Node<T>* save = first->next;
	// изтриваме първия
	delete first;
	// и първия става равен на новия
	first = save;
}

// изтриване на последния елемент от листа
template<class T>
void pop_last(Node<T>*& first)
{
	// проверяваме дали листа не е празен
	if (first == nullptr)
	{
		return;
	}
	// aко не е празен създаваме помощен указател, който да ни помага 
	// да обхождаме листа
	Node<T>* current = first;
	// докато не достигнем последния елемент
	while (current != nullptr)
	{
		current = current->next;
	}
	//след като сме излезли от цикъла, current = last
	// изтриваме връзката между последния и предпоследния елемент
	current->prev->next = nullptr;
	delete current; // изтриваме съдържанието на последния елемент
}

// изтриване на елемент по дадена стойност
template<class T>
void pop_by_value(Node<T>*& first, T value)
{
	if (first == nullptr) // ако листа е празен
	{
		return 
	}
	// ако не е празен, си създаваме нов указател, който
	// да ни помага да обхождаме листа
	Node<T>* current = first;
	while (current != nullptr && current->data != data) 
		// Стигаме до елемента, който искаме да изтрием
	{
		current = current->next;
	}
	if (current->prev == nullptr) 
		// Ако трябва да изтрием първия елемент от списъка, т.е. няма предишен
	{
		current->next->prev = nullptr;
		first = current->next;
	}
	else if (current->next == nullptr) 
		// Ако трябва да изтрием последния елемент от списъка, т.e пак няма следващ 
	{
		current->prev->next = nullptr;
	}
	else 
		// Ако трябва да изтрием елемент по средата на списъка
	{	// пренасочваме указателите
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
}

// изтриване на елемент по подадена позиция
template<class T>
void pop_by_position(Node<T>*& first, int position)
{
	if (first==nullptr)
	{
		return // проверяваме дали листа, който ни е подаден е празен;
	}
	// ако не е празен си създаваме помощен указател, който ни помага да 
	// обхождаме листа
	Node<T>* current = first;
	for (size_t i = 0; i < position; i++)
	{
		current = current->next; // достигаме до позицията
	}
	if (current->prev = nullptr)
		// ако искаме да изтрием първия елемент;
	{
		current->next->prev = nullptr;
		first = current->next;
	}
	else if (current->next = nullptr) // ако искаме да изтрием последния
	{
		current->prev->next = nullptr;
	}
	else
	{
		// неформално казано - разкачаме указателите;
		current->prev->next = nullptr;
		current->next->prev = nullptr;
	}
	delete current; // накрая просто изтриваме съдържанието на елемента
}
template<class T>
void print(Node<T>*& first)
{ // Указател, който ни помага да обхождаме
	Node<T>* current = first;
	while (current != nullptr)
	{
// извеждаме съдържанието на текущия,
		std::cout << current->data << " ";
// после преместваме текущия към следващия
		current = current->next;
	}
	std::cout << "\n";
}
int main()
{
  
}
