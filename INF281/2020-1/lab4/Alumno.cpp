//
// Created by Carlos on 12/10/2020.
//

#include "Alumno.hpp"
#include <cstring>

using namespace std;

Alumno::Alumno():
escala(0),
especialidad(nullptr),
facultad(nullptr)
{}

Alumno::~Alumno()
{
    delete especialidad;
    delete facultad;
}

int Alumno::getPrioridad()
{
    return 4;
}

void Alumno::setEspecialidad(const char *val)
{
    copystr(especialidad,val);
}

void Alumno::setFacultad(const char *val)
{
    copystr(facultad, val);
}

void Alumno::setEscala(int val)
{
    escala = val;
}

int Alumno::getEscala() const
{
    return escala;
}

void Alumno::getEspecialidad(char *ptr) const
{
    strcpy(ptr, especialidad);
}

void Alumno::getFacultad(char *ptr) const
{
    strcpy(ptr, facultad);
}

void Alumno::read(std::istream &is)
{
    char buff[200], _;
    setInfo(is);
    is >> escala >> _;
    is.getline(buff, 200, ',');
    setEspecialidad(buff);
    is.getline(buff, 200);
    setFacultad(buff);
}

void Alumno::print(std::ostream &os)
{
    char ptr[200];
    getNombre(ptr);
    os << "Codigo: " << getCodigo() << endl
       << "Nombre: " << ptr << endl
       << "Facultad: " << facultad << endl
       << "Especialidad: " << especialidad << endl;
}
