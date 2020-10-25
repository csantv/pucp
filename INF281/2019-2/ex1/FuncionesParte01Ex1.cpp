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
    ifstream file = iopen_file("ingreso.txt");
    int ruc, mes; char nomfile[13];
    while (true) {
        file >> ruc >> mes;
        if (file.eof()) break;
        void *liquidacion = nullptr; char *nomcliente = nullptr;
        gen_liquidacion(liquidacion, ventas, productos, ruc, mes);
        sprintf(nomfile, "%d.txt", ruc);
        get_nom_client(clientes, ruc, nomcliente);
        if (!nomcliente) continue;
        ofstream reporte = oopen_file(nomfile);
        reporte << setfill(' ') << setw(19) << "" << "Liquidacion: " << nomcliente << endl
                << setfill('=') << setw(74) << "" << endl
                << "  CODIGO" << setfill(' ') << setw(7) << ""
                << "NOMBRE DEL PRODUCTO" << setw(32) << ""
                << "IMPORTE" << endl
                << setfill('=') << setw(74) << "" << endl;
        delete nomcliente;
        gen_rep_liquid(reporte, liquidacion, productos);
    }
}

void get_nom_client(void *clientes, int ruc, char *&nombre)
{
    void **cArr = reinterpret_cast<void**>(clientes);
    for (int i = 0; cArr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(cArr[i]);
        int rruc = *reinterpret_cast<int*>(reg[0]);
        if (ruc == rruc) {
            char *rnom = reinterpret_cast<char*>(reg[1]);
            nombre = new char [strlen(rnom) + 1];
            strcpy(nombre, rnom);
            return;
        }
    }
}

void get_nom_prod(void *productos, char* codigo, char *&nombre)
{
    void **pArr = reinterpret_cast<void**>(productos);
    for (int i = 0; pArr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(pArr[i]);
        char *rcode = reinterpret_cast<char*>(reg[0]);
        if (!strcmp(codigo, rcode)) {
            char *rnom = reinterpret_cast<char*>(reg[1]);
            nombre = new char [strlen(rnom) + 1];
            strcpy(nombre, rnom);
            return;
        }
    }
}

void gen_rep_liquid(ofstream& reporte, void *liquidacion, void *productos)
{
    void **liquidArr = reinterpret_cast<void**>(liquidacion);
    for (int i = 0; liquidArr[i] != nullptr ; ++i) {
        void **reg = reinterpret_cast<void**>(liquidArr[i]); char *nomprod = nullptr;
        char *codprod = reinterpret_cast<char*>(reg[0]);
        double imp = *reinterpret_cast<double*>(reg[1]);
        get_nom_prod(productos, codprod, nomprod);
        reporte << "  " << codprod << "      " << setfill(' ') << setw(49) << left << nomprod
                << setw(9) << right << fixed << setprecision(1) << imp << endl;
        delete nomprod;
    }
}

double get_prod_precio(char *codigo, void *productos)
{
    void **pArr = reinterpret_cast<void**>(productos);
    for (int i = 0; pArr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(pArr[i]);
        if (!strcmp(codigo, reinterpret_cast<char*>(reg[0]))) {
            return *reinterpret_cast<double*>(reg[2]);
        }
    }
    return -1;
}

int get_ind_prod(void *liquidacion, char *codigo)
{
    void **lArr = reinterpret_cast<void**>(liquidacion);
    for (int i = 0; lArr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(lArr[i]);
        if (!strcmp(codigo, reinterpret_cast<char*>(reg[0]))) return i;
    }
    return -1;
}

int insert_prod_liquid(void *&liquidacion, char *codigo)
{
    void **lArr = reinterpret_cast<void**>(liquidacion);
    int numEl = 0; while (lArr[numEl] != nullptr) numEl++;
    void **aux = new void*[numEl+2](), **reg = new void*[2];
    for (int i = 0; i < numEl; ++i) aux[i] = lArr[i];
    reg[0] = new char [strlen(codigo) + 1];
    strcpy(reinterpret_cast<char*>(reg[0]), codigo);
    reg[1] = new double();
    aux[numEl] = reg;
    liquidacion = aux;
    return numEl;
}

void gen_liquidacion(void *&liquidacion, void *ventas, void *productos, int ruc, int mes)
{
    if (!liquidacion) liquidacion = new void*();
    void **vArr = reinterpret_cast<void**>(ventas);
    for (int i = 0; vArr[i] != nullptr; ++i) {
        void **regV = reinterpret_cast<void**>(vArr[i]);
        int rruc = *reinterpret_cast<int*>(regV[1]), rmes = (*reinterpret_cast<int*>(regV[0]) % 10000) / 100;
        if (rruc == ruc && rmes == mes) {
            char *cod = reinterpret_cast<char*>(regV[2]); int numprod = *reinterpret_cast<int*>(regV[3]);
            double precio = get_prod_precio(cod, productos);
            int indprod = get_ind_prod(liquidacion, cod);
            if (indprod == -1) indprod = insert_prod_liquid(liquidacion, cod);
            void **&lArr = reinterpret_cast<void**&>(reinterpret_cast<void**&>(liquidacion)[indprod]);
            double *&importe = reinterpret_cast<double*&>(lArr[1]);
            *importe += numprod * precio;
        }
    }
}