#include "TagCalculations.h"
#include "TagCheck.h"
#include "ErrorRepository.h"
#include "IMLRepository.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
struct Tag
{
	std::string tagName;
	std::vector<double> content;
	std::string id;
};

struct Tree
{
	Tag tagNode;
	Tree* left;
	Tree* right;
};

struct Result
{
	std::vector<double> list;
};

void printVector(std::vector<double> content)
{
	while (!content.empty())
	{
		std::cout << content.back() << " ";
		content.pop_back();
	}
}

void printTag(Tag elem)
{
	std::cout << "(Tag name:" << elem.tagName << " Content:";
	printVector(elem.content);
	std::cout << ")";
}

void printTree(Tree* first)
{
	if (first == nullptr)
	{
		return;
	}

	printTag(first->tagNode);

	if (first->left == nullptr && first->right == nullptr)
	{
		return;
	}

	std::cout << "(L:";
	if (first->left == nullptr)
	{
		std::cout << "EMPTY ";
	}

	printTree(first->left);

	std::cout << "R:";
	if (first->right == nullptr)
	{
		std::cout << "EMPTY";
	}

	printTree(first->right);
	std::cout << ")";
}

void printResult(Result* result)
{
	printVector(result->list);
}

Tree* findBiggestPosition(Tree* tree)
{
	if (tree->left == nullptr)
	{
		return tree;
	}

	return findBiggestPosition(tree->left);
}

int numberOfCoppies(Tree* tree, Tree* toMatch)
{
	if (tree == nullptr)
	{
		return 0;
	}

	if (tree->tagNode.tagName == toMatch->tagNode.tagName)
	{
		return 1 + numberOfCoppies(tree->left, toMatch);
	}

	return 0 + numberOfCoppies(tree->left, toMatch);
}

//  "<MAP-MLT \"2\">1 2 3<AGG-SUM>4 5 6</AGG-SUM><SRT-REV>7<AGG-SUM>4 5 6</AGG-SUM>8</SRT-REV></MAP-MLT>"
Tree* makeTree(Tree*& tree, std::string input, int index, std::string identificator)
{
	std::vector<double> currentContent;
	tree = new Tree{ {"", currentContent, identificator}, nullptr, nullptr };

	while (input[index] != '>')
	{
		tree->tagNode.tagName += input[index];

		index++;
	}

	tree->tagNode.tagName += input[index];
	index++;

	//  "<MAP-MLT \"2\">1 2 3<AGG-SUM>4 5 6</AGG-SUM><SRT-REV>7<AGG-SUM>4 5 6</AGG-SUM>8</SRT-REV></MAP-MLT>"
	while (input[index] != '\0')
	{
		if (isdigit(input[index]) == 4 || input[index] == '-')
		{
			std::string number;
			double tempNumber;

			while (input[index] != ' ' && input[index] != '<')
			{
				number += input[index];
				index++;
			}

			tempNumber = atof(number.c_str());
			tree->tagNode.content.push_back(tempNumber);

		}
		if (input[index] == '<')
		{
			if (input[index + 1] == '/')
			{
				size_t positions = 0;
				size_t tempIndex = index;

				while (input[tempIndex] != '>')
				{
					positions++;
					tempIndex++;
				}

				if (input[tempIndex + 1] == '<' && input[tempIndex + 2] != '/')
				{
					tree->left = makeTree(tree->left, input, tempIndex + 1, identificator + "L");

					return tree;
				}
				else
				{
					return tree;
				}
			}
			else if (input[index] != '>' && tree->right != nullptr)
			{
				tree->left = makeTree(tree->left, input, index, identificator + "L");
				return tree;
			}
			else if (input[index] != '>')
			{
				tree->right = makeTree(tree->right, input, index, identificator + "R"); //find biggest position

				Tree* temp = findBiggestPosition(tree->right);
				int copyCounter = numberOfCoppies(tree->right, temp);
				copyCounter--;//0
				//  "<MAP-MLT \"2\">1 2 3<AGG-SUM>4 5 6</AGG-SUM><SRT-REV>7<AGG-SUM>4 5 6</AGG-SUM>8</SRT-REV></MAP-MLT>"
				while (!(input[index] == '/' && input[index + 1] == temp->tagNode.tagName[1] && copyCounter == 0))
				{// while doesnt work properly when there are the same tags int the left, because it takes the first one
					if (input[index] == '/' && input[index + 1] == temp->tagNode.tagName[1] && copyCounter != 0)
					{
						copyCounter--;
					}
					index++;
				}
				while (input[index] != '>')
				{
					index++;
				}
			}
		}

		index++;
	}

	return tree;

}

std::vector<double> reverseContent(std::vector<double> list)
{
	std::vector<double> temp;

	while (!(list.empty()))
	{
		temp.push_back(list.back());
		list.pop_back();
	}

	return temp;
}

void reverseTree(Tree*& first)
{
	if (first == nullptr)
	{
		return;
	}

	first->tagNode.content = reverseContent(first->tagNode.content);
	reverseTree(first->right);
	reverseTree(first->left);
}
//<MAP-INC "1">
double takeMapInc(std::string input)
{
	std::string temp;
	size_t size = 10;

	while (input[size] != '\"')
	{
		temp += input[size];
		size++;
	}

	return atof(temp.c_str());
}
//<SRT-ORD "ASC">
std::string getOrder(std::string input)
{
	std::string temp;
	size_t index = 10;

	while (input[index] != '\"')
	{
		temp += input[index];
		index++;
	}

	return temp;
}

// MAP + 1 на всички елементи от списъка; AGG събира всички елементи от списък; SRT преобръща списъка
Result* returnNodeResult(Tree* first)
{
	std::vector<double> resultVector;
	Result* newResult = new Result{ resultVector };

	if (isMap_Inc(first->tagNode.tagName))
	{
		double temp = takeMapInc(first->tagNode.tagName);
		newResult->list = map_inc(temp, first->tagNode.content);
	}
	else if (isMap_Mlt(first->tagNode.tagName))
	{
		double temp = takeMapInc(first->tagNode.tagName);
		newResult->list = map_mlt(temp, first->tagNode.content);
	}
	else if (isAgg_Sum(first->tagNode.tagName))
	{
		newResult->list.push_back(agg_sum(first->tagNode.content));
	}
	else if (isAgg_Pro(first->tagNode.tagName))
	{
		newResult->list.push_back(agg_pro(first->tagNode.content));
	}
	else if (isAgg_Avg(first->tagNode.tagName))
	{
		newResult->list.push_back(agg_avg(first->tagNode.content));
	}
	else if (isAgg_Fst(first->tagNode.tagName))
	{
		newResult->list.push_back(agg_fst(first->tagNode.content));
	}
	else if (isAgg_Lst(first->tagNode.tagName))
	{
		newResult->list.push_back(agg_lst(srt_rev(first->tagNode.content)));
	}
	else if (isSrt_Rev(first->tagNode.tagName))
	{
		newResult->list = srt_rev(first->tagNode.content);
	}
	else if (isSrt_Ord_ASC(first->tagNode.tagName))
	{
		newResult->list = srt_ord(getOrder(first->tagNode.tagName), first->tagNode.content);
	}
	else if (isSrt_Ord_DSC(first->tagNode.tagName))
	{
		newResult->list = srt_slc((int)takeMapInc(first->tagNode.tagName), first->tagNode.content);
	}
	else if (isSrt_Slc(first->tagNode.tagName))
	{
		newResult->list = srt_slc((int)takeMapInc(first->tagNode.tagName), first->tagNode.content);
	}
	else if (isSrt_Dst(first->tagNode.tagName))
	{
		newResult->list = srt_dst(first->tagNode.content);
	}

	return newResult;
}

bool isRightTree(Tree* first, Tree* current)
{
	if (first == nullptr && current == nullptr)
	{
		return true;
	}
	if (first == nullptr || current == nullptr)
	{
		return false;
	}
	return first->tagNode.tagName == current->tagNode.tagName && first->tagNode.content == current->tagNode.content
		&& isRightTree(first->right, current->right) && isRightTree(first->left, current->left);
}
//"<MAP>1 2 3<AGG>4 5 6</AGG><SRT>7<AGG>4 5 6</AGG> 8</SRT><SRT>7<AGG>4 5 6</AGG> 8</SRT></MAP>"
int nodeCoppies(Tree* first, Tree* current)
{
	if (first->tagNode.id == current->tagNode.id || first == nullptr)
	{
		return 0;
	}

	if (first->tagNode.tagName == current->tagNode.tagName && first->tagNode.content == current->tagNode.content)
	{
		if (first->right == nullptr && first->left == nullptr)
		{
			return 1;
		}
		if (first->right != nullptr && first->left != nullptr)
		{
			return 1 + nodeCoppies(first->right, current) + nodeCoppies(first->left, current);
		}
		if (first->right == nullptr)
		{
			return 1 + nodeCoppies(first->left, current);
		}
		return 1 + nodeCoppies(first->right, current);
	}

	if (first->right == nullptr && first->left == nullptr)
	{
		return 0;
	}
	if (first->right != nullptr && first->left != nullptr)
	{
		return 0 + nodeCoppies(first->right, current) + nodeCoppies(first->left, current);
	}
	if (first->right == nullptr)
	{
		return 0 + nodeCoppies(first->left, current);
	}
	return 0 + nodeCoppies(first->right, current);
}
// <MAP-MLT \"2\">1 2 3<AGG-SUM>4 5 6</AGG-SUM><SRT-REV>7<AGG-SUM>4 5 6</AGG-SUM>8</SRT-REV></MAP-MLT>
std::vector<double> getNumbers(Tree* first, Tree* tree, std::string input)
{
	std::vector<double> numbers;
	size_t index = 0;
	int duplicates = nodeCoppies(first, tree);
	while (input[index] != '\0')
	{
		std::string temp;
		size_t tempIndex = index;
		if (input[index] == '<')
		{
			while (input[tempIndex] != '>')
			{
				temp += input[tempIndex];

				tempIndex++;
			}
			temp += input[tempIndex];
		}

		if (temp == tree->tagNode.tagName)
		{
			//std::cout << "Temp: " << temp << " dup: " << duplicates << std::endl;
			if (duplicates == 0)
			{// <MAP-MLT \"2\">1 2 3<AGG-SUM>4 5 6</AGG-SUM><SRT-REV>7<AGG-SUM>4 5 6</AGG-SUM>8</SRT-REV></MAP-MLT>

				index = tempIndex + 1;
				while (input[index] != '<' && input[index] != '\0')
				{
					if (isdigit(input[index]) == 4 || input[index] == '-')
					{
						std::string number;
						double tempNumber;

						while (input[index] != ' ' && input[index] != '<')
						{
							number += input[index];
							index++;
						}

						tempNumber = atof(number.c_str());
						numbers.push_back(tempNumber);

					}
					else
					{

						index++;
					}
				}
				return numbers;
			}
			else
			{
				duplicates--;
			}
		}

		index++;
	}

	return numbers;
}
// "<SRT-ORD \"ASC\">81 3<MAP-INC \"1\">4 12 55<AGG-AVG>4 8</AGG-AVG></MAP-INC>22</SRT-ORD>"
Result* returnTreeResult(Tree* first, Tree* current, std::string input)
{
	std::vector<double> resultVector;
	Result* newResult = new Result{ resultVector };

	if (current == nullptr)
	{
		return newResult;
	}

	if (current->left == nullptr && current->right == nullptr)
	{
		newResult = returnNodeResult(current);
		return newResult;
	}

	//right left
	Result* newRight = new Result{ resultVector };
	newRight = returnTreeResult(first, current->right, input);//6

	if (!(getNumbers(first, current, input).empty()))//5 5 2 1 4
	{
		std::vector<double> temp;
		double toCompare = getNumbers(first, current, input).back();
		while (!(current->tagNode.content.empty()))
		{
			temp.push_back(current->tagNode.content.back());
			current->tagNode.content.pop_back();
			if (temp.back() == toCompare)
			{
				while (!(newRight->list.empty()))
				{
					temp.push_back(newRight->list.back());
					newRight->list.pop_back();
				}
			}
		}

		while (!(temp.empty()))
		{
			current->tagNode.content.push_back(temp.back());
			temp.pop_back();
		}

		current->tagNode.content = reverseContent(current->tagNode.content);
	}
	else
	{
		current->tagNode.content = reverseContent(current->tagNode.content);

		while (!(newRight->list.empty()))
		{
			current->tagNode.content.push_back(newRight->list.back());
			newRight->list.pop_back();
		}
	}

	Result* newLeft = new Result{ resultVector };
	newLeft = returnTreeResult(first, current->left, input); //8, 7
	newResult = returnNodeResult(current); // 2, 3, 4

	while (!(newLeft->list.empty()))
	{
		newResult->list.push_back(newLeft->list.back());
		newLeft->list.pop_back();
	}

	newResult->list = reverseContent(newResult->list);

	return newResult;
}

std::string takeTag(std::string input)
{
	std::string result;
	size_t i = 0;

	while (input[i] != '\0')
	{
		if (input[i] == '<')
		{
			while (input[i] != '>')
			{
				result += input[i];

				i++;
			}
			result += input[i];
			return result;
		}

		i++;
	}

	return result;
}
//<AGG-SUM>4 5 6</AGG-SUM
int positionsToAfterTag(std::string input, int index)
{
	size_t positions = 0;

	while (input[index] != '>')
	{
		positions++;
		index++;
	}
	positions++;
	return positions;
}