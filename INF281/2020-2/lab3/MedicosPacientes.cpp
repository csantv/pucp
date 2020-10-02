/*
 * NOMBRE: CARLOS SANTOS TORO VERA
 * CODIGO: 20171878
 */

#include <iostream>
#include <iomanip>

#include "MedicosPacientes.h"

using namespace std;

void operator>>(std::ifstream& in, struct StMedico& med)
{
    in >> med.codigo >> med.nombre >> med.especialidad >> med.tarifa;
    med.numPac = 0;
    med.ingresosP = 0;
    med.ingresosS = 0;
}

std::ifstream& operator>>(std::ifstream& in, struct StPaciente& pac)
{
    int dd, mm, yy; char _;
    in >> dd >> _ >> mm >> _ >> yy >> pac.estado >> pac.codigo
        >> pac.nombre >> pac.prima;
    pac.fecha = yy * 10000 + mm * 100 + dd;
    return in;
}

void operator+(struct StMedico& med, struct StPaciente& pac)
{
    int i = med.numPac;
    med.fechas[i] = pac.fecha;
    med.pacientes[i] = pac.codigo;
    med.prima[i] = pac.prima;
    med.estado[i] = pac.estado;
    med.numPac++;
}

void operator+(struct StMedico& med, int fecha)
{
    for (int i = 0; i < med.numPac; ++i) {
        if (med.fechas[i] == fecha) {
            med.estado[i] = 'R';
        }
    }
}

void operator-(struct StMedico& med, int fecha)
{
    int i = 0;
    while (i < med.numPac) {
        if (med.fechas[i] == fecha && med.estado[i] == 'R') {
            // eliminar y reindexar
            for (int j = i; j < med.numPac - 1; ++j) {
                med.fechas[j] = med.fechas[j + 1];
                med.pacientes[j] = med.pacientes[j + 1];
                med.prima[j] = med.prima[j + 1];
                med.estado[j] = med.estado[j + 1];
            }
            med.numPac--;
            continue;
        }
        i++;
    }
}

void operator/(struct StMedico& med, int fecha)
{
    int i = 0;
    while (i < med.numPac) {
        if (med.fechas[i] < fecha && med.estado[i] == 'A') {
            // eliminar y reindexar
            for (int j = i; j < med.numPac - 1; ++j) {
                med.fechas[j] = med.fechas[j + 1];
                med.pacientes[j] = med.pacientes[j + 1];
                med.prima[j] = med.prima[j + 1];
                med.estado[j] = med.estado[j + 1];
            }
            med.numPac--;
            continue;
        }
        i++;
    }
}

void operator++(struct StMedico& med)
{
    med.ingresosS = 0;
    med.ingresosP = 0;
    for (int i = 0; i < med.numPac; ++i) {
        if (med.estado[i] == 'A') {
            float prima = med.prima[i];
            med.ingresosP += prima * med.tarifa / 100;
            med.ingresosS += (100 - prima) * med.tarifa / 100;
        }
    }
}

void operator++(struct StMedico& med, int ig)
{
    ++med;
}

void show_atend(ostream& out, struct StMedico& med)
{
    int j = 1;
    for (int i = 0; i < med.numPac; ++i) {
        if (med.estado[i] == 'A') {
            int dd = med.fechas[i] % 100, mm = (med.fechas[i] / 100) % 100, yy = (med.fechas[i] / 10000);
            float pagop = med.prima[i] * med.tarifa / 100, pagos = (100 - med.prima[i]) * med.tarifa / 100;
            out << j << ")     " << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << yy
                << "    " << med.pacientes[i] << right << setfill(' ') << setw(12) << pagop
                << right << setfill(' ') << setw(9) << pagos << endl;
            j++;
        }
    }
}

void show_reserv(ostream& out, struct StMedico& med)
{
    int j = 1;
    for (int i = 0; i < med.numPac; ++i) {
        if (med.estado[i] == 'R') {
            int dd = med.fechas[i] % 100, mm = (med.fechas[i] / 100) % 100;
            out << j << ")     " << setfill('0') << setw(2) << dd << "/" << setw(2) << mm
                << "         " << med.pacientes[i] << endl;
            j++;
        }
    }
}

void operator<<(std::ostream& out, struct StMedico& med)
{
    out << "Medico: " << med.nombre << endl << "Codigo: " << med.codigo << endl << "Especialidad: "
        << med.especialidad << endl << "Honorarios por cita: " << fixed << setprecision(2) << med.tarifa << endl;
    out << setfill('=') << setw(48) << "" << endl << "Pacientes atendidos:" << endl << setfill('-')
        << setw(48) << "" << endl << "No.    Fecha         Paciente    Pago     Seguro" << endl;
    show_atend(out, med);
    out << setfill('=') << setw(48) << "" << endl << "Pacientes por atender:" << endl << setfill('-')
        << setw(48) << "" << endl << "No.    Fecha         Paciente" << endl;
    show_reserv(out, med);
    out << setfill('=') << setw(48) << "" << endl;
    out << "Monto total recibido por pacientes:" << setfill(' ') << right << fixed << setw(10) << med.ingresosP
        << endl << "Monto a solicitar al seguro:" << setfill(' ') << right << fixed << setw(17) << med.ingresosS
        << endl;
}