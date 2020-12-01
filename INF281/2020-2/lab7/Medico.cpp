/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "Medico.h"
#include "Paciente.h"
#include "func-aux.h"
#include <cstring>
#include <iomanip>

using namespace std;

Medico::Medico()
{
    codigo = new char[7];
    nombre = nullptr;
    especialidad = nullptr;
    fechas = nullptr;
    pacientes = nullptr;
    prima = nullptr;
    estado = nullptr;
    tarifa = 0;
    numPac = 0;
    ingresosP = 0;
    ingresosS = 0;
}

Medico::~Medico()
{
    delete codigo;
    delete especialidad;
    delete nombre;
    delete fechas;
    delete pacientes;
    delete prima;
    delete estado;
}

std::istream& operator>>(std::istream &is, Medico &med)
{
    delete med.nombre;
    delete med.especialidad;

    char buff[100];
    is >> med.codigo >> buff;
    med.nombre = new char[strlen(buff)+1];
    strcpy(med.nombre, buff);
    is >> buff;
    med.especialidad = new char[strlen(buff)+1];
    strcpy(med.especialidad, buff);
    is >> med.tarifa;
    return is;
}

std::ostream& operator<<(std::ostream &os, const Medico &med)
{
    os << "Medico: " << med.nombre << endl;
    os << "Codigo: " << med.codigo << endl;
    os << "Especialidad: " << med.especialidad << endl;
    os << "Honorarios por cita: " << fixed << setprecision(2) << med.tarifa << endl;
    med.print_pac_atendidos(os);
    med.print_pac_antender(os);
    os << setfill('=') << setw(40) << "" << endl;
    os << "Monto total recibido por pacientes: " << setfill(' ') << right << setw(8)
        << fixed << setprecision(2) << med.ingresosP << endl;
    os << "Monto a solicitar al seguro: " << right << setw(15)
        << fixed << setprecision(2) << med.ingresosS << endl;
    return os;
}

void Medico::operator+(const Paciente &pac)
{
    append_double(prima, pac.getPrima());
    append_int(fechas, pac.getFecha());
    append_int(pacientes, pac.getCodigo());
    append_char(estado, pac.getEstado());
    numPac++;
}

void Medico::operator*(int fecha)
{
    for (int i = 0; i < numPac; ++i) {
        if (fechas[i] == fecha && estado[i] == 'R') estado[i] = 'A';
    }
}

void Medico::operator-(int fecha)
{
    for (int i = 0; i < numPac; ++i) {
        if (fechas[i] == fecha && estado[i] == 'R') estado[i] = 'E';
    }
}

void Medico::operator++(int dum)
{
    for (int i = 0; i < numPac; ++i) {
        if (estado[i] != 'A') continue;
        ingresosS += (prima[i]/100) * tarifa;
        ingresosP += (1 - prima[i]/100) * tarifa;
    }
}

void Medico::print_pac_atendidos(std::ostream &os) const
{
    int n = 0;
    os << setfill('=') << setw(40) << "" << endl;
    os << "Pacientes atendidos:" << endl;
    os << setfill('-') << setw(40) << "" << endl;
    os << "No.   Fecha" << setfill(' ') << setw(8) << "" << "Paciente"
       << "    Pago     Seguro" << endl;
    for (int i = 0; i < numPac; ++i) {
        if (estado[i] != 'A') continue;
        double pagoS = (prima[i]/100)*tarifa,
                pagoP = (1 - prima[i]/100) * tarifa;
        int yy = fechas[i] / 10000, mm = (fechas[i] % 10000) / 100, dd = (fechas[i] % 100);
        os << ++n << ")    "
           << setfill('0') << setw(2) << dd << "/" << setfill('0') << setw(2)
           << mm << "/" << yy << "   " << pacientes[i]
           << setfill(' ') << setw(12) << right << fixed << setprecision(2) << pagoP
           << setw(9) << right << fixed << setprecision(2) << pagoS << endl;
    }
}

void Medico::print_pac_antender(std::ostream &os) const
{
    int n = 0;
    os << setfill('=') << setw(40) << "" << endl;
    os << "Pacientes por atender:" << endl;
    os << setfill('-') << setw(40) << "" << endl;
    os << "No.   Fecha" << setfill(' ') << setw(8) << "" << "Paciente" << endl;
    for (int i = 0; i < numPac; ++i) {
        if (estado[i] != 'R') continue;
        int mm = (fechas[i] % 10000) / 100, dd = (fechas[i] % 100);
        os << ++n << ")    "
           << setfill('0') << setw(2) << dd << "/" << setfill('0')
           << setw(2) << mm << " " << setw(7) << setfill(' ') << "" << pacientes[i] << endl;
    }
}
