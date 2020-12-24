#include "Tuberia.hpp"

double Tuberia::getRadioInterior() const {
    return radioInterior;
}

void Tuberia::setRadioInterior(double val) {
    radioInterior = val;
}

double Tuberia::area() const
{
    return Cilindro::area() - 2 * Circulo::area();
}

double Tuberia::volumen() const
{
    return 0;
}

void Tuberia::mostrarResultados() const
{

}
