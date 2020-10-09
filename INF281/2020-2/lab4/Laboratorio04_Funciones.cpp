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

void append_tarifas(double *& tarifas, double tarifa, int numDat)
{
    double* aux; int cap = numDat + INCREMENTOS;
    aux = new double [cap];
    for (int i = 0; i < numDat; ++i) {
        aux[i] = tarifas[i];
    }
    aux[numDat] = tarifa;
    aux[numDat + 1] = -1;
    if (!tarifas) delete tarifas;
    tarifas = aux;
}

void append_str(char **& arr, char* str, int numDat)
{
    char** aux; int cap = numDat + INCREMENTOS;
    aux = new char* [cap];
    for (int i = 0; i < numDat; ++i) {
        aux[i] = new char [strlen(arr[i]) + 1];
        strcpy(aux[i], arr[i]);
        delete arr[i];
    }
    aux[numDat] = new char [strlen(str) + 1];
    strcpy(aux[numDat], str);
    aux[numDat + 1] = new char;
    *aux[numDat + 1] = EOF;
    if (!arr) delete arr;
    arr = aux;
}

void cargarMedicos(char**& codigoMed, char**& medicos, double*& tarifas)
{
    ifstream relMedicos = iopen_file("RelacionMedicos.csv", ios::in);
    char cod[7], str[50]; double tarifa; int numDat = 0;
    while (true) {
        if (relMedicos.eof()) break;
        relMedicos.getline(cod, 7, ',');
        append_str(codigoMed, cod, numDat);
        relMedicos.getline(str, 50, ',');
        append_str(medicos, str, numDat);
        relMedicos.getline(str, 50, ',');
        relMedicos >> tarifa >> ws;
        append_tarifas(tarifas, tarifa, numDat);
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

void reporteDeIngresos(char**& codigoMed, char**& medicos, double*& tarifas)
{

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