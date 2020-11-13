//
// Created by cst on 11/12/20.
//

#include "ListaConEnteros.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void *leeEntero(std::ifstream& arch)
{
    int dato, *d;
    arch >> dato;
    if (arch.eof()) return nullptr;
    d = new int{dato};
    return d;
}

int cmpEntero(const void *d1, const void *d2)
{
    int dato1 = *static_cast<int*>(const_cast<void*>(d1));
    int dato2 = *static_cast<int*>(const_cast<void*>(d2));
    return dato1 - dato2;
}

void imprimeEntero(void *d)
{
    int dato = *static_cast<int*>(d);
    cout << setw(4) << dato << endl;
}

void eliminaEntero(void *d)
{
    int *dato = static_cast<int*>(d);
    delete dato;
}