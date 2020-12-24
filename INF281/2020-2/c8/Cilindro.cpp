#include "Cilindro.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

double Cilindro::getAltura() const {
    return altura;
}

void Cilindro::setAltura(double val) {
    altura = val;
}

double Cilindro::volumen() const
{
    return Circulo::area() * altura;
}

double Cilindro::area() const
{
    return 2 * Circulo::area() + Circulo::circunferencia()*altura;
}

void Cilindro::mostrarResultados() const
{
    cout << setprecision(2) << fixed
         << "Radio:              " << setw(10) << getRadio() << endl
         << "Altura:             " << setw(10) << altura << endl
         << "Volumen:            " << setw(10) << volumen() << endl
         << "Area de la sup.:    " << setw(10) << area() << endl
         << "Area de la base:    " << setw(10) << Circulo::area() << endl
         << "Circunferencia:     " << setw(10) << circunferencia() << endl;
}
