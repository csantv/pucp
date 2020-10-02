/*
 * NOMBRE: CARLOS SANTOS TORO VERA
 * CODIGO: 20171878
 */

#ifndef INF281_MEDICOSPACIENTES_H
#define INF281_MEDICOSPACIENTES_H

#include <fstream>

struct StMedico
{
    char codigo[7];
    char nombre[100];
    char especialidad[100];
    float tarifa;
    int fechas[100];
    int pacientes[100];
    float prima[100];
    char estado[100];
    int numPac;
    float ingresosP;
    float ingresosS;
};

struct StPaciente
{
    int fecha;
    int codigo;
    char nombre[100];
    float prima;
    char estado;
};

void operator>>(std::ifstream& in, struct StMedico& med);
std::ifstream& operator>>(std::ifstream& in, struct StPaciente& pac);
void operator+(struct StMedico& med, struct StPaciente& pac);
void operator+(struct StMedico& med, int fecha);
void operator-(struct StMedico& med, int fecha);
void operator/(struct StMedico& med, int fecha);
void operator++(struct StMedico& med);
void operator++(struct StMedico& med, int ig);
void operator<<(std::ostream& out, struct StMedico& med);

#endif
