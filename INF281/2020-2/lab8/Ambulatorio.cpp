/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "Ambulatorio.h"

Ambulatorio::Ambulatorio():
porcSeguro(0),
Paciente()
{}

Ambulatorio::Ambulatorio(const Ambulatorio &orig):
porcSeguro(orig.getPorcSeguro()),
Paciente(orig)
{}

double Ambulatorio::getPorcSeguro() const
{
    return porcSeguro;
}

void Ambulatorio::setPorcSeguro(double val)
{
    porcSeguro = val;
}
