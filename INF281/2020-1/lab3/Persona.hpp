#ifndef INF281_PERSONA_HPP
#define INF281_PERSONA_HPP


class Persona {
public:
    Persona();
    Persona(const Persona &orig);

    void getNombre(char *ptr) const;

    void setNombre(const char *nombre);

    int getCodigo() const;

    void setCodigo(int codigo);

    void getDistrito(char *ptr) const;

    void setDistrito(const char *distrito);

    virtual ~Persona();

private:
    char *nombre;
    int codigo;
    char *distrito;
};


#endif //INF281_PERSONA_HPP
