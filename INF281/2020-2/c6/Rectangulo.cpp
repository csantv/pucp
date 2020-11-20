#include "Rectangulo.hpp"

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

static int i = 1;

void Rectangulo::setBase(double value)
{
    base = value;
}

void Rectangulo::setAltura(double value)
{
    altura = value;
}

double Rectangulo::getBase() const
{
    return base;
}

double Rectangulo::getAltura() const
{
    return altura;
}

void Rectangulo::leeDatos()
{
    cout << "Ingrese la base: ";
    cin >> base;
    cout << "Ingrese la altura: ";
    cin >> altura;
}

void Rectangulo::imprimeDatos()
{
    cout << "Nombre:    " << nombre << endl
         << setprecision(2) << fixed
         << "Base :     " << base << endl
         << "Altura:    " << altura << endl;

}

double Rectangulo::area() const
{
    return base * altura;
}

double Rectangulo::perimetro() const
{
    return 2 * (base + altura);
}

void Rectangulo::imprimeResultados()
{
    imprimeDatos();
    cout << "Area:      " << area() << endl;
    cout << "Perimetro: " << perimetro() << endl;
}

void Rectangulo::getNombre(char *cad) const
{
    strcpy(cad, nombre);
}

void Rectangulo::setNombre(const char *value)
{
    delete nombre;
    nombre = new char[strlen(value) + 1];
    strcpy(nombre, value);
}

Rectangulo::Rectangulo():
base(0),
altura(0),
nombre(nullptr)
{}

Rectangulo::Rectangulo(const char* nombre, double base, double altura):
base(base),
altura(altura),
nombre(nullptr)
{
    setNombre(nombre);
}

Rectangulo::Rectangulo(const Rectangulo &rhs):
base(rhs.getBase()),
altura(rhs.getAltura()),
nombre(nullptr)
{
    char n[100];
    rhs.getNombre(n);
    setNombre(n);
}

Rectangulo::~Rectangulo()
{
    delete nombre;
    cout << "Destructor (" << i << ")" << endl;
    i++;
}
