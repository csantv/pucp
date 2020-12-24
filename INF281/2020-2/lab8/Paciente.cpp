/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "Paciente.h"
#include <cstring>

Paciente::Paciente():
dni(0),
nombre(nullptr),
codMed(nullptr)
{}

Paciente::Paciente(const Paciente &orig):
dni(orig.getDni()),
nombre(nullptr),
codMed(nullptr)
{
    char buff[200];
    orig.getNombre(buff);
    setNombre(buff);
    orig.getCodMed(buff);
    setCodMed(buff);
}

Paciente::~Paciente()
{
    nombre = nullptr;
    codMed = nullptr;
    delete nombre;
    delete codMed;
}

int Paciente::getDni() const
{
    return dni;
}

void Paciente::setDni(int val)
{
    dni = val;
}

void Paciente::getNombre(char *ptr) const
{
    strcpy(ptr, nombre);
}

void Paciente::getCodMed(char *ptr) const
{
    strcpy(ptr, codMed);
}

void Paciente::setNombre(const char *val)
{
    delete nombre;
    nombre = new char[strlen(val)+1];
    strcpy(nombre, val);
}

void Paciente::setCodMed(const char *val)
{
    delete codMed;
    codMed = new char[strlen(val)+1];
    strcpy(codMed, val);
}

bool Paciente::isNull()
{
    return dni == 0 && nombre == nullptr && codMed == nullptr;
}
