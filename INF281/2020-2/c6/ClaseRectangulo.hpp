//
// Created by cst on 11/17/20.
//

#ifndef INF281_CLASERECTANGULO_HPP
#define INF281_CLASERECTANGULO_HPP

class ClaseRectangulo {
private:
    char *nombre;
    double base;
    double altura;
public:
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
    void inicializarNombre();
};


#endif //INF281_CLASERECTANGULO_HPP
