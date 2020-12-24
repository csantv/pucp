//
// Created by cst on 12/18/20.
//

#ifndef INF281_PERSONA_HPP
#define INF281_PERSONA_HPP

#include <iostream>

class Persona {
private:
    int dni;
    char *nombre;
    double sueldo;
public:
    Persona();
    Persona(const Persona &orig);
    virtual ~Persona();

    int getDni() const;

    void setDni(int dni);

    double getSueldo() const;

    void setSueldo(double sueldo);

    void getNombre(char *ptr) const;
    void setNombre(const char *val);

    Persona& operator=(const Persona &orig);
};

std::istream& operator>>(std::istream &is, Persona &rhs);
std::ostream& operator<<(std::ostream &os, const Persona &rhs);

#endif //INF281_PERSONA_HPP
