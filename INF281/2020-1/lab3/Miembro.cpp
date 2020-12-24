#include "Miembro.hpp"

Miembro::Miembro():
numAlumnos(0),
numProfs(0),
lalumno(nullptr),
lprofesor(nullptr)
{}

Miembro::Miembro(const Miembro &orig)
{
    numAlumnos = orig.numAlumnos;
    numProfs = orig.numProfs;
    lprofesor = new Profesor[orig.numProfs];
    lalumno = new Alumno[orig.numAlumnos];
    for (int i = 0; i < numProfs; ++i) {
        lprofesor[i] = orig.lprofesor[i];
    }
    for (int i = 0; i < numAlumnos; ++i) {
        lalumno[i] = orig.lalumno[i];
    }
}

Miembro::~Miembro()
{
    delete[] lalumno;
    delete[] lprofesor;
}

void Miembro::operator+(const Alumno &rhs)
{
    if (!lalumno) lalumno = new Alumno;
    numAlumnos++;
    auto aux = new Alumno[numAlumnos];
    for (int i = 0; i < numAlumnos-1; ++i) aux[i] = lalumno[i];
    aux[numAlumnos] = rhs;
    delete[] lalumno;
    lalumno = aux;
}

void Miembro::operator+(const Profesor &rhs)
{
    if (!lprofesor) lprofesor = new Profesor;
    numProfs++;
    auto aux = new Profesor[numProfs];
    for (int i = 0; i < numProfs - 1; ++i) aux[i] = lprofesor[i];
    aux[numProfs] = rhs;
    delete[] lprofesor;
    lprofesor = aux;
}
