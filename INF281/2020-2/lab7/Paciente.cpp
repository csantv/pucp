/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "Paciente.h"
#include <cstring>

using namespace std;;

Paciente::Paciente()
{
    nombre = nullptr;
    fecha = 0;
    codigo = 0;
    prima = 0;
    estado = 0;
}

Paciente::~Paciente()
{
    delete nombre;
}

std::istream& operator>>(std::istream &is, Paciente &pac)
{
    delete pac.nombre;
    char _, buff[200];
    is >> pac.estado >> pac.codigo >> buff >> pac.prima;
    pac.nombre = new char[strlen(buff)+1];
    strcpy(pac.nombre, buff);
    return is;
}

double Paciente::getPrima() const {
    return prima;
}

char Paciente::getEstado() const {
    return estado;
}

int Paciente::getFecha() const {
    return fecha;
}

int Paciente::getCodigo() const {
    return codigo;
}

void Paciente::setFecha(int val) {
    fecha = val;
}
