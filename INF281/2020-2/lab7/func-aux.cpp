/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#include <iostream>
#include <cstring>
#include "func-aux.h"

using namespace std;

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

fstream open_file(const char* name, ios_base::openmode mode)
{
    fstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
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

void append_double(double*& arr, double val)
{
    if (!arr) arr = new double();
    int numDat = 0; while (arr[numDat] != 0) numDat++;
    double* aux = new double [numDat + 2]();
    for (int i = 0; i < numDat; ++i) aux[i] = arr[i];
    aux[numDat] = val;
    delete[] arr;
    arr = aux;
}

void append_int(int*& arr, int val)
{
    if (!arr) arr = new int();
    int numDat = 0; while (arr[numDat] != 0) numDat++;
    int* aux = new int [numDat + 2]();
    for (int i = 0; i < numDat; ++i) aux[i] = arr[i];
    aux[numDat] = val;
    delete[] arr;
    arr = aux;
}

void append_char(char *&arr, char ch)
{
    if (!arr) arr = new char();
    int numDat = strlen(arr);
    char *aux = new char[numDat + 2]();
    strcpy(aux, arr);
    aux[numDat] = ch;
    delete[] arr;
    arr = aux;
}

int get_fecha(int dd, int mm, int yy)
{
    int res = yy;
    if (mm < 10) {
        res *= 100;
        res += mm;
    } else {
        res += mm * 100;
    }
    if (dd < 10) {
        res *= 100;
        res += dd;
    } else {
        res += dd * 100;
    }
    return res;
}
