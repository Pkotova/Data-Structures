#pragma once
#include <iostream>
#include <cstring>

using namespace std;

class String
{
    char* data;
    unsigned length;

public:


    String();
    String(char c);
    String(const char* c);
    String(const String& s);
    ~String();
    unsigned len() const;
    int index(char c) const;
    void upcase(unsigned first, unsigned last);
    void downcase(unsigned first, unsigned last);
    void togglecase(unsigned first, unsigned last);

    friend std::ostream& operator<< (std::ostream& os, const String& s);
    friend std::istream& operator>> (std::istream& is, String& s);

    char  operator[] (unsigned j) const;
    char& operator[] (unsigned j);

    String& operator= (const String& s);
    String& operator+= (const String& s);


    friend String operator+ (const String& leftOperand, const String& rightOperand);
    friend String operator+ (const String& leftOperand, char          rightOperand);
    friend String operator+ (const String& leftOperand, const char* rightOperand);
    friend String operator+ (char          leftOperand, const String& rightOperand);
    friend String operator+ (const char* leftOperand, const String& rightOperand);

    friend bool operator== (const String& leftOperand, const String& rightOperand);
    friend bool operator== (const String& leftOperand, char          rightOperand);
    friend bool operator== (const String& leftOperand, const char* rightOperand);
    friend bool operator== (char          leftOperand, const String& rightOperand);
    friend bool operator== (const char* leftOperand, const String& rightOperand);

    friend bool operator> (const String& leftOperand, const String& rightOperand);
    friend bool operator> (const String& leftOperand, char          rightOperand);
    friend bool operator> (const String& leftOperand, const char* rightOperand);
    friend bool operator> (char          leftOperand, const String& rightOperand);
    friend bool operator> (const char* leftOperand, const String& rightOperand);

    friend bool operator!= (const String& leftOperand, const String& rightOperand);
    friend bool operator!= (const String& leftOperand, char          rightOperand);
    friend bool operator!= (const String& leftOperand, const char* rightOperand);
    friend bool operator!= (char          leftOperand, const String& rightOperand);
    friend bool operator!= (const char* leftOperand, const String& rightOperand);

    friend bool operator< (const String& leftOperand, const String& rightOperand);
    friend bool operator< (const String& leftOperand, char          rightOperand);
    friend bool operator< (const String& leftOperand, const char* rightOperand);
    friend bool operator< (char          leftOperand, const String& rightOperand);
    friend bool operator< (const char* leftOperand, const String& rightOperand);

    friend bool operator<= (const String& leftOperand, const String& rightOperand);
    friend bool operator<= (const String& leftOperand, char          rightOperand);
    friend bool operator<= (const String& leftOperand, const char* rightOperand);
    friend bool operator<= (char          leftOperand, const String& rightOperand);
    friend bool operator<= (const char* leftOperand, const String& rightOperand);

    friend bool operator>= (const String& leftOperand, const String& rightOperand);
    friend bool operator>= (const String& leftOperand, char          rightOperand);
    friend bool operator>= (const String& leftOperand, const char* rightOperand);
    friend bool operator>= (char          leftOperand, const String& rightOperand);
    friend bool operator>= (const char* leftOperand, const String& rightOperand);

};
