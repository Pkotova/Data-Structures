#include "String.h"

String::String()
{
    length = 0;
    data = new char[0];
}

String::String(char c)
{
    length = 1;
    data = new char(c);
}

String::String(const char* c)
{
    if (c)
    {
        unsigned n = 0;
        while (c[n] != '\0') n++;
        length = n;
        data = new char[n];
        for (unsigned j = 0; j < n; j++)
            data[j] = c[j];
    }
    else
    {
        length = 0;
        data = new char[0];
    }
}

String::String(const String& s)
{
    length = s.len();
    data = new char[length];
    for (unsigned j = 0; j < length; j++)
        data[j] = s[j];
}



String::~String()
{
    delete[] data;
}



unsigned String::len() const
{
    return length;
}

int String::index(char c) const
{
    for (unsigned j = 0; j < length; j++)
        if (data[j] == c) return (int)j;
    return -1;
}



void String::upcase(unsigned first, unsigned last)
{
    if ((first >= last) || (last > length)) throw 1;

    for (unsigned j = first; j < last; j++)
        if ('a' <= data[j] && data[j] <= 'z')
            data[j] -= ('a' - 'A');
}

void String::downcase(unsigned first, unsigned last)
{
    if ((first >= last) || (last > length)) throw 1;

    for (unsigned j = first; j < last; j++)
        if ('A' <= data[j] && data[j] <= 'Z')
            data[j] += ('a' - 'A');
}

void String::togglecase(unsigned first, unsigned last)
{
    if ((first >= last) || (last > length)) throw 1;

    for (unsigned j = first; j < last; j++)
        if ('A' <= data[j] && data[j] <= 'Z')
            data[j] += ('a' - 'A');
        else if ('a' <= data[j] && data[j] <= 'z')
            data[j] -= ('a' - 'A');
}



std::ostream& operator<< (std::ostream& os, const String& s)
{
    if (s.len() > 0)
    {
        for (unsigned j = 0; j < s.len(); j++)
            os << s[j];
    }
    else os << "";

    return os;
}

std::istream& operator>> (std::istream& is, String& s)
{
    char* c = new char[1000];
    is >> c;
    s = String(c);
    delete[] c;

    return is;
}



char String::operator[] (unsigned j) const
{
    if (j >= length) throw 1;
    return data[j];
}

char& String::operator[] (unsigned j)
{
    if (j >= length) throw 1;
    return data[j];
}



String& String::operator= (const String& s)
{
    if (this == &s) return *this;

    delete data;
    length = s.len();
    data = new char[length];
    for (unsigned j = 0; j < length; j++)
        data[j] = s[j];
    return *this;
}



String& String::operator+= (const String& s)
{
    unsigned len = length + s.len();
    char* str = new char[len];

    for (unsigned j = 0; j < length; j++)
        str[j] = data[j];

    for (unsigned i = 0; i < s.len(); i++)
        str[length + i] = s[i];

    delete data;
    length = len;
    data = str;
    return *this;
}



String operator+ (const String& leftOperand, const String& rightOperand)
{
    return String(leftOperand) += rightOperand;
}

String operator+ (const String& leftOperand, char rightOperand)
{
    return String(leftOperand) += String(rightOperand);
}

String operator+ (const String& leftOperand, const char* rightOperand)
{
    return String(leftOperand) += String(rightOperand);
}

String operator+ (char leftOperand, const String& rightOperand)
{
    return String(leftOperand) += rightOperand;
}
String operator+ (const char* leftOperand, const String& rightOperand)
{
    return String(leftOperand) += rightOperand;
}



bool operator== (const String& leftOperand, const String& rightOperand)
{
    if (leftOperand.len() != rightOperand.len()) return false;

    unsigned cap = leftOperand.len();
    unsigned   n = 0;
    while ((n < cap) && (leftOperand[n] == rightOperand[n])) n++;
    return (n == cap);
}

bool operator== (const String& leftOperand, char rightOperand)
{
    return (leftOperand == String(rightOperand));
}

bool operator== (const String& leftOperand, const char* rightOperand)
{
    return (leftOperand == String(rightOperand));
}

bool operator== (char leftOperand, const String& rightOperand)
{
    return (String(leftOperand) == rightOperand);
}

bool operator== (const char* leftOperand, const String& rightOperand)
{
    return (String(leftOperand) == rightOperand);
}



bool operator> (const String& leftOperand, const String& rightOperand)
{
    unsigned cap = (leftOperand.len() < rightOperand.len()) ? leftOperand.len() : rightOperand.len();
    unsigned n = 0;
    while ((n < cap) && (leftOperand[n] == rightOperand[n])) n++;
    if (n == cap) return (leftOperand.len() > rightOperand.len());

    if ((('A' <= leftOperand[n] && leftOperand[n] <= 'Z') || ('a' <= leftOperand[n] && leftOperand[n] <= 'z')) &&
        (('A' <= rightOperand[n] && rightOperand[n] <= 'Z') || ('a' <= rightOperand[n] && rightOperand[n] <= 'z')))
    {
        char A = (leftOperand[n] & ~32);
        char B = (rightOperand[n] & ~32);
        if (A != B) return (A > B);
    }
    return leftOperand[n] > rightOperand[n];
}

bool operator> (const String& leftOperand, char rightOperand)
{
    return (leftOperand > String(rightOperand));
}

bool operator> (const String& leftOperand, const char* rightOperand)
{
    return (leftOperand > String(rightOperand));
}

bool operator> (char leftOperand, const String& rightOperand)
{
    return (String(leftOperand) > rightOperand);
}

bool operator> (const char* leftOperand, const String& rightOperand)
{
    return (String(leftOperand) > rightOperand);
}



bool operator!= (const String& leftOperand, const String& rightOperand)
{
    return !(leftOperand == rightOperand);
}

bool operator!= (const String& leftOperand, char rightOperand)
{
    return !(leftOperand == rightOperand);
}

bool operator!= (const String& leftOperand, const char* rightOperand)
{
    return !(leftOperand == rightOperand);
}

bool operator!= (char leftOperand, const String& rightOperand)
{
    return !(leftOperand == rightOperand);
}

bool operator!= (const char* leftOperand, const String& rightOperand)
{
    return !(leftOperand == rightOperand);
}



bool operator< (const String& leftOperand, const String& rightOperand)
{
    return !(leftOperand == rightOperand) && !(leftOperand > rightOperand);
}

bool operator< (const String& leftOperand, char rightOperand)
{
    return !(leftOperand == rightOperand) && !(leftOperand > rightOperand);
}

bool operator< (const String& leftOperand, const char* rightOperand)
{
    return !(leftOperand == rightOperand) && !(leftOperand > rightOperand);
}

bool operator< (char leftOperand, const String& rightOperand)
{
    return !(leftOperand == rightOperand) && !(leftOperand > rightOperand);
}

bool operator< (const char* leftOperand, const String& rightOperand)
{
    return !(leftOperand == rightOperand) && !(leftOperand > rightOperand);
}



bool operator<= (const String& leftOperand, const String& rightOperand)
{
    return !(leftOperand > rightOperand);
}

bool operator<= (const String& leftOperand, char rightOperand)
{
    return !(leftOperand > rightOperand);
}

bool operator<= (const String& leftOperand, const char* rightOperand)
{
    return !(leftOperand > rightOperand);
}

bool operator<= (char leftOperand, const String& rightOperand)
{
    return !(leftOperand > rightOperand);
}

bool operator<= (const char* leftOperand, const String& rightOperand)
{
    return !(leftOperand > rightOperand);
}



bool operator>= (const String& leftOperand, const String& rightOperand)
{
    return (leftOperand == rightOperand) || (leftOperand > rightOperand);
}

bool operator>= (const String& leftOperand, char rightOperand)
{
    return (leftOperand == rightOperand) || (leftOperand > rightOperand);
}

bool operator>= (const String& leftOperand, const char* rightOperand)
{
    return (leftOperand == rightOperand) || (leftOperand > rightOperand);
}

bool operator>= (char leftOperand, const String& rightOperand)
{
    return (leftOperand == rightOperand) || (leftOperand > rightOperand);
}

bool operator>= (const char* leftOperand, const String& rightOperand)
{
    return (leftOperand == rightOperand) || (leftOperand > rightOperand);
}
