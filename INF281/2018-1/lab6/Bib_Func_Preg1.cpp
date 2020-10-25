#include "Bib_Func_Preg1.h"
#include "func-aux.h"

#include <iostream>
#include <iomanip>

using namespace std;

void leerUsuarios(void *&usuarios)
{
    int codigo; char _, nombre[50];
    usuarios = nullptr;
    ifstream usr = iopen_file("Usuarios.csv", ios::in);
    while (true) {
        usr >> codigo >> _;
        if (usr.eof() || usr.fail()) break;
        usr.getline(nombre, 50, '\r');
        usr >> ws;
        insert_usuario(usuarios, codigo, nombre);
    }
}

void insert_usuario(void *&usuarios, int codigo, char *nombre)
{
    if (!usuarios) usuarios = new void*();
    void **usr = reinterpret_cast<void**>(usuarios);
    int numEl = 0; while (usr[numEl]) numEl++;
    void **aux = new void*[numEl+2](), **reg = new void*[4];
    int *cod = new int {codigo};
    for (int i = 0; i < numEl; ++i) aux[i] = usr[i];
    reg[0] = cod;
    reg[1] = new char* [strlen(nombre) + 1]();
    strcpy(reinterpret_cast<char*>(reg[1]), nombre);
    aux[numEl] = reg;
    usuarios = aux;
}

void imprimirUsuarios(void *usuarios)
{
    ofstream reporte = oopen_file("ReporteUsuarios.txt", ios::out);
    reporte << "USUARIOS DE LA BIBLIOTECA" << endl;
    reporte << "No.    CODIGO       NOMBRE" << endl;
    void **usr = reinterpret_cast<void**>(usuarios);
    for (int i = 0; usr[i] != nullptr; ++i) {
        void **reg = reinterpret_cast<void**>(usr[i]);
        int codigo = *reinterpret_cast<int*>(reg[0]);
        char *nombre = reinterpret_cast<char*>(reg[1]);
        reporte << right << setfill(' ') << setw(2) << i + 1 << ")    "
                << left << setw(13) << codigo << nombre << endl;
    }
}