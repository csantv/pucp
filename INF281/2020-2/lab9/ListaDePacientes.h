//
// CODIGO: 20171878
// NOMBRE: TORO VERA CARLOS SANTOS
//

#ifndef INF281_LISTADEPACIENTES_H
#define INF281_LISTADEPACIENTES_H

#include "NodoPaciente.h"
#include "Paciente.h"

class ListaDePacientes {
public:
    ListaDePacientes();
    virtual ~ListaDePacientes();
    void creaLista(const char *file);
    void imprimeLista(const char *filename);

private:
    void insertar(Paciente *&pac);
    class NodoPaciente *lista;
};


#endif //INF281_LISTADEPACIENTES_H
