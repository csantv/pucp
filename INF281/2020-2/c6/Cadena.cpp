#include "Cadena.hpp"
#include <cstring>
#include <iostream>

using namespace std;

Cadena::Cadena():
str(nullptr),
len(0),
cap(0)
{}

Cadena::Cadena(const char *val):
str(nullptr),
len(strlen(val)),
cap(len+1)
{
    str = new char[cap]();
    strcpy(str, val);
}

Cadena::Cadena(int num):
str(nullptr),
len(0),
cap(num)
{
    str = new char[cap]();
}

Cadena::Cadena(const Cadena &rhs):
str(nullptr),
len(rhs.len),
cap(rhs.cap)
{
    str = new char[cap];
    strcpy(str, rhs.str);
}

Cadena::~Cadena()
{
    delete str;
}

unsigned long long Cadena::length() const
{
    return len;
}

void Cadena::print() const
{
    cout << str << endl;
}

void Cadena::assign(const char *val)
{
    unsigned long long newlen = strlen(val)+1;
    if (newlen > cap) {
        cap = 1.3 * newlen;
        delete str;
        str = new char[cap];
    }
    strcpy(str, val);
    len = newlen;
}

void Cadena::assign(const Cadena &cad)
{
    char buff[cad.length()+1];
    cad.getStr(buff);
    assign(buff);
}

void Cadena::getStr(char *ptr) const
{
    strcpy(ptr, str);
}

Cadena& Cadena::operator=(const char *val)
{
    assign(val);
    return *this;
}

Cadena& Cadena::operator=(const Cadena &cad)
{
    if (&cad != this) {
        assign(cad);
    }
    return *this;
}

Cadena Cadena::operator+(const Cadena &rhs) const
{
    Cadena tmp(*this);
    tmp.append(rhs);
    return tmp;
}

void Cadena::append(const char *val)
{
    char buff[len + strlen(val) + 1];
    strcpy(buff, str);
    strcat(buff, val);
    assign(buff);
}

void Cadena::append(const Cadena &cad)
{
    char buff[cad.length()+1];
    cad.getStr(buff);
    append(buff);
}

void Cadena::swap(Cadena &cad)
{
    char buff[cad.length()+1];
    char buff2[len+1];
    cad.getStr(buff);
    strcpy(buff2, str);
    cad.assign(buff2);
    assign(buff);
}

int Cadena::compare(const char *val)
{
    return strcmp(str, val);
}

int Cadena::compare(const Cadena &cad)
{
    char buff[cad.length()+1];
    cad.getStr(buff);
    return compare(buff);
}
