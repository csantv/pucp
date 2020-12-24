//
// Created by Carlos on 12/10/2020.
//

#ifndef INF281_PERSONA_HPP
#define INF281_PERSONA_HPP

#include <iostream>

class Persona {
public:
    Persona();
    virtual ~Persona();

    void setNombre(const char *val);
    void setDistrito(const char *val);
    void setCodigo(int val);

    void getNombre(char *ptr) const;
    void getDistrito(char *ptr) const;
    int getCodigo() const;

    static void copystr(char *&dest, const char *src);
    void setInfo(std::istream &is);

    virtual int getPrioridad() = 0;
    virtual void read(std::istream &is) = 0;
    virtual void print(std::ostream &os) = 0;

private:
    char *nombre;
    int codigo;
    char *distrito;
};


#endif //INF281_PERSONA_HPP
