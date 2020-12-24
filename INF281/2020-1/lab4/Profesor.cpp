#include "Profesor.hpp"
#include <cstring>

using namespace std;

Profesor::Profesor():
categoria(nullptr),
dedicacion(nullptr),
seccion(nullptr),
grado(nullptr)
{}

Profesor::~Profesor()
{
    delete categoria;
    delete dedicacion;
    delete seccion;
    delete grado;
}

int Profesor::getPrioridad()
{
    if (strcmp(dedicacion, "TC") != 0) return 1;
    if (strcmp(dedicacion, "TP") != 0) return 2;
    if (strcmp(dedicacion, "TPA") != 0) return 3;
    return -1;
}

void Profesor::setCategoria(const char *val)
{
    copystr(categoria, val);
}

void Profesor::setDedicacion(const char *val)
{
    copystr(dedicacion, val);
}

void Profesor::setSeccion(const char *val)
{
    copystr(seccion, val);
}

void Profesor::setGrado(const char *val)
{
    copystr(grado, val);
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

void Profesor::read(std::istream &is)
{
    char buff[200];
    setInfo(is);
    is.getline(buff, 200, ',');
    setCategoria(buff);
    is.getline(buff, 200, ',');
    setDedicacion(buff);
    is.getline(buff, 200, ',');
    setSeccion(buff);
    is.getline(buff, 200);
    setGrado(buff);
}

void Profesor::print(std::ostream &os)
{
    char ptr[200];
    getNombre(ptr);
    os << "Codigo: " << getCodigo() << endl
       << "Nombre: " << ptr << endl
       << "Dedicacion: " << dedicacion << endl
       << "Seccion: " << seccion << endl;
}
