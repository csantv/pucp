#include "Funcioneslaboratorio05.h"
#include "func-aux.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

#define INCREMENTOS 2

using namespace std;

void appendAlmacen(char ***&almacenes, char* codAl, char* oldCodAl, char* codProd)
{
    if (!almacenes) almacenes = new char** {new char*()};
    int numAl = 0; while (almacenes[numAl]) numAl++;
    if (!strcmp(codAl, oldCodAl)) {     // mismo almacen
        int numProd = 0; while (almacenes[numAl-1][numProd]) numProd++;
        char **aux = new char*[numProd + 2]();
        for (int i = 0; i < numProd; ++i) aux[i] = almacenes[numAl - 1][i];
        aux[numProd] = new char[strlen(codProd) + 1];
        strcpy(aux[numProd], codProd);
        almacenes[numAl-1] = aux;
    } else { // nuevo almacen
        char ***aux = new char**[numAl + 2]();
        for (int i = 0; i < numAl; ++i) aux[i] = almacenes[i];
        aux[numAl] = new char*[2]();
        aux[numAl][0] = new char[strlen(codProd) + 1];
        strcpy(aux[numAl][0], codProd);
        almacenes = aux;
    }
}

void leerPalets(char ***&almacenes)
{
    ifstream stock = iopen_file("stock.txt", ios::in);
    char codAl[4], codPal[4], codProd[8], oldCodAl[4] = {0};
    almacenes = nullptr;
    while (true) {
        stock.getline(codAl, 4, ' ');
        stock >> ws;
        stock.getline(codProd, 8, ' ');
        stock >> ws;
        stock.getline(codPal, 4);
        appendAlmacen(almacenes, codAl, oldCodAl, codProd);
        strcpy(oldCodAl, codAl);
        if (stock.eof()) break;
    }
}

void imprimirPalets(char *** const &almacenes)
{
    for (int i = 0; almacenes[i + 1]; ++i) {
        cout << "Almacen " << i + 1 << ":" << endl;
        for (int j = 0; almacenes[i][j]; ++j) {
            cout << almacenes[i][j] << endl;
        }
    }
}

void append_str(char **& arr, char* str)
{
    if (!arr) arr = new char*();
    int numEl = 0; while (arr[numEl]) numEl++;
    char **aux = new char*[numEl+2]();
    for (int i = 0; i < numEl; ++i) aux[i] = arr[i];
    aux[numEl] = new char[strlen(str) + 1];
    strcpy(aux[numEl], str);
    arr = aux;
}

void leerProductos(char **&codigoProd, char **&nombreProd)
{
    ifstream productos = iopen_file("productos.txt", ios::in);
    codigoProd = nullptr; nombreProd = nullptr;
    char codProd[8], nomProd[100];
    while (true) {
        productos.getline(codProd, 8, ',');
        append_str(codigoProd, codProd);
        productos.getline(nomProd, 100);
        append_str(nombreProd, nomProd);
        if (productos.eof()) break;
    }
}

void imprimirProductos(char **&codigoProd, char **&nombreProd)
{
    cout << endl;
    for (int i = 0; codigoProd[i + 1]; ++i) {
        cout << "Codigo: " << codigoProd[i] <<
             setfill(' ') << setw(5) << "" << "Nombre: " << nombreProd[i] << endl;
    }
}

void ordenaproductos(char **&codigoProd, char **&nombreProd)
{
    int numProd = 0;
    while (codigoProd[numProd]) numProd++;
    sort_str(codigoProd, nombreProd, 0, numProd - 2);
}

void sort_str(char **&codigoProd, char **&nombreProd, int izq, int der)
{
    int limite;
    if (izq >= der) return;
    cambiar(codigoProd, nombreProd, izq, (izq + der) / 2);
    limite = izq;
    for (int i = izq + 1; i <= der; ++i) {
        if (strcmp(nombreProd[i], nombreProd[izq]) < 0) {
            cambiar(codigoProd, nombreProd, ++limite, i);
        }
    }
    cambiar(codigoProd, nombreProd, izq, limite);
    sort_str(codigoProd, nombreProd, izq, limite - 1);
    sort_str(codigoProd, nombreProd, limite + 1, der);
}

void cambiar(char **str1, char** str2, int i, int k)
{
    char* aux = str1[i];
    str1[i] = str1[k];
    str1[k] = aux;
    aux = str2[i];
    str2[i] = str2[k];
    str2[k] = aux;
}

void cuentaproductos(char ***&almacenes, char **&codigoProd, char **&nombreProd)
{
    ofstream reporte = oopen_file("reporte.txt", ios::out);
    reporte << "NOMBRE DE PRODUCTO" << setw(40) << setfill(' ') << ""
            << "CODIGO DE PRODUCTO" << setw(20) << ""
            << "CANTIDAD DE PALETS" << endl;
    for (int i = 0; codigoProd[i + 1]; ++i) {
        char* codigo = codigoProd[i];
        int numPalets = 0;
        for (int j = 0; almacenes[j + 1]; ++j) {    // buscar numero de palets
            for (int k = 0; almacenes[j][k]; ++k) {
                if (!strcmp(codigo, almacenes[j][k])) numPalets++;
            }
        }
        reporte << setw(65) << left << nombreProd[i]
                << codigoProd[i] << setw(30) << ""
                << numPalets << endl;
    }
}