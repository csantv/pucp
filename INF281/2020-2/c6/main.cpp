#include "Rectangulo.hpp"
#include "Cadena.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    Cadena cad1 ("Carlos Toro Vera");
    Cadena cad2 ("Awebo");

    cad1.print();
    cad2.print();

    cad1.swap(cad2);

    cad1.print();
    cad2.print();

    Cadena cad3;
    cad3 = cad1 + cad2;

    cad3.print();
    return 0;
}
