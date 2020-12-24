#include "Profesor.hpp"
#include <cstring>

Profesor::Profesor():
categoria(nullptr),
dedicacion(nullptr),
seccion(nullptr),
grado(nullptr)
{}

Profesor::Profesor(const Profesor &orig):
categoria(nullptr),
dedicacion(nullptr),
seccion(nullptr),
grado(nullptr),
Persona(orig)
{
    char buff[200];
    orig.getCategoria(buff);
    setCategoria(buff);
    orig.getDedicacion(buff);
    setDedicacion(buff);
    orig.getSeccion(buff);
    setSeccion(buff);
    orig.getGrado(buff);
    setGrado(buff);
}

Profesor::~Profesor()
{
    delete categoria;
    delete dedicacion;
    delete seccion;
    delete grado;
}

void Profesor::setGrado(const char *val) {
    copystr(grado, val);
}

void Profesor::setCategoria(const char *val) {
    copystr(categoria, val);
}

void Profesor::setDedicacion(const char *val) {
    copystr(categoria, val);
}

void Profesor::setSeccion(const char *val) {
    copystr(seccion, val);
}

void Profesor::getCategoria(char *ptr) const
{
    strcpy(ptr, categoria);
}

void Profesor::getDedicacion(char *ptr) const
{
    strcpy(ptr, dedicacion);
}

void Profesor::getSeccion(char *ptr) const
{
    strcpy(ptr, seccion);
}

void Profesor::getGrado(char *ptr) const
{
    strcpy(ptr, grado);
}

void Profesor::copystr(char *&dest, const char *orig)
{
    delete dest;
    dest = new char[strlen(orig)+1];
    strcpy(dest, orig);
}
