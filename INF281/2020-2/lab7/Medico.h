/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#ifndef INF281_MEDICO_H
#define INF281_MEDICO_H

#include <iostream>

class Paciente;

class Medico {
public:
    friend std::istream& operator>>(std::istream &is, Medico &med);
    friend std::ostream& operator<<(std::ostream &os, const Medico &med);
    void operator+(const Paciente &pac);
    void operator*(int fecha);
    void operator-(int fecha);
    void operator++(int dum);
    Medico();
    ~Medico();

private:
    // info med
    char *codigo;
    char *nombre;
    char *especialidad;
    double tarifa;
    // info pac
    int *fechas;
    int *pacientes;
    double *prima;
    char *estado;
    int numPac;
    double ingresosP;
    double ingresosS;

    void print_pac_atendidos(std::ostream &os) const;
    void print_pac_antender(std::ostream &os) const;
};


#endif //INF281_MEDICO_H
