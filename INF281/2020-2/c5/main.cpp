#include <iostream>
#include <iomanip>
#include <cstring>

#define INCREMENTO 5

using namespace std;

void leeDatosExactos(int*& datos, int& numDat)
{
    int buff[1000];
    numDat = 0;
    while (true) {
        cin >> buff[numDat];
        if (cin.eof()) break;
        numDat++;
    }
    datos = new int [numDat];
    for (int i = 0; i < numDat; ++i) {
        datos[i] = buff[i];
    }
}

void imprimeDatos(const int* datos, int numDat)
{
    for (int i = 0; i < numDat; ++i) {
        cout << setw(5) << datos[i];
    }
    cout << endl;
}

void leeDatosExactos(int*& datos)
{
    int buff[1000], numDat = 0;
    while (true) {
        cin >> buff[numDat];
        if (cin.eof()) break;
        numDat++;
    }
    buff[numDat] = -1;
    numDat++;
    datos = new int [numDat];
    for (int i = 0; i < numDat; ++i) {
        datos[i] = buff[i];
    }
}

void imprimeDatos(const int* datos)
{
    for (int i = 0; datos[i] != -1; ++i) {
        cout << setw(5) << datos[i];
    }
    cout << endl;
}

void leeDatosExactos(char*& nombre)
{
    char buff[200];
    int numCar;
    cin.getline(buff, 200);
    numCar = strlen(buff);
    nombre = new char [numCar + 1];
    strcpy(nombre, buff);
}

void incrementarEspacios(int *&datos, int numDat, int &cap)
{
    int* aux;
    cap += INCREMENTO;
    if (!datos) {
        datos = new int [cap]; return;
    }
    aux = new int [cap];
    for (int i = 0; i < numDat; ++i) {
        aux[i] = datos[i];
    }
    delete datos;
    datos = aux;
}

void leeDatosPorIncrementos(int *& datos, int& numDat)
{
    int cap = 0, dato;
    numDat = 0;
    datos = nullptr;
    while (true) {
        cin >> dato;
        if (cin.eof()) break;
        if (numDat == cap) incrementarEspacios(datos, numDat, cap);
        datos[numDat] = dato;
        numDat++;
    }
}

void incrementarEspaciosSND(int *&datos, int& numDat, int &cap)
{
    int* aux; cap += INCREMENTO;
    if (!datos) {
        datos = new int [cap];
        datos[0] = -1;
        numDat = 1;
        return;
    }
    aux = new int [cap];
    for (int i = 0; i < numDat; ++i) {
        aux[i] = datos[i];
    }
    delete datos;
    datos = aux;
}

void leeDatosPorIncrementos(int *& datos)
{
    int cap = 0, numDat = 0, dato; datos = nullptr;
    while (true) {
        cin >> dato;
        if (cin.eof()) break;
        if (numDat == cap) incrementarEspaciosSND(datos, numDat, cap);
        datos[numDat] = -1;
        datos[numDat-1] = dato;
        numDat++;
    }
}

int main(int argc, char** argv)
{
    int *datos, numDat;
    char* nombre;
//    leeDatosExactos(datos, numDat);
//    imprimeDatos(datos, numDat);
//    leeDatosExactos(datos);
//    leeDatosExactos(nombre);
//    cout << nombre << endl;
//    imprimeDatos(datos);
//    leeDatosPorIncrementos(datos, numDat);
    leeDatosPorIncrementos(datos);
    imprimeDatos(datos);
    return 0;
}