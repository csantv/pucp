#include "Persona.hpp"
#include <cstring>
#include <iomanip>

using namespace std;

Persona::Persona()
{
    nombre = nullptr;
    dni = 0;
    sueldo = 0;
}

Persona::~Persona()
{
    delete nombre;
}

Persona::Persona(const Persona &orig):
Persona()
{
    *this = orig;
}

Persona& Persona::operator=(const Persona &orig)
{
    if (&orig != this) {
        char nomb[60];
        orig.getNombre(nomb);
        setNombre(nomb);
        sueldo = orig.sueldo;
        dni = orig.dni;
    }
    return *this;
}

int Persona::getDni() const {
    return dni;
}

void Persona::setDni(int val) {
    dni = val;
}

double Persona::getSueldo() const {
    return sueldo;
}

void Persona::setSueldo(double val) {
    sueldo = val;
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

std::istream& operator>>(std::istream &is, Persona &rhs)
{
    int dni; double sueldo;
    char nomb[60], _;
    is >> dni >> _;
    is.getline(nomb, 60, ',');
    is >> sueldo;
    rhs.setNombre(nomb);
    rhs.setDni(dni);
    rhs.setSueldo(sueldo);
    return is;
}

std::ostream &operator<<(std::ostream &os, const Persona &rhs)
{
    char nomb[60];
    rhs.getNombre(nomb);
    os << nomb << " " << rhs.getDni() << " " <<  setprecision(2) << fixed << rhs.getSueldo();
    return os;
}
