#include "ClaseRectangulo.hpp"

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

void ClaseRectangulo::setBase(double value)
{
    base = value;
}

void ClaseRectangulo::setAltura(double value)
{
    altura = value;
}

double ClaseRectangulo::getBase() const
{
    return base;
}

double ClaseRectangulo::getAltura() const
{
    return altura;
}

void ClaseRectangulo::leeDatos()
{
    cout << "Ingrese la base: ";
    cin >> base;
    cout << "Ingrese la altura: ";
    cin >> altura;
}

void ClaseRectangulo::imprimeDatos()
{
    cout << setprecision(2) << fixed
         << "Base :     " << base << endl
         << "Altura:    " << altura << endl
         << "Nombre:    " << nombre << endl;

}

double ClaseRectangulo::area() const
{
    return base * altura;
}

double ClaseRectangulo::perimetro() const
{
    return 2 * (base + altura);
}

void ClaseRectangulo::imprimeResultados()
{
    imprimeDatos();
    cout << "Area:      " << area() << endl;
    cout << "Perimetro: " << perimetro() << endl;
}

void ClaseRectangulo::getNombre(char *cad) const
{
    strcpy(cad, nombre);
}

void ClaseRectangulo::setNombre(const char *value)
{
    delete nombre;
    nombre = new char[strlen(value) + 1];
    strcpy(nombre, value);
}

void ClaseRectangulo::inicializarNombre()
{
    nombre = nullptr;
}


