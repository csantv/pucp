#include "PriorityQueuePacientes.hpp"
#include "PriorityQueue.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

enum PAC {DNI, NOMBRE, TIPO, CODIGO, TARIFA, DESC};

int get_prio(char tipo)
{
    if (tipo == 'E') return 3;
    if (tipo == 'U') return 2;
    if (tipo == 'A') return 1;
    return -1;
}

const char* get_tipo(char tipo)
{
    if (tipo == 'E') return "Emergencia";
    if (tipo == 'U') return "Urgencia";
    if (tipo == 'A') return "Ambulatorio";
    return nullptr;
}

double get_tarifa(int codigo)
{
    ifstream file = iopen_file("Tarifas.txt");
    int rcod; double tarif;
    while (true) {
        file >> rcod >> tarif;
        if (file.eof()) break;
        if (rcod == codigo) return tarif;
    }
    return 0;
}

double get_pago(void *pac)
{
    void **reg = static_cast<void**>(pac);
    char tipo = *static_cast<char*>(reg[TIPO]);
    double tarifa = get_tarifa(*static_cast<int*>(reg[CODIGO]));
    double porc = *static_cast<double*>(reg[TARIFA]);
    double desc = *static_cast<double*>(reg[DESC]);
    if (tipo == 'E') return 0;
    if (tipo == 'U') {
        return (porc * tarifa / 100) * (100 - desc) / 100;
    }
    if (tipo == 'A') {
        return porc * tarifa / 100;
    }
    return -1;
}

void cargar_cola(void *&cola)
{
    ifstream file = iopen_file("Pacientes.csv");
    int dni, codigo; char nombre[100], tipo, _; double tarifa = 0, descuento = 0;
    void *reg;
    while (true) {
        file >> dni >> _;
        if (file.eof()) break;
        file.getline(nombre, 100, ',');
        file >> tipo >> _ >> codigo >> _;
        if (tipo == 'U') {
            file >> tarifa >> _ >> descuento >> _;
        } else if (tipo == 'A') {
            file >> tarifa >> _;
        }
        reg = get_pac_reg(dni, nombre, tipo, codigo, tarifa, descuento);
        encolar(cola, new int {get_prio(tipo)}, reg, comp_pac);
    }
}

void *get_pac_reg(int dni, char *nombre, char tipo, int codigo, double tarifa, double descuento)
{
    void **reg = new void*[6];
    reg[DNI] = new int{dni};
    reg[NOMBRE] = new char[strlen(nombre) + 1];
    strcpy(static_cast<char*>(reg[NOMBRE]), nombre);
    reg[TIPO] = new char {tipo};
    reg[CODIGO] = new int {codigo};
    reg[TARIFA] = new double {tarifa};
    reg[DESC] = new double {descuento};
    return reg;
}

int comp_pac(const void* a, const void* b)
{
    void **regA = static_cast<void**>(const_cast<void*>(a));
    void **regB = static_cast<void**>(const_cast<void*>(b));
    int prioA = *static_cast<int*>(regA[PRIO]);
    int prioB = *static_cast<int*>(regB[PRIO]);
    return prioA - prioB;
}

void atender_pacientes(void *&cola)
{
    ofstream reporte = oopen_file("ReporteAtencionPacientes.txt");
    reporte << setw(30) << setfill(' ') << "" << "ATENCION DE PACIENTES" << endl
            << setw(80) << setfill('=') << "" << endl
            << "No.     DNI" << setfill(' ') << setw(8) << ""
            << setw(40) << left << "Paciente" << "Especialidad     Pago"
            << setw(7) << "" << "Tipo" << endl;
    double total = 0; int i = 0;
    while (true) {
        void **nodo = static_cast<void**>(desencolar(cola));
        if (!nodo) break;
        void **nododato = static_cast<void**>(nodo[DATO]);
        void **reg = static_cast<void**>(nododato[VAL]);
        reporte << setfill(' ') << setw(3) << right << ++i << ") ";
        total += imprime_paciente(reporte, reg);
    }
    reporte << setw(80) << setfill('=') << "" << endl
            << "Total cobrado: " << fixed << setprecision(2) << total << endl;
}

double imprime_paciente(ofstream &reporte, void *pac)
{
    void **reg = static_cast<void**>(pac);
    double pago = get_pago(pac);
    reporte << setfill(' ') << setw(3) << ""
            << setw(8) << left << *static_cast<int*>(reg[DNI])
            << setw(3) << "" << setw(40) << left << static_cast<char*>(reg[NOMBRE])
            << "    " << *static_cast<int*>(reg[CODIGO]) << setw(15) << fixed
            << right << setprecision(2) << pago << setw(5) << ""
            << get_tipo(*static_cast<char*>(reg[TIPO])) << endl;
    return pago;
}

ifstream iopen_file(const char* name, ios_base::openmode mode)
{
    ifstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}

ofstream oopen_file(const char* name, ios_base::openmode mode)
{
    ofstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}