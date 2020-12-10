#include "TagCalculations.h"
#include <algorithm> 
#include <functional>
#include <iostream>
#include<vector>

std::vector<double>& map_inc(double n, std::vector<double>& content)
{
	int size = content.size();
	for (size_t i = 0; i < size; i++)
	{
		content[i] += n;
	}
	return content;
}

std::vector<double>& map_mlt(double n, std::vector<double>& content)
{
	int size = content.size();
	for (size_t i = 0; i < size; i++)
	{
		content[i] *= n;
	}
	return content;
}

double add_sum(std::vector<double>& content)
{
	double sum = 0;
	int size = content.size();
	for (size_t i = 0; i < size; i++)
	{
		sum += content[i];
	}
	return sum;
}

double add_pro(std::vector<double>& content)
{
	double product = 1;
	int size = content.size();
	for (size_t i = 0; i < size; i++)
	{
		product *= content[i];
	}
	return product;
}

double add_avg(std::vector<double>& content)
{
	double sum = 0;
	int size = content.size();
	for (size_t i = 0; i < size; i++)
	{
		sum += content[i];
	}
	return (sum / size);
}

double add_fst(std::vector<double>& content)
{
	return content[0];
}

double add_lst(std::vector<double>& content)
{
	return content[content.size() - 1];
}

std::vector<double>& srt_rev(std::vector<double>& content)
{
	std::reverse(content.begin(), content.end());
	return content;
}

std::vector<double>& srt_ord(std::string order, std::vector<double>& content)
{
	if (order == "ASC")
	{
		sort(content.begin(), content.end());
	}
	else
	{
		sort(content.begin(), content.end(), std::greater<int>());
	}
	return content;
}

std::vector<double> srt_slc(int n, std::vector<double>& content)
{
	int size = content.size();
	std::vector<double> subVector;
	for (size_t i = n; i < size; i++)
	{
		subVector.push_back(content[i]);
	}
	return subVector;
}

std::vector<double>& srt_dst(std::vector<double>& content)
{
	int size = content.size();
	std::vector<double> subVector;
	auto end = content.end();
	for (auto it = content.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	content.erase(end, content.end());
	
	return content;
}
