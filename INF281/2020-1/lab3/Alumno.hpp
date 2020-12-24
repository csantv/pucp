#ifndef INF281_ALUMNO_HPP
#define INF281_ALUMNO_HPP

#include "Persona.hpp"

class Alumno : public Persona {
public:
    Alumno();
    Alumno(const Alumno &orig);
    ~Alumno() override;

    int getEscala() const;

    void setEscala(int escala);

    void getEspecialidad(char *ptr) const;

    void setEspecialidad(const char *val);

    void getFacultad(char *ptr) const;

    void setFacultad(const char *val);

private:
    int escala;
    char *especialidad;
    char *facultad;
};


#endif //INF281_ALUMNO_HPP
