#include "FuncionesParte01Ex1.h"
#include "func-aux.h"

#include <iomanip>
#include <iostream>

using namespace std;

void leeVentas(void *&ventas)
{
    ifstream file = iopen_file("ventas.csv", ios::in);
    int fecha, ruc, cantidad; char codigo[8], _;
    ventas = nullptr;
    while (true) {
        file >> fecha >> _ >> ruc >> _;
        if (file.eof()) break;
        file.getline(codigo, 9, ',');
        file >> cantidad;
        insert_venta(ventas, fecha, ruc, codigo, cantidad);
    }
}

void insert_venta(void *&ventas, int fecha, int ruc, char *codigo, int cantidad)
{
    if (!ventas) ventas = new void*();
    void **vArr = reinterpret_cast<void**>(ventas);
    int numEl = 0; while (vArr[numEl] != nullptr) numEl++;
    void **aux = new void*[numEl + 2](), **reg = new void*[4];
    for (int i = 0; i < numEl; ++i) aux[i] = vArr[i];
    reg[0] = new int {fecha};
    reg[1] = new int {ruc};
    reg[3] = new int {cantidad};
    reg[2] = new char[strlen(codigo) + 1];
    strcpy(reinterpret_cast<char*>(reg[2]), codigo);
    aux[numEl] = reg;
    ventas = aux;
}

void imprimeVentas(void *ventas)
{
    ofstream reporte = oopen_file("ReporteVentas.txt", ios::out);
    void **ventasArr = reinterpret_cast<void**>(ventas);
    for (int i = 0; ventasArr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(ventasArr[i]);
        reporte << *reinterpret_cast<int*>(reg[0]) << " "
                << *reinterpret_cast<int*>(reg[1]) << " "
                << reinterpret_cast<char*>(reg[2]) << " "
                << *reinterpret_cast<int*>(reg[3]) << endl;
    }
}

void leeProductos(void *&productos)
{
    ifstream file = iopen_file("productos.csv");
    char codigo[8], nombre[100]; double precio; productos = nullptr;
    while (true) {
        file.getline(codigo, 8, ',');
        if (file.eof()) break;
        file.getline(nombre, 100, ',');
        file >> precio;
        file >> ws;
        insert_producto(productos, codigo, nombre, precio);
    }
}

void insert_producto(void *&productos, char *codigo, char *nombre, double precio)
{
    if (!productos) productos = new void*();
    void **pArr = reinterpret_cast<void**>(productos);
    int numEl = 0; while (pArr[numEl] != nullptr) numEl++;
    void **aux = new void*[numEl+2](), **reg = new void*[3];
    for (int i = 0; i < numEl; ++i) aux[i] = pArr[i];
    reg[2] = new double {precio};
    reg[0] = new char [strlen(codigo) + 1];
    strcpy(reinterpret_cast<char*>(reg[0]), codigo);
    reg[1] = new char [strlen(nombre) + 1];
    strcpy(reinterpret_cast<char*>(reg[1]), nombre);
    aux[numEl] = reg;
    productos = aux;
}

void imprimeProductos(void *productos)
{
    ofstream reporte = oopen_file("ReporteProductos.txt");
    void **pArr = reinterpret_cast<void**>(productos);
    for (int i = 0; pArr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(pArr[i]);
        reporte << reinterpret_cast<char*>(reg[0]) << " "
                << reinterpret_cast<char*>(reg[1]) << " "
                << *reinterpret_cast<double*>(reg[2]) << endl;
    }
}

void leerClientes(void *&clientes)
{
    ifstream file = iopen_file("clientes.csv");
    int codigo; char nombre[50], _;
    clientes = nullptr;
    while (true) {
        file >> codigo >> _;
        if (file.eof()) break;
        file.getline(nombre, 50);
        insert_cliente(clientes, codigo, nombre);
    }
}

void insert_cliente(void *&clientes, int codigo, char *nombre)
{
    if (!clientes) clientes = new void*();
    void **cArr = reinterpret_cast<void**>(clientes);
    int numEl = 0; while (cArr[numEl]) numEl++;
    void **aux = new void*[numEl+2](), **reg = new void*[3];
    for (int i = 0; i < numEl; ++i) aux[i] = cArr[i];
    reg[0] = new int {codigo};
    reg[1] = new char [strlen(nombre) + 1];
    strcpy(reinterpret_cast<char*>(reg[1]), nombre);
    aux[numEl] = reg;
    clientes = aux;
}

void imprimeClientes(void *clientes)
{
    void **cArr = reinterpret_cast<void**>(clientes);
    ofstream reporte = oopen_file("ReporteClientes.txt");
    for (int i = 0; cArr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(cArr[i]);
        reporte << *reinterpret_cast<int*>(reg[0]) << " "
                << reinterpret_cast<char*>(reg[1]) << endl;
    }
}

void liquidaVentas(void *clientes, void* ventas, void *productos)
{

}