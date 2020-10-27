/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "FuncionesEx01_20202_Preg02.h"

#include <iostream>
#include <iomanip>

#define INCREMENTOS 5

using namespace std;

void leerDatos(char **&clientes, int ***&productos, char ***&strProductos)
{
    ifstream file = iopen_file("pedidos.csv");
    int ruc; char nomtienda[50], _; clientes = nullptr; productos = nullptr; strProductos = nullptr;
    while (true) {
        file >> ruc >> _;
        if (file.eof()) break;
        file.getline(nomtienda, 50, ',');
        int clientind = insert_cliente(clientes, nomtienda);
        insert_intproductos(productos);
        insert_strprod(strProductos);
        while (true) {
            int dd, mm, yy, codprod, cantprod; char nomprod[50];
            file >> yy >> _ >> mm >> _ >> dd >> _ >> codprod >> _;
            file.getline(nomprod, 50, ',');
            file >> ws;
            file >> ws >> cantprod >> noskipws >> _ >> skipws;
            int prodind = insert_intproductos(productos, codprod, cantprod, clientind);
            insert_strprod(strProductos, nomprod, clientind, prodind);
            if (_ == '\n') break;
        }
    }
}

void insert_strprod(char ***&strProductos, char* nomprod, int clientid, int prodind)
{
    if (!strProductos[clientid]) strProductos[clientid] = new char*();
    int numEl = 0; while (strProductos[clientid][numEl]) numEl++;
    if (!strProductos[clientid][prodind]) {    // no existe producto
        if ((numEl+1) % INCREMENTOS == 1) {
            char **aux = new char*[numEl+1+INCREMENTOS]();
            for (int i = 0; i < numEl; ++i) aux[i] = strProductos[clientid][i];
            aux[numEl] = new char[strlen(nomprod)+1];
            strcpy(aux[numEl], nomprod);
            strProductos[clientid] = aux;
        } else {
            strProductos[clientid][numEl] = new char[strlen(nomprod)+1];
            strcpy(strProductos[clientid][numEl], nomprod);
        }
    }
}

void insert_strprod(char ***&strProductos)
{
    if (!strProductos) strProductos = new char**();
    int numEl = 0; while (strProductos[numEl]) numEl++;
    if ((numEl+1) % INCREMENTOS ==1) {
        char ***aux = new char**[numEl+1+INCREMENTOS]();
        for (int i = 0; i < numEl; ++i) aux[i] = strProductos[i];
        strProductos = aux;
    }
}

int insert_cliente(char **&clientes, char *nomcliente)
{
    if (!clientes) clientes = new char*();
    int numEl = 0; while (clientes[numEl]) numEl++;
    if ((numEl + 1) % INCREMENTOS == 1) {
        char **aux = new char*[numEl+1+INCREMENTOS]();
        for (int i = 0; i < numEl; ++i) aux[i] = clientes[i];
        aux[numEl] = new char[strlen(nomcliente)+1];
        strcpy(aux[numEl], nomcliente);
        clientes = aux;
    } else {
        clientes[numEl] = new char[strlen(nomcliente) + 1];
        strcpy(clientes[numEl], nomcliente);
    }
    return numEl;
}

int insert_intproductos(int ***&productos, int codprod, int cantprod, int clientind)
{
    if (!productos[clientind]) productos[clientind] = new int*();
    int numEl = 0; while (productos[clientind][numEl]) numEl++;
    for (int i = 0; productos[clientind][i]; ++i) { // verificar que no exista el producto
        if (productos[clientind][i][0] == codprod) {
            productos[clientind][i][1] += cantprod;
            return i;
        }
    }
    if ((numEl+1) % INCREMENTOS ==1) {
        int **aux = new int*[numEl+1+INCREMENTOS]();
        for (int i = 0; i < numEl; ++i) aux[i] = productos[clientind][i];
        aux[numEl] = new int[2] {codprod, cantprod};
        delete productos[clientind];
        productos[clientind] = aux;
    } else {
        productos[clientind][numEl] = new int[2]{codprod, cantprod};
    }
    return numEl;
}

int insert_intproductos(int ***&productos)
{
    if (!productos) productos = new int**();
    int numEl = 0; while (productos[numEl]) numEl++;
    if ((numEl+1) % INCREMENTOS ==1) {
        int ***aux = new int**[numEl+1+INCREMENTOS]();
        for (int i = 0; i < numEl; ++i) aux[i] = productos[i];
        productos = aux;
    }
    return numEl;
}

void imprimirDatos(char **clientes, int ***productos, char ***strProductos)
{
    ofstream reporte = oopen_file("ReporteAtencion.txt");
    reporte << setfill(' ') << setw(21) << "" << "REPORTE DE ATENCION" << endl;
    for (int i = 0; clientes[i]; ++i) {
        reporte << "Cliente : " << clientes[i] << endl
                << setfill('=') << setw(90) << "" << endl
                << "  Cod. Producto    " << setfill(' ') << setw(50) << left << "Producto"
                << "Cant. Solicitada  " << endl
                << setfill('=') << setw(90) << "" << endl;
        for (int j = 0; productos[i][j]; ++j) {
            reporte << setfill(' ') << setw(10) << right << productos[i][j][0]
                    << setw(9) << "" << setw(50) << left << strProductos[i][j] << " "
                    << setw(10) << right << productos[i][j][1] << endl;
        }
        reporte << endl;
    }
}

ifstream iopen_file(const char* name, ios_base::openmode mode)
{
    ifstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}

ofstream oopen_file(const char* name, ios_base::openmode mode)
{
    ofstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}

int strlen(const char* arr)
{
    int i = 0;
    while (arr[i]) i++;
    return i;
}

void strcpy(char* dest, const char* src)
{
    while((*dest++ = *src++));
}

int strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}