//
// CODIGO: 20171878
// NOMBRE: TORO VERA CARLOS SANTOS
//

#ifndef INF281_OPERATORS_H
#define INF281_OPERATORS_H

#include "Paciente.h"
#include "Emergencia.h"
#include "Urgencia.h"
#include "Ambulatorio.h"
#include <iostream>

std::istream& operator>>(std::istream &is, Paciente *&pac);
std::ostream& operator<<(std::ostream &os, Paciente *&pac);

#endif //INF281_OPERATORS_H
