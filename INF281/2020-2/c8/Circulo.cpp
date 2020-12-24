#include "Circulo.hpp"
#include <iostream>
#include <iomanip>

#define M_PI 3.1416

using namespace std;

double Circulo::getRadio() const {
    return radio;
}

void Circulo::setRadio(double val) {
    radio = val;
}

double Circulo::area() const
{
    return M_PI * radio * radio;
}

double Circulo::circunferencia() const
{
    return 2 * M_PI * radio;
}

void Circulo::mostrarResultados() const
{
    cout << setprecision(2) << fixed
         << "Radio:     " << setw(10) << radio << endl
         << "Area:      " << setw(10) << area() << endl
         << "Perimetro: " << setw(10) << circunferencia() << endl;
}
