#include "ClaseRectangulo.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    ClaseRectangulo rectangulo, rect01;

    rectangulo.inicializarNombre();
    rectangulo.setNombre("Primer Rectangulo");
    rectangulo.setBase(14.78);
    rectangulo.setAltura(25.98);
    rectangulo.imprimeResultados();

    return 0;
}
