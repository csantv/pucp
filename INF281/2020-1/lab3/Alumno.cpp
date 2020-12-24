#include "Alumno.hpp"
#include <cstring>

Alumno::Alumno():
especialidad(nullptr),
facultad(nullptr),
escala(0)
{}

Alumno::Alumno(const Alumno &orig):
especialidad(nullptr),
facultad(nullptr),
escala(0),
Persona(orig)
{
    char buff[200];
    orig.getEspecialidad(buff);
    setEspecialidad(buff);
    orig.getFacultad(buff);
    setFacultad(buff);
}

Alumno::~Alumno()
{
    delete especialidad;
    delete facultad;
}

int Alumno::getEscala() const {
    return escala;
}

void Alumno::setEscala(int val) {
    escala = val;
}

void Alumno::getEspecialidad(char *ptr) const
{
    strcpy(ptr, especialidad);
}

void Alumno::setEspecialidad(const char *val)
{
    delete especialidad;
    especialidad = new char[strlen(val)+1];
    strcpy(especialidad, val);
}

void Alumno::getFacultad(char *ptr) const
{
    strcpy(ptr, facultad);
}

void Alumno::setFacultad(const char *val)
{
    delete facultad;
    facultad = new char[strlen(val)+1];
    strcpy(facultad, val);
}
