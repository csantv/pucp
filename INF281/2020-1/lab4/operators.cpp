//
// CODIGO: 20171878
// NOMBRE: TORO VERA CARLOS SANTOS
//

#include "operators.hpp"

std::istream &operator>>(std::istream &is, Persona *&rhs) {
    char tipo, _;
    is >> tipo >> _;
    if (tipo == 'A') {
        rhs = new Alumno;
    } else {
        rhs = new Profesor;
    }
    rhs->read(is);
    return is;
}

std::ostream &operator<<(std::ostream &os, Persona *&rhs) {
    rhs->print(os);
    return os;
}
