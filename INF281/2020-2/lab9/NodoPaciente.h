//
// CODIGO: 20171878
// NOMBRE: TORO VERA CARLOS SANTOS
//

#ifndef INF281_NODOPACIENTE_H
#define INF281_NODOPACIENTE_H

#include "ListaDePacientes.h"
#include "Paciente.h"

class NodoPaciente {
public:
    NodoPaciente();
    ~NodoPaciente();
    friend class ListaDePacientes;

private:
    class Paciente *dato;
    class NodoPaciente *sig;
};


#endif //INF281_NODOPACIENTE_H
