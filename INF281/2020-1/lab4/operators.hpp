//
// CODIGO: 20171878
// NOMBRE: TORO VERA CARLOS SANTOS
//

#ifndef INF281_OPERATORS_HPP
#define INF281_OPERATORS_HPP

#include "Persona.hpp"
#include "Alumno.hpp"
#include "Profesor.hpp"
#include <iostream>

std::istream& operator>>(std::istream &is, Persona *&rhs);
std::ostream& operator<<(std::ostream &os, Persona *&rhs);

#endif //INF281_OPERATORS_HPP
