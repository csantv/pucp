/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#ifndef INF281_PACIENTE_H
#define INF281_PACIENTE_H


class Paciente {
public:
    Paciente();
    Paciente(const Paciente &orig);
    ~Paciente();

    int getDni() const;
    void setDni(int dni);

    void getNombre(char *ptr) const;
    void getCodMed(char *ptr) const;

    void setNombre(const char *val);
    void setCodMed(const char *val);

    bool isNull();

private:
    int dni;
    char *nombre;
    char *codMed;
};


#endif //INF281_PACIENTE_H
