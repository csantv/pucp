#include "Persona.hpp"
#include <cstring>

Persona::Persona():
nombre(nullptr),
codigo(0),
distrito(nullptr)
{}

Persona::Persona(const Persona &orig):
codigo(orig.getCodigo()),
nombre(nullptr),
distrito(nullptr)
{
    char buff[200];
    orig.getNombre(buff);
    setNombre(buff);
    orig.getDistrito(buff);
    setDistrito(buff);
}

Persona::~Persona()
{
    delete nombre;
    delete distrito;
}

void Persona::getNombre(char *ptr) const
{
    strcpy(ptr, nombre);
}

void Persona::setNombre(const char *val)
{
    delete nombre;
    nombre = new char[strlen(val)+1];
    strcpy(nombre, val);
}

int Persona::getCodigo() const
{
    return codigo;
}

void Persona::setCodigo(int val)
{
    codigo = val;
}

void Persona::getDistrito(char *ptr) const
{
    strcpy(ptr, distrito);
}

void Persona::setDistrito(const char *val)
{
    delete distrito;
    distrito = new char[strlen(val)+1];
    strcpy(distrito, val);
}
