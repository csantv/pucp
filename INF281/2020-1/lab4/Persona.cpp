//
// Created by Carlos on 12/10/2020.
//

#include "Persona.hpp"
#include <cstring>

Persona::Persona():
nombre(nullptr),
codigo(0),
distrito(nullptr)
{}

Persona::~Persona()
{
    delete nombre;
    delete distrito;
}

void Persona::setInfo(std::istream &is)
{
    char buff[200], _; int cod;
    is.getline(buff, 200, ',');
    setNombre(buff);
    is >> cod >> _;
    setCodigo(cod);
    is.getline(buff, 200, ',');
    setDistrito(buff);
}

void Persona::setNombre(const char *val)
{
    copystr(nombre, val);
}

void Persona::setDistrito(const char *val)
{
    copystr(distrito, val);
}

void Persona::setCodigo(int val)
{
    codigo = val;
}

void Persona::getNombre(char *ptr) const
{
    strcpy(ptr, nombre);
}

void Persona::getDistrito(char *ptr) const
{
    strcpy(ptr, distrito);
}

int Persona::getCodigo() const
{
    return codigo;
}

void Persona::copystr(char *&dest, const char *src)
{
    delete dest;
    dest = new char[strlen(src)+1];
    strcpy(dest, src);
}
