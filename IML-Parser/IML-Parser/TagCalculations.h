#pragma once
#include<vector>
#include<string>

std::vector<double>& map_inc(double n, std::vector<double>& content);
std::vector<double>& map_mlt(double n, std::vector<double>& content);

double add_sum(std::vector<double>& content);
double add_pro(std::vector<double>& content);
double add_avg(std::vector<double>& content);
double add_fst(std::vector<double>& content);
double add_lst(std::vector<double>& content);

std::vector<double>& srt_rev(std::vector<double>& content);
std::vector<double>& srt_ord(std::string order, std::vector<double>& content);
std::vector<double> srt_slc(int n, std::vector<double>& content);
std::vector<double>& srt_dst(std::vector<double>& content);


