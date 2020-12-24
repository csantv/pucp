//
// CODIGO: 20171878
// NOMBRE: TORO VERA CARLOS SANTOS
//

#include "operators.h"

std::istream &operator>>(std::istream &is, Paciente *&pac) {
    char tipo, _;
    is >> tipo >> _;
    if (tipo == 'E') {
        pac = new Emergencia;
    } else if (tipo == 'U') {
        pac = new Urgencia;
    } else if (tipo == 'A') {
        pac = new Ambulatorio;
    } else {
        return is;
    }
    pac->leer(is);
    return is;
}

std::ostream &operator<<(std::ostream &os, Paciente *&pac) {
    if (pac != nullptr) pac->imprimir(os);
    return os;
}
