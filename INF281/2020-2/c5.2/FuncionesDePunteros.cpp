#include <iostream>
#include <cstring>

using namespace std;

#include "FuncionesDePunteros.h"

using namespace std;

void leerNombres(char **& nombres, int& numDat, const char* nombArch)
{
    char *buff[500], *nomb;
    numDat = 0;
    ifstream arch (nombArch, ios::in);
    if (!arch) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    while (true) {
        nomb = leeCadena(arch);
        if (nomb == nullptr) break;
        buff[numDat] = nomb;
        numDat++;
    }
    nombres = new char* [numDat];
    for (int i = 0; i < numDat; ++i) {
        nombres[i] = buff[i];
    }
}

char* leeCadena(std::ifstream &archNomb)
{
    char cadena[500], *cad;
    archNomb.getline(cadena, 500);
    if (archNomb.eof()) return nullptr;
    cad = new char [strlen(cadena) + 1];
    strcpy(cad, cadena);
    return cad;
}

void ordenar(char** nombres, int izq, int der)
{
    int limite;
    if (izq >= der) return;
    cambiar(nombres, izq, (izq + der) / 2);
    limite = izq;
    for (int i = izq + 1; i <= der; ++i) {
        if (strcmp(nombres[i], nombres[izq]) < 0) {
            cambiar(nombres, ++limite, i);
        }
    }
    cambiar(nombres, izq, limite);
    ordenar(nombres, izq, limite - 1);
    ordenar(nombres, limite + 1, der);
}

void cambiar(char **nombres, int i, int k)
{
    char* aux = nombres[i];
    nombres[i] = nombres[k];
    nombres[k] = aux;
}

void imprimir(char** nombres, int numDat, const char* nombArch)
{
    ofstream archNomb (nombArch, ios::out);
    if (!archNomb) {
        cout << "ERROR: No se pudo abrir el archivo." << nombArch << endl;
        exit(1);
    }
    for (int i = 0; i < numDat; ++i) {
        cout << nombres[i] << endl;
    }
}