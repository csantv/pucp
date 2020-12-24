/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#ifndef INF281_LISTADEPACIENTES_H
#define INF281_LISTADEPACIENTES_H

#include "Ambulatorio.h"
#include "Urgencia.h"
#include "Emergencia.h"
#include <iostream>

class ListaDePacientes {
public:
    ListaDePacientes();
    ListaDePacientes(const ListaDePacientes &orig);
    ~ListaDePacientes();

    void operator+(const Ambulatorio &rhs);
    void operator+(const Emergencia &rhs);
    void operator+(const Urgencia &rhs);
    friend std::istream& operator>>(std::istream &is, ListaDePacientes &lista);

    int numAmb() const;
    int numUrg() const;
    int numEme() const;

private:
    Ambulatorio *lAmb;
    Urgencia *lUrg;
    Emergencia *lEmer;
};


#endif //INF281_LISTADEPACIENTES_H
