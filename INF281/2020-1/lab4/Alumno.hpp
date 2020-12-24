//
// Created by Carlos on 12/10/2020.
//

#ifndef INF281_ALUMNO_HPP
#define INF281_ALUMNO_HPP

#include "Persona.hpp"

class Alumno: public Persona {
public:
    Alumno();
    ~Alumno() override;

    void setEspecialidad(const char *val);
    void setFacultad(const char *val);
    void setEscala(int val);

    int getEscala() const;
    void getEspecialidad(char *ptr) const;
    void getFacultad(char *ptr) const;

    int getPrioridad() override;
    void read(std::istream &is) override;
    void print(std::ostream &os) override;

private:
    int escala;
    char *especialidad;
    char *facultad;
};


#endif //INF281_ALUMNO_HPP
