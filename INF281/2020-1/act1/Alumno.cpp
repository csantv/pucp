#include <iomanip>

#include "Alumno.h"

using namespace std;

void operator+ (struct Alumno& lhs, struct ACurso& rhs)
{
    if (lhs.codigo != rhs.codigo) return;
    if (rhs.operacion != 'N') return;
    int num = lhs.numcur;
    lhs.curso[num] = rhs.curso;
    lhs.ciclo[num] = rhs.ciclo;
    lhs.nota[num] = rhs.nota;
    lhs.credito[num] = rhs.credito;
    lhs.numcur++;
}

void operator* (struct Alumno& lhs, struct ACurso& rhs)
{
    if (lhs.codigo != rhs.codigo) return;
    if (rhs.operacion != 'A') return;
    for (int i = 0; i < lhs.numcur; ++i) {
        if (lhs.ciclo[i] == rhs.ciclo &&
            lhs.curso[i] == rhs.curso) {
            lhs.nota[i] = rhs.nota;
            return;
        }
    }
}

void operator- (struct Alumno& lhs, struct ACurso& rhs)
{
    if (lhs.codigo != rhs.codigo) return;
    if (rhs.operacion != 'E') return;
    for (int i = 0; i < lhs.numcur; ++i) {
        if (lhs.ciclo[i] == rhs.ciclo &&
            lhs.curso[i] == rhs.curso) {
            lhs.curso[i] = 0;
            lhs.ciclo[i] = 0;
            lhs.nota[i] = 0;
            lhs.credito[i] = 0;
            lhs.numcur--;
            return;
        }
    }
}

float operator/ (struct Alumno& rhs, int ciclo)
{
    int sum = 0, num = 0;
    for (int i = 0; i < rhs.numcur; ++i) {
        if (rhs.ciclo[i] == ciclo) {
            sum += rhs.nota[i];
            num++;
        }
    }
    return (float)sum / (float)num;
}

float operator-- (struct Alumno& arg)
{
    float sum = 0;
    for (int i = 0; i < arg.numcur; ++i) {
        sum += arg.credito[i];
    }
    return sum;
}

float operator++ (struct Alumno& arg)
{
    float sum = 0;
    for (int i = 0; i < arg.numcur; ++i) {
        if (arg.nota[i] >= 11)
            sum += arg.credito[i];
    }
    return sum;
}

void operator>> (ifstream& lhs, struct Alumno& rhs)
{
    char ignore[50]; int _;
    lhs >> rhs.tipo >> rhs.codigo >> rhs.nombre;
    lhs >> _;
    if (lhs.fail()) {
        lhs.clear();
    }
    lhs >> ignore >> ignore;
}

void operator>> (ifstream& lhs, struct ACurso& rhs)
{
    char ignore[7], _;
    int yy, div;
    lhs >> rhs.codigo >> ignore >> rhs.nota >> yy >> _ >> div >> rhs.credito >> rhs.operacion;
    rhs.ciclo = yy * 10 + div;
}

void operator<< (ofstream& lhs, struct Alumno& rhs)
{
    lhs << "Nombre: " << rhs.nombre << endl << "Codigo: " << rhs.codigo << endl;
    lhs << setfill('=') << setw(28) << "" << endl;
}