//
// Created by Carlos on 12/3/2020.
//

#ifndef INF281_CILINDRO_HPP
#define INF281_CILINDRO_HPP

#include "Circulo.hpp"

class Cilindro : public Circulo {
private:
    double altura;
public:
    double getAltura() const;

    void setAltura(double val);

    virtual double volumen() const;

    double area() const override;    // area de la superficie

    void mostrarResultados() const override;
};


#endif //INF281_CILINDRO_HPP
