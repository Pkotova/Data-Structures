#include "IMLRepository.h"
#include"fstream"
#include"iostream"
#include <string>
#include"Form1.h"
void IMLRepository::setFile(string file)
{
    this->file = "Zad2.txt";
}
string IMLRepository::getFile() const
{
    return this->file;
}
void IMLRepository::setScript(string script)
{
    this->script = script;
}
string IMLRepository::getScript()
{
  //  CppCLRWinformsProjekt::Form1 ff;
    string ss = this->getFile();
   
    std::ifstream input_file("Zad2.txt");
    std::string dna;
    std::string text_read;
    while (std::getline(input_file, text_read))
    {
        const std::string::size_type position = text_read.find('\n');
        if (position != std::string::npos)
        {
            text_read.erase(position);
        }
        dna += text_read;
    }
    //dna = "ne mojah da namerq faila";
    return dna;
}
string IMLRepository::getOriginalScript()
{
    //  CppCLRWinformsProjekt::Form1 ff;
    string ss = this->getFile();
  //  int row = 1;
    std::ifstream input_file(ss);
    std::string dna;
    std::string text_read;
    while (std::getline(input_file, text_read))
    {
        //dna += to_string(row);
        dna += '\t';
        dna += text_read;
        dna += '\r';
        dna += '\n';
        //row++;
    }
    //dna = "ne mojah da namerq faila";
    return dna;
}

