#include "IMLRepository.h"
#include"fstream"
#include"iostream"
#include <string>
void IMLRepository::setFile(const char file[30])
{
    strcpy_s(this->file, 30, file);
}
void IMLRepository::setScript(String script)
{
    this->script = script;
}
string IMLRepository::getScript()
{
    std::ifstream input_file("zad1.txt");
    std::string dna;
    std::string text_read;
    while (std::getline(input_file, text_read))
    {
        const std::string::size_type position = text_read.find('\r');
        if (position != std::string::npos)
        {
            text_read.erase(position);
        }
        dna += text_read;
    }
 
    return dna;
}
