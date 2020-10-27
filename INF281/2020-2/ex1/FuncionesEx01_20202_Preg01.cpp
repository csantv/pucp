/*
 *  NOMBRE: TORO VERA CARLOS SANTOS
 *  CODIGO: 20171878
 */

#include "FuncionesEx01_20202_Preg01.h"

#include <iostream>
#include <iomanip>

using namespace std;

void leerDatos(void *&pedidos, void *&stock)
{
    leer_pedidos(pedidos);
    reporte_pedidos(pedidos, "ReportePedidos.txt");
    leer_stock(stock);
    reporte_stock(stock);
}

void leer_pedidos(void *&pedidos)
{
    ifstream file = iopen_file("pedidos.csv");
    int ruc; char nomtienda[50], _; pedidos = nullptr;
    while (true) {
        file >> ruc >> _;
        if (file.eof()) break;
        file.getline(nomtienda, 50, ',');
        while (true) {
            int dd, mm, yy, codprod, cantprod; char nomprod[50];
            file >> yy >> _ >> mm >> _ >> dd >> _ >> codprod >> _;
            file.getline(nomprod, 50, ',');
            file >> ws;
            file >> ws >> cantprod >> noskipws >> _ >> skipws;
            int fecha = yy * 10000 + mm * 100 + dd;
            insert_pedido(pedidos, fecha, ruc, codprod, nomprod, cantprod);
            if (_ == '\n') break;
        }
    }
}

void reporte_pedidos(void *pedidos, const char* filename)
{
    ofstream reporte = oopen_file(filename);
    void **pArr = reinterpret_cast<void**>(pedidos);
    reporte << "FECHA    RUC      CODPROD " << setfill(' ') << setw(50) << left << "NOMPROD"
            << "CANTPED CANTATEND" << endl << setfill('=') << setw(95) << "" << endl;
    for (int i = 0; pArr[i]; ++i) {
        void **reg = reinterpret_cast<void**>(pArr[i]);
        reporte << *reinterpret_cast<int*>(reg[0]) << " " << *reinterpret_cast<int*>(reg[1]) << " "
                << setfill(' ') << setw(7) << right << *reinterpret_cast<int*>(reg[2]) << " "
                << setw(50) << left << reinterpret_cast<char*>(reg[3])
                << right << setw(7) << *reinterpret_cast<int*>(reg[4])
                << right << setw(10) << *reinterpret_cast<int*>(reg[5]) << endl;
    }
}

void insert_pedido(void *&pedidos, int fecha, int ruc, int codprod, char *nomprod, int cantprod)
{
    if (!pedidos) pedidos = new void**();
    void **pArr = reinterpret_cast<void**>(pedidos);
    int numEl = 0; while (pArr[numEl]) numEl++;
    void **aux = new void*[numEl+2](), **reg = new void*[6];
    for (int i = 0; i < numEl; ++i) aux[i] = pArr[i];
    reg[0] = new int{fecha};
    reg[1] = new int{ruc};
    reg[2] = new int{codprod};
    reg[3] = new char[strlen(nomprod)+1];
    strcpy(reinterpret_cast<char*>(reg[3]), nomprod);
    reg[4] = new int{cantprod};
    reg[5] = new int();
    aux[numEl] = reg;
    pedidos = aux;
}

void reporte_stock(void *stock)
{
    ofstream reporte = oopen_file("ReporteStock.txt");
    void **sArr = reinterpret_cast<void**>(stock);
    reporte << "CODIGO  DISPONIBLE" << endl
            << "==================" << endl;
    for (int i = 0; sArr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(sArr[i]);
        reporte << setfill(' ') << setw(8) << left << *reinterpret_cast<int*>(reg[0])
                << setw(5) << left << *reinterpret_cast<int*>(reg[1]) << endl;
    }
}

void leer_stock(void *&stock)
{
    ifstream file = iopen_file("stock.csv");
    int codprod, numdisp; char _; stock = nullptr;
    while (true) {
        file >> codprod >> _ >> numdisp;
        if (file.eof()) break;
        insert_stock(stock, codprod, numdisp);
    }
}

void insert_stock(void *&stock, int codprod, int numdisp)
{
    if (!stock) stock = new void**();
    void **sArr = reinterpret_cast<void**>(stock);
    int numEl = 0; while (sArr[numEl]) numEl++;
    void **aux = new void*[numEl+2](), **reg = new void*[2];
    for (int i = 0; i < numEl; ++i) aux[i] = sArr[i];
    reg[0] = new int {codprod};
    reg[1] = new int {numdisp};
    aux[numEl] = reg;
    stock = aux;
}

void atiende(void *&pedidos, void *&stock)
{
    void **&pArr = reinterpret_cast<void**&>(pedidos);
    int numEl = 0; while (pArr[numEl]) numEl++;
    sort_fechas(pedidos, 0, numEl-1);
    for (int i = 0; pArr[i]; ++i) {
        void **&reg = reinterpret_cast<void**&>(pArr[i]);
        int codprod = *reinterpret_cast<int*>(reg[2]);
        int pedido = *reinterpret_cast<int*>(reg[4]);
        *reinterpret_cast<int*>(reg[5]) = actualizar_stock(stock, codprod, pedido);
    }
    reporte_pedidos(pedidos, "ReportePedidosAtendidos.txt");
}

int actualizar_stock(void *&stock, int codprod, int pedido)
{
    void **&sArr = reinterpret_cast<void**&>(stock);
    int cant = 0;
    for (int i = 0; sArr[i]; ++i) {
        void **&reg = reinterpret_cast<void**&>(sArr[i]);
        int rcod = *reinterpret_cast<int*>(reg[0]);
        if (rcod == codprod) {
            int *numdisp = reinterpret_cast<int*>(reg[1]);
            if (!*numdisp) break;
            if (*numdisp >= pedido) {
                cant = pedido;
                *numdisp -= pedido;
            } else if (*numdisp < pedido) {
                cant = *numdisp;
                *numdisp = 0;
            }
            break;
        }
    }
    return cant;
}

void sort_fechas(void *&pedidos, int izq, int der)
{
    int limite;
    if (izq >= der) return;
    void **pArr = reinterpret_cast<void**>(pedidos);
    cambiar(pedidos, izq, (izq + der) / 2);
    limite = izq;
    for (int i = izq + 1; i <= der; ++i) {
        int fecha1 = *reinterpret_cast<int*>(reinterpret_cast<void**>(pArr[i])[0]);
        int fecha2 = *reinterpret_cast<int*>(reinterpret_cast<void**>(pArr[izq])[0]);
        if (fecha1 < fecha2) {
            cambiar(pedidos, ++limite, i);
        }
    }
    cambiar(pedidos, izq, limite);
    sort_fechas(pedidos, izq, limite - 1);
    sort_fechas(pedidos, limite + 1, der);
}

void cambiar(void *el, int i, int k)
{
    void **&elArr = reinterpret_cast<void**&>(el);
    void **aux = reinterpret_cast<void**>(elArr[i]);
    reinterpret_cast<void**&>(elArr[i]) = reinterpret_cast<void**&>(elArr[k]);
    reinterpret_cast<void**&>(elArr[k]) = aux;
}

void imprimirDatos(void *&pedidos)
{
    ofstream reporte = oopen_file("ReporteAtencion.txt");
    void **pArr = reinterpret_cast<void**>(pedidos);
    reporte << setfill(' ') << setw(37) << "" << "REPORTE DE ATENCION";
    int numEl = 0; while (pArr[numEl]) numEl++;
    sort_ruc(pedidos, 0, numEl - 1);
    int oldruc, ruc = 0;
    for (int i = 0; pArr[i]; ++i) {
        void **reg = reinterpret_cast<void**>(pArr[i]);
        oldruc = ruc; ruc = *reinterpret_cast<int*>(reg[1]);
        if (oldruc != ruc) {
            reporte << endl << "RUC:   " << ruc << endl
                    << setfill('=') << setw(120) << "" << endl
                    << setfill(' ') << "  Fecha" << setw(7) << ""
                    << "Cod. Producto" << "    "
                    << left << setw(50) << "Producto"
                    << "Cant. Solicitada     Cant. Atendida" << endl
                    << setfill('=') << setw(120) << "" << endl;
        }
        imprimir_pedido(reg, reporte);
    }
}

void imprimir_pedido(void *reg, ofstream& reporte)
{
    void **rreg = reinterpret_cast<void**>(reg);
    int fecha = *reinterpret_cast<int*>(rreg[0]);
    reporte << "  " << fecha / 10000 << "/" << setfill('0') << setw(2) << right
            << fecha % 10000 / 100 << "/" << setfill('0') << setw(2) << right
            << fecha % 10
            << right << setw(10) << setfill(' ') << *reinterpret_cast<int*>(rreg[2])
            << setw(9) << "" << left << setw(50) << reinterpret_cast<char*>(rreg[3])
            << right << setw(8) << *reinterpret_cast<int*>(rreg[4])
            << setw(20) << *reinterpret_cast<int*>(rreg[5])
            << endl;
}

void sort_ruc(void *&pedidos, int izq, int der)
{
    int limite;
    if (izq >= der) return;
    void **pArr = reinterpret_cast<void**>(pedidos);
    cambiar(pedidos, izq, (izq + der) / 2);
    limite = izq;
    for (int i = izq + 1; i <= der; ++i) {
        int ruc1 = *reinterpret_cast<int*>(reinterpret_cast<void**>(pArr[i])[1]);
        int ruc2 = *reinterpret_cast<int*>(reinterpret_cast<void**>(pArr[izq])[1]);
        if (ruc1 <= ruc2) {
            cambiar(pedidos, ++limite, i);
        }
    }
    cambiar(pedidos, izq, limite);
    sort_ruc(pedidos, izq, limite - 1);
    sort_ruc(pedidos, limite + 1, der);
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