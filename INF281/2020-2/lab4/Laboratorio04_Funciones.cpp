/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#include <iostream>

#include "Laboratorio04_Funciones.h"

#define INCREMENTOS 2

using namespace std;

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

void append_str(char **& arr, char* str)
{
    if (!arr) arr = new char* {new char {EOF}};             // verificar si es nulo e iniciarlo
    int numDat = 0; while (*arr[numDat] != EOF) numDat++;   // obtener numero de datos
    char** aux = new char* [numDat + 2];                    // arreglo auxiliar
    for (int i = 0; i < numDat; ++i) {                      // copiar datos
        aux[i] = new char [strlen(arr[i]) + 1];
        strcpy(aux[i], arr[i]);
        delete arr[i];
    }
    aux[numDat] = new char [strlen(str) + 1];               // agregar nuevo valor
    strcpy(aux[numDat], str);
    aux[numDat + 1] = new char {EOF};   // fin del arreglo es EOF
    delete[] arr;   // eliminar arreglo anterior
    arr = aux;      // asignar nuevo arreglo a arr
}

void append_int(int*& arr, int val)
{
    if (!arr) arr = new int {-1};
    int numDat = 0; while (arr[numDat] != -1) numDat++;
    int* aux = new int [numDat + 2];
    for (int i = 0; i < numDat; ++i) aux[i] = arr[i];
    aux[numDat] = val;
    aux[numDat + 1] = -1;
    delete[] arr;
    arr = aux;
}

void append_double(double*& arr, double val)
{
    if (!arr) arr = new double {-1};
    int numDat = 0; while (arr[numDat] != -1) numDat++;
    double* aux = new double [numDat + 2];
    for (int i = 0; i < numDat; ++i) aux[i] = arr[i];
    aux[numDat] = val;
    aux[numDat + 1] = -1;
    delete[] arr;
    arr = aux;
}

void cargarMedicos(char**& codigoMed, char**& medicos, double*& tarifas)
{
    codigoMed = nullptr; medicos = nullptr; tarifas = nullptr;
    ifstream relMedicos = iopen_file("RelacionMedicos.csv", ios::in);
    char cod[7], str[50]; double tarifa; int numDat = 0;
    while (true) {
        if (relMedicos.eof()) break;
        relMedicos.getline(cod, 7, ',');
        append_str(codigoMed, cod);
        relMedicos.getline(str, 50, ',');
        append_str(medicos, str);
        relMedicos.getline(str, 50, ',');
        relMedicos >> tarifa >> ws;
        append_double(tarifas, tarifa);
        numDat++;
    }
}

void reporteMedicos(char**& codigoMed, char**& medicos, double*& tarifas)
{
    ofstream reporte = oopen_file("ReporteMedicos.txt", ios::out);
    int i = 0;
    while (true) {
        if (tarifas[i] == -1) break;
        reporte << "Medico: " << medicos[i] << endl;
        reporte << "Codigo:" << codigoMed[i] << endl;
        reporte << "Tarifa: " << tarifas[i] << endl;
        reporte << endl;
        i++;
    }
}

int buscarPac(char **& pacientes, char* nombre)
{
    int ind = 0;
    for (int i = 0; *pacientes[i] != EOF; ++i) {
        if (!strcmp(nombre, pacientes[i])) ind = i;
    }
    return ind;
}

void cargarPacientes(char* codMed, int *& codigoPac, char **& pacientes, double *& porcentajes, int*& veces)
{
    ifstream pacDat = iopen_file("Pacientes-Atencion.csv", ios::in);
    int _i, codPac; char _c, estado, nombre[50], readMed[7]; double porcentaje; int numDat = 0;
    while (true) {
        if (pacDat.eof()) break;
        pacDat >> _i >> _c >> _i >> _c >> _i >> _c; // fecha
        while (true) {
            pacDat >> estado >> _c >> codPac >> _c;
            pacDat.getline(nombre, 50, ',');
            pacDat >> porcentaje >> _c;
            pacDat.getline(readMed, 7);
            pacDat >> _c;
            if (_c == '\n') break;
            if (estado == 'A') {
                int indice = buscarPac(pacientes, nombre);
                if (indice < 0) {
                    append_int(codigoPac, codPac);
                    append_str(pacientes, nombre);
                    append_double(porcentajes, porcentaje);
                    append_int(veces, 1);
                } else {
                    veces[indice]++;
                }
                numDat++;
            }
        }
    }
}

void reporteDelMedico(std::ofstream& reporte, char* codMed, char**& codigoMed, char**& medicos, double*& tarifas,
                      int *& codigoPac, char **& pacientes, double *& porcentajes, int*& veces)
{

}

void liberarEspacios(int *& codigoPac, char **& pacientes, double *& porcentajes, int*& veces)
{
    delete codigoPac;
    delete veces;
    delete porcentajes;
    for (int i = 0; *pacientes[i] != EOF; ++i) {
        delete pacientes[i];
    }
    delete[] pacientes;
}

void reporteDeIngresos(char**& codigoMed, char**& medicos, double*& tarifas)
{
    int *codigoPac, *veces;
    char **pacientes, codMed[7];
    double *porcentajes;
    ifstream medFile = iopen_file("Medicos.csv", ios::in);
    ofstream reporte = oopen_file("ReporteIngresos.txt", ios::out);
    while (true) {
        if (medFile.eof()) break;
        medFile >> codMed;
        cargarPacientes(codMed, codigoPac, pacientes, porcentajes, veces);
        reporteDelMedico(reporte, codMed, codigoMed, medicos, tarifas, codigoPac, pacientes,
                         porcentajes, veces);
        liberarEspacios(codigoPac, pacientes, porcentajes, veces);
    }
}

std::ifstream iopen_file(const char* name, std::ios_base::openmode mode)
{
    ifstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}

std::ofstream oopen_file(const char* name, std::ios_base::openmode mode)
{
    ofstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}

std::fstream open_file(const char* name, std::ios_base::openmode mode)
{
    fstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}