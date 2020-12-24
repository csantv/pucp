#include "Plantilla.hpp"
#include <iostream>
#include "Persona.hpp"

int main(int argc, char **argv)
{
//    Plantilla<string> xd;
//    xd.setDato("aweqwdasdbsbaf");
//    xd.imprimirDato();
    Plantilla<Persona> objPer;
    objPer.leerDato();
    objPer.imprimirDato();
    return 0;
}