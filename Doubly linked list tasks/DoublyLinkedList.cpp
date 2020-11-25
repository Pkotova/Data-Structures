#include <iostream>
// дефинираме темплейтна структура двойно свързан списък
template<class T>
struct DLLNode
{
	T data;				// елемент
	DLLNode<T>* next;	// указател към следващия елемент
	DLLNode<T>* prev;   // указател към предишния елемент

	DLLNode(const T& _data, DLLNode<T>* _next, DLLNode<T>* _prev) // кутийката, конструктор
	{
		data = _data;
		next = _next;
		prev = _prev;
	}
};

// добавяне на елемент 
template<class T>
void push_back(DLLNode<T>*& first, const T& elem) //
{
// трябва да проверим нали node не е празен
	if (first == nullptr)
	{
		first = new DLLNode<T>(elem, nullptr, nullptr);
		return;
	}
// ако не е празен - създаваме нов ноуд, който да ни бъде първи 
	DLLNode<T>* current = first;
// изместваме всички елементи 
	while (current->next != nullptr)
	{
		current = current->next;
	}
// накрая добавяме новият емемент накрая на списъка
	current->next = new DLLNode<T>(elem, nullptr, current);
}

//премахваме последния елемент
template<class T>
void removeLast(DLLNode<T>*& first) // указател към референция
{
// приемаме първия елемент, защото трябва да знаем откъде почва
	if (first == nullptr)
	{
		return;
	}

	DLLNode<T>* current = first;
// обхождаме листа, докато не стигнем до последния елемент
	while (current->next != nullptr)
	{
		current = current->next;
	}
// насочваме указателя на последния елемент, към указателя на предпоследния елемент
	current->prev->next = nullptr;
// current = последния елемент и го изтриваме 
	delete current;
}

// изтриване на елемент от дадена позиция
template<class T>
void removeAtPosition(DLLNode<T>*& first, int position)
{
// ако първия ни елемент е празен или позицията е <1, прекратяваме
	if (first == nullptr || position < 1)
	{
		return;
	}
// ако не, създаваме нов node, който да ни последява всички елементи от листа
	DLLNode<T>* current = first;
	DLLNode<T>* temp;
// ако листа има само един елемент, тоест prevous е празен, next e празен и position e = 1
	if (current->prev == nullptr && current->next == nullptr && position == 1) // only one elem
	{
// изтриваме current, защото няма да ни трябва,
// nullptr На първия елемент (махаме го)
		delete current;
		first = nullptr;
		return;
	}
// обхождаме листа, докато position > 1 и съществува следващ елемент
	while (position > 1 && current->next)
	{
		current = current->next;
		--position;
	}
// ако следващия елемент не съществува и позицията е > 1 - то тогава няма такъв елемент
	if (current->next == nullptr && position > 1) 
	{
		return;
	}
// иначе, ако предишния е празен
	else if (current->prev == nullptr)
	{
		temp = current; // запазвам стойността на current
		current->next->prev = nullptr; // пренасочвам указателя на последния към предпоследния елемент
		current = current->next; // текущия елемент го пренасочваме към следващия
		first = current; // текущия елемент става първи
		delete temp; // изтриваме temp ????
		return;
	}
	else if (current->next == nullptr) //aко текущият елемент е последен
	{ 
		current->prev->next = nullptr;//пренасочваме указателя на предпоследния елемент, към последния елемент
		delete current; // изтриваме рекущия елемент
		return;
	}
	else
	{
		temp = current;
		current->next->prev = current->prev;
		current->prev->next = current->next;
		current = current->next;
		delete temp;
		return;
	}
}

// ЗАДАЧИ
/*
	Да се дефинира функция int count(dllnode<T>* l,int x), 
	която преброява колко пъти елементът x се среща в 
	списъка с първи елемент l.
*/
template<class T>
int count(DLLNode<T>* list, int element) 
{
	size_t br = 0;
// докато не сме стигнали края на листа
	while (list != nullptr)
	{
// да проверяваме колко елемента са равни на подадения 
		if (list->data == elem)
		{
			++br;
		}
// Обхождане на листа - преминаваме на следващия елемент
		list = list->next;
	}

	return br;
}

/*
	Функция dllnode<int>* range (int x, int y) която създава и връща
	първия елемент на списък с елементи x, x + 1, ..., y, при положение, че
	x ≤ y.
*/
DLLNode<int>* range(int x, int y) // 16.2
{
// създаваме първия елемент, който е равен на х+1 и няма предишен и следващ
	DLLNode<int>* first = new DLLNode<int>(x++, nullptr, nullptr);
// създаваме указател, който ще обхожда листа
	DLLNode<int>* current = first;
// докато x<=y (тъй като увеличаваме x на всяка итерация, трябва да го правим
// докато x не е по-малко или равно на y
	while (x <= y)
	{
// текущия елемент current има указател към следващия елемент
// той е сочи към НОВ елемент, който ние създаваме
		current->next = new DLLNode<int>(x, nullptr, current);
// текущия елемент минава към следващия елемент
		current = current->next;
// увеличаваме x + 1;
		++x;
	}

	return first;
}

/*
	Да се дефинира функция removeAll (dllnode<T>*& l,const T& x), 
	която изтрива всички срещания на елемента x от списъка l
*/
template<class T>
void removeAll(DLLNode<T>*& first, const T& elem) 
{
// проверяваме дали нашият лист не е празен
	if (first == nullptr)
	{
		return;
	}
// ако не е празен, създаваме елемент, който ще ни помага да обхождаме другите елементи
	DLLNode<T>* current = first;
	size_t iterator = 0; // следи ни всяка позиция
// докато листът не е празен
	while (current != nullptr)
	{
// проверяваме дали всеки текущ елемент е равен на подадения
		if (current->data == elem)
		{
// и го изтриваме като подаваме елемента и на коя позиция се намира
			removeAtPosition(first, br);
		}
// минаваме на следващия елемент
		current = current->next;
// като увеличаваме и позицията на която се намираме
		++iterator;
	}
}

/*
	Да се дефинира функция void append(dllnode*<T>& l1, dllnode<T>*
	l2), която добавя към края на списъка l1 всички елементи на списъка
	l2.
*/
template<class T>
void append(DLLNode<T>*& list1, DLLNode<T>* list2) 
{
//елемент, който ще ни помага да обхождаме лист1 
	DLLNode<T>* current = list1;
// докато достигнем края на листа
	while (current->next != nullptr)
	{
// обхождаме го докато не хванем последния елемент
		current = current->next;
	}
// започваме да обхождаме лист 2, докато той не е празен
	while (list2 != nullptr)
	{
// в първата итерация current пази последния елемент на list1, съответно
// пренасочваме current->next да сочи към нов node, който съдържа първия елемент на 
// list 2, next = null ptr, тоест ние не знаем какъв е, след a prevous e текущия елемент
		current->next = new DLLNode<T>(list2->data, nullptr, current);
// current минава на следващия елемент
		current = current->next;
// a това вече пази втория елемент на list 2
		list2 = list2->next;
	}
}

/*
	 Да се дефинира функция dllnode* concat(dllnode<T>* l1, dllnode<T>*
	l2), който съединява два списъка в нов, трети списък. Т.е. concat(l1, l2)
	създава и връща нов списък от елементите на l1, следвани от елементите
	на l2.
*/
template<class T>
DLLNode<T>* concat(DLLNode<T>* list1, DLLNode<T>* list2) // 16.5
{
// приемаме два листа и трябва да ги съберем в трети, result ще бъде третия лист
	DLLNode<T>* result = new DLLNode<T>(list1->data, nullptr, nullptr);
	list1 = list1->next;
	DLLNode<T>* current = result;
// докато първия лист не е празен
	while (list1 != nullptr)
	{
// следващия елемент е равен на нов елемент, който е със стойност първия елемент
// на лист едно
// и малко си загубих логиката, ама е аналогично 
		current->next = new DLLNode<T>(list1->data, nullptr, current);
		current = current->next;
		list1 = list1->next;
	}
// правим абсолютно същото за list 2
	while (list2 != nullptr)
	{
		current->next = new DLLNode<T>(list2->data, nullptr, current);
		current = current->next;
		list2 = list2->next;
	}
// накрая просто връщаме резултатния списък 
// абе все едно долепяш два масива, приемрно нз май е така
	return result;
}

/*
	 Да се дефинира функция reverse, която обръща реда на елементите
	на списък. Например, списъкът с елементи 1, 2, 3 ще се преобразува до
	списъка с елементи 3, 2, 1.
*/
template<class T>
void reverse(DLLNode<T>*& first)
{
// абсолютно аналогично на reverse-ването на масив
	DLLNode<T>* current = first;
	DLLNode<T>* temp = nullptr;

	while (current != nullptr)
	{
//swap на указатели, тук не е нужно да се разместват целите кутийки
// а само пренасочваме указателя

		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	first = temp->prev;
}

/*
	Да се напише функция void removeduplicates(dllnode*& l), която
	изтрива всички дублиращи се елементи от списъка l
*/

//реализираме помощна функция, която ни казва дали два елемента са дубликати
template<class T>
bool isDuplicate(DLLNode<T>* first, T elem)
{
// ако има само един елемент, то той няма как да има дубликат
	if (first == nullptr)
	{
		return false;
	}
// помощен указател, който ще ни помага
// с обхождането на листа
	DLLNode<T>* current = first;
// ще броим дубликатите
	int br = 0;
// докато листа не е празен
	while (current != nullptr)
	{
// проверяваме дали текущия елемент не е равен на подадения
		if (current->data == elem)
		{
// aко е дубликат увеличаваме брояча
			++br;
		}
// след това минаваме на следващия елемент
		current = current->next;
	}

	return br != 1;
}
// реалната функция от задачата
template<class T>
void removeDuplicates(DLLNode<T>*& first) 
{
// проверка за празен лист
	if (first == nullptr)
	{
		return;
	}
// помага да обикаляме 
	DLLNode<T>* current = first;
	DLLNode<T>* temp;
	current = current->next;
// трябва да имаме поне два елемента
	int br = 2;

	while (current != nullptr)
	{
		if (isDuplicate(first, current->data))
		{
			if (current->next != nullptr)
			{
				temp = current;
				current->next->prev = current->prev;
				current->prev->next = current->next;
				current = current->next;
				delete temp;
			}
			else
			{
				temp = current;
				current->prev->next = nullptr;
				current = current->prev;
				delete temp;
			}
		}

		current = current->next;
		++br;
	}
}

int main()
{
   
}

