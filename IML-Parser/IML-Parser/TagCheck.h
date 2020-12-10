#pragma once
#include<iostream>
#include <string>
#include <regex>

bool isMap_Inc(std::string tag)
{
	std::regex inc("(<MAP-INC) ((\"(-?(\\d)+(\\.)?(\\d)*)\">))");
	if (regex_match(tag, inc)) return true;
	return false;
}

bool isMap_Mlt(std::string tag)
{
	std::regex mlt("(<MAP-MLT) ((\"(-?(\\d)+(\\.)?(\\d)*)\">))");
	if (regex_match(tag, mlt)) return true;
	return false;
}

bool isAgg_Sum(std::string tag)
{
	std::regex sum("(<AGG-SUM>)");
	if (regex_match(tag, sum)) return true;
	return false;
}

bool isAgg_Pro(std::string tag)
{
	std::regex pro("(<AGG-PRO>)");
	if (regex_match(tag, pro)) return true;
	return false;
}

bool isAgg_Avg(std::string tag)
{
	std::regex avg("(<AGG-AVG>)");
	if (regex_match(tag, avg)) return true;
	return false;
}

bool isAgg_Fst(std::string tag)
{
	std::regex fst("(<AGG-FST>)");
	if (regex_match(tag, fst)) return true;
	return false;
}

bool isAgg_Lst(std::string tag)
{
	std::regex lst("(<AGG-LST>)");
	if (regex_match(tag, lst)) return true;
	return false;
}

bool isSrt_Rev(std::string tag)
{
	std::regex rev("(<SRT-REV>)");
	if (regex_match(tag, rev)) return true;
	return false;
}

bool isSrt_Ord_ASC(std::string tag)
{
	std::regex asc("(<SRT-ORD) (\")(ASC)(\">)");
	if (regex_match(tag, asc)) return true;
	return false;
}

bool isSrt_Ord_DSC(std::string tag)
{
	std::regex dsc("(<SRT-ORD) (\")(DSC)(\">)");
	if (regex_match(tag, dsc)) return true;
	return false;
}

bool isSrt_Slc(std::string tag)
{
	std::regex slc("(<SRT-SLC) ((\"(-?(\\d)+(\\.)?(\\d)*)\">))");
	if (regex_match(tag, slc)) return true;
	return false;
}

bool isSrt_Dst(std::string tag)
{
	std::regex dst("(<SRT-DST>)");
	if (regex_match(tag, dst)) return true;
	return false;
}