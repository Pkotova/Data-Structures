#include <iostream>
#include <string>
#include"Tree.h"
#include"ErrorRepository.h"

int main()
{
	// MAP + 1 на всички елементи от списъка; AGG събира всички елементи от списък; SRT преобръща списъка
	ErrorRepository er;
	std::string testCase = er.cleanScript();
	//std::string testCase = "<SRT-ORD \"ASC\">81 3<MAP-INC \"1\">4 12 55<AGG-AVG>4 8</AGG-AVG></MAP-INC>22</SRT-ORD>";
	std::string id = "";
	size_t index = 0;
	Tree* tree = nullptr;
	tree = makeTree(tree, testCase, index, id);

	reverseTree(tree);
	printTree(tree);
	std::cout << "\n\n";

	std::cout << "Result: ";
	printResult(returnTreeResult(tree, tree, testCase));
	std::cout << "\n";

	return 0;
	
}

