/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#ifndef INF281_EMERGENCIA_H
#define INF281_EMERGENCIA_H

#include "Paciente.h"

class Emergencia: public Paciente {
public:
    Emergencia();
    Emergencia(const Emergencia &orig);
    ~Emergencia();

    int getTelefonoRef() const;

    void setTelefonoRef(int val);

    void getNombreRef(char *ptr) const;

    void setNombreRef(const char *val);

private:
    int telefonoRef;
    char *nombreRef;
};


#endif //INF281_EMERGENCIA_H
