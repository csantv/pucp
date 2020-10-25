#include "func-aux.h"
#include "Bib_Func_Preg2.h"

#include <iomanip>
#include <iostream>

#define INCREMENTOS 5

using namespace std;

void leerPrestamos(void *&usuarios)
{
    ifstream prest = iopen_file("Perstamos.csv", ios::in);
    int codigo; char _, codLibro[7], fecha[11];
    init_num_prestamos(usuarios);
    while (true) {
        prest >> codigo >> _;
        if (prest.eof() || prest.fail()) break;
        prest.getline(codLibro, 8, ',');
        prest.getline(fecha, 12, '\r');
        prest >> ws;
        insertar_prestamo(usuarios, codigo, codLibro, fecha);
    }
}

void init_num_prestamos(void *&usuarios)
{
    void **&usr = reinterpret_cast<void**&>(usuarios);
    for (int i = 0; usr[i] != nullptr; ++i) {
        void **&reg = reinterpret_cast<void**&>(usr[i]);
        reg[3] = new int {0};
    }
}

void insertar_prestamo(void *&usuarios, int codigo, char *codLibro, char *fecha)
{
    int ind = buscar_usuario(usuarios, codigo);
    void **&usr = reinterpret_cast<void**&>(usuarios);
    void **&reg = reinterpret_cast<void**&>(usr[ind]);
    void **&prestArr = reinterpret_cast<void**&>(reg[2]);
    if (!prestArr) prestArr = new void*();
    int numEl = inc_num_prestamos(usuarios, ind);
    void **prest = new void*[2];
    prest[0] = new char[strlen(codLibro) + 1];
    prest[1] = new char[strlen(fecha) + 1];
    strcpy(reinterpret_cast<char*>(prest[0]), codLibro);
    strcpy(reinterpret_cast<char*>(prest[1]), fecha);
    if ((numEl - 1) % INCREMENTOS == 0) {   // usar aux
        void **aux = new void*[numEl + INCREMENTOS]();
        for (int i = 0; i < numEl; ++i) aux[i] = prestArr[i];
        aux[numEl-1] = prest;
        prestArr = aux;
    } else {
        prestArr[numEl-1] = prest;
    }
}

int inc_num_prestamos(void *&usuarios, int ind)
{
    void **&reg = reinterpret_cast<void**&>(reinterpret_cast<void**&>(usuarios)[ind]);
    reg[3] = new int {*reinterpret_cast<int*>(reg[3]) + 1};
    return *reinterpret_cast<int*>(reg[3]);
}

int buscar_usuario(void *usuarios, int codigo)
{
    int cod = -1;
    void **usr = reinterpret_cast<void**>(usuarios);
    for (int i = 0; usr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void **>(usr[i]);
        if (*reinterpret_cast<int *>(reg[0]) == codigo) cod = i;
    }
    return cod;
}

void imprimirPrestamos(void *usuarios)
{
    ofstream reporte = oopen_file("ReportePrestamos.txt", ios::out);
    void **usr = reinterpret_cast<void**>(usuarios);
    reporte << "REGISTRO DE PRESTAMOS DE LA BIBLIOTECA" << endl;
    for (int i = 0; usr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(usr[i]);
        int codigo = *reinterpret_cast<int*>(reg[0]);
        char *nombre = reinterpret_cast<char*>(reg[1]);
        void **prestArr = reinterpret_cast<void**>(reg[2]);
        int numPrest = *reinterpret_cast<int*>(reg[3]);
        for (int j = 0; j < numPrest; ++j) {
            void **prest = reinterpret_cast<void**>(prestArr[j]);
            char *codLibro = reinterpret_cast<char*>(prest[0]);
            char *fecha = reinterpret_cast<char*>(prest[1]);
            reporte << codigo << " " << nombre << " " << codLibro << " " << fecha << endl;
        }
    }
}