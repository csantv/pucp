/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "Emergencia.h"
#include <cstring>

Emergencia::Emergencia():
telefonoRef(0),
nombreRef(nullptr),
Paciente()
{}

Emergencia::Emergencia(const Emergencia &orig):
telefonoRef(orig.getTelefonoRef()),
nombreRef(nullptr),
Paciente(orig)
{
    char buff[200];
    orig.getNombreRef(buff);
    setNombreRef(buff);
}

Emergencia::~Emergencia()
{
    nombreRef = nullptr;
    delete nombreRef;
}

int Emergencia::getTelefonoRef() const {
    return telefonoRef;
}

void Emergencia::setTelefonoRef(int val)
{
    telefonoRef = val;
}

void Emergencia::getNombreRef(char *ptr) const
{
    strcpy(ptr, nombreRef);
}

void Emergencia::setNombreRef(const char *val)
{
    delete nombreRef;
    nombreRef = new char[strlen(val)+1];
    strcpy(nombreRef, val);
}
