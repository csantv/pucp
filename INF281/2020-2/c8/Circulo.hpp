//
// Created by Carlos on 12/3/2020.
//

#ifndef INF281_CIRCULO_HPP
#define INF281_CIRCULO_HPP


class Circulo {
private:
    double radio;
public:
//    Circulo();
//    Circulo(const Circulo &orig);
//    virtual ~Circulo();

    double getRadio() const;

    void setRadio(double radio);

    virtual double area() const;

    double circunferencia() const;

    virtual void mostrarResultados() const;
};


#endif //INF281_CIRCULO_HPP
