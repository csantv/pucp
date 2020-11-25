//
// Created by cst on 11/17/20.
//

#ifndef INF281_RECTANGULO_HPP
#define INF281_RECTANGULO_HPP

class Rectangulo {
private:
    char *nombre;
    double base;
    double altura;
public:
    Rectangulo();
    Rectangulo(const char* nombre, double base, double altura);
    Rectangulo(const Rectangulo& rhs);
    ~Rectangulo();

    void setBase(double value);
    void setAltura(double value);
    double getBase() const;
    double getAltura() const;
    double area() const;
    double perimetro() const;

    void leeDatos();
    void imprimeDatos();
    void imprimeResultados();

    void getNombre(char *cad) const;
    void setNombre(const char *value);
};


#endif //INF281_RECTANGULO_HPP
