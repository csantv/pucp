/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "Urgencia.h"

Urgencia::Urgencia():
porcUrgencia(0),
porcSeguro(0)
{}

Urgencia::Urgencia(const Urgencia &orig):
Paciente(orig),
porcUrgencia(orig.getPorcUrgencia()),
porcSeguro(orig.getPorcSeguro())
{}

Urgencia::~Urgencia() = default;

double Urgencia::getPorcSeguro() const
{
    return porcSeguro;
}

void Urgencia::setPorcSeguro(double val)
{
    porcSeguro = val;
}

double Urgencia::getPorcUrgencia() const
{
    return porcUrgencia;
}

void Urgencia::setPorcUrgencia(double val)
{
    porcUrgencia = val;
}
