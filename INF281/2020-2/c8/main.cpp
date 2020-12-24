#include <iostream>
#include <iomanip>
#include "Circulo.hpp"
#include "Cilindro.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Circulo circulo{};

    circulo.setRadio(24.03);
    circulo.mostrarResultados();

    cout << endl;

    Cilindro cilindro{};
    cilindro.setRadio(24.83);
    cilindro.setAltura(12.32);
    cilindro.mostrarResultados();
    return 0;
}
