#ifndef INF281_MIEMBRO_HPP
#define INF281_MIEMBRO_HPP

#include "Alumno.hpp"
#include "Profesor.hpp"

class Miembro {
public:
    Miembro();
    Miembro(const Miembro &orig);
    ~Miembro();

    void operator+(const Alumno &rhs);
    void operator+(const Profesor &rhs);

private:
    Alumno *lalumno;
    Profesor *lprofesor;

    int numAlumnos;
    int numProfs;
};


#endif //INF281_MIEMBRO_HPP
