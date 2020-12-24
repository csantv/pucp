#ifndef INF281_PROFESOR_HPP
#define INF281_PROFESOR_HPP

#include "Persona.hpp"

class Profesor : public Persona {
public:
    Profesor();
    Profesor(const Profesor &orig);
    ~Profesor() override;

    void getCategoria(char *ptr) const;
    void getDedicacion(char *ptr) const;
    void getSeccion(char *ptr) const;
    void getGrado(char *ptr) const;

    void setCategoria(const char *val);
    void setDedicacion(const char *val);
    void setSeccion(const char *val);
    void setGrado(const char *val);

private:
    char *categoria;
    char *dedicacion;
    char *seccion;
    char *grado;

    static void copystr(char *&dest, const char *orig);
};


#endif //INF281_PROFESOR_HPP
