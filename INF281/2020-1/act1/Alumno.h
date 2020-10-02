#ifndef INF281_ALUMNO_H
#define INF281_ALUMNO_H

#include <fstream>

struct Alumno
{
    int codigo;
    char tipo;
    char nombre[100];
    int curso[100];
    int ciclo[100];
    int nota[100];
    float credito[100];
    int numcur;
};

struct ACurso
{
    int codigo;
    int curso;
    int ciclo;
    int nota;
    float credito;
    char operacion;
};

void operator+ (struct Alumno& lhs, struct ACurso& rhs);
void operator* (struct Alumno& lhs, struct ACurso& rhs);
void operator- (struct Alumno& lhs, struct ACurso& rhs);
float operator/ (struct Alumno& rhs, int ciclo);
float operator-- (struct Alumno& arg);
float operator++ (struct Alumno& arg);
void operator>> (std::ifstream& lhs, struct Alumno& rhs);
void operator>> (std::ifstream& lhs, struct ACurso& rhs);
void operator<< (std::ofstream& lhs, struct Alumno& rhs);

#endif //INF281_ALUMNO_H
