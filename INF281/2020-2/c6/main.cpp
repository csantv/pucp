#include "Rectangulo.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    Rectangulo rectangulo, rect01("Segundo Rectangulo", 5.9, 10.75);
    Rectangulo *ptr;

    rectangulo.setNombre("Primer Rectangulo");
    rectangulo.setBase(14.78);
    rectangulo.setAltura(25.98);
    rectangulo.imprimeResultados();

    rect01.imprimeResultados();
//    auto ptr = new Rectangulo("PT Rectangulo", 1, 2);
//
//    ptr->imprimeResultados();
//    delete ptr;
    ptr = new Rectangulo[5];
    delete[] ptr;

    return 0;
}
