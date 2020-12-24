/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#ifndef INF281_URGENCIA_H
#define INF281_URGENCIA_H

#include "Paciente.h"

class Urgencia: public Paciente {
public:
    Urgencia();
    Urgencia(const Urgencia &orig);
    ~Urgencia();

    double getPorcSeguro() const;

    void setPorcSeguro(double val);

    double getPorcUrgencia() const;

    void setPorcUrgencia(double val);

private:
    double porcSeguro;
    double porcUrgencia;
};


#endif //INF281_URGENCIA_H
