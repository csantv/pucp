/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#ifndef INF281_PACIENTE_H
#define INF281_PACIENTE_H

#include <iostream>

class Paciente {
public:
    Paciente();

    ~Paciente();

    friend std::istream& operator>>(std::istream &is, Paciente &pac);

    double getPrima() const;

    char getEstado() const;

    int getFecha() const;

    int getCodigo() const;

    void setFecha(int val);

private:
    int fecha;
    int codigo;
    char *nombre;
    double prima;
    char estado;
};


#endif //INF281_PACIENTE_H
