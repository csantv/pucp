#ifndef INF281_TUBERIA_HPP
#define INF281_TUBERIA_HPP

#include "Cilindro.hpp"

class Tuberia : public Cilindro {
private:
    double radioInterior;
public:
    double getRadioInterior() const;

    void setRadioInterior(double val);

    double volumen() const override;
    double area() const override;
    void mostrarResultados() const override;
};


#endif //INF281_TUBERIA_HPP
