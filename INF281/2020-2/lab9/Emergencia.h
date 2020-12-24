//
// CODIGO: 20171878
// NOMBRE: TORO VERA CARLOS SANTOS
//

#ifndef INF281_EMERGENCIA_H
#define INF281_EMERGENCIA_H

#include "Paciente.h"

class Emergencia: public Paciente {
public:
    Emergencia();
    Emergencia(const Emergencia &orig);

    ~Emergencia() override;
    void leer(std::istream &is) override;
    void imprimir(std::ostream &os) override;
    int prioridad() override;
    bool usaSeguro() override;

    int getTelefonoRef() const;

    void setTelefonoRef(int val);

    void getNombreRef(char *ptr) const;

    void setNombreRef(const char *val);

private:
    int telefonoRef;
    char *nombreRef;
};


#endif //INF281_EMERGENCIA_H
