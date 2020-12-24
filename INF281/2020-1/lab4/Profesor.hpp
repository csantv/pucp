//
// Created by Carlos on 12/10/2020.
//

#ifndef INF281_PROFESOR_HPP
#define INF281_PROFESOR_HPP

#include "Persona.hpp"

class Profesor: public Persona {
public:
    Profesor();
    ~Profesor() override;

    void setCategoria(const char *val);
    void setDedicacion(const char *val);
    void setSeccion(const char *val);
    void setGrado(const char *val);

    void getCategoria(char *ptr) const;
    void getDedicacion(char *ptr) const;
    void getSeccion(char *ptr) const;
    void getGrado(char *ptr) const;

    int getPrioridad() override;
    void read(std::istream &is) override;
    void print(std::ostream &os) override;

private:
    char *categoria;
    char *dedicacion;
    char *seccion;
    char *grado;
};


#endif //INF281_PROFESOR_HPP
