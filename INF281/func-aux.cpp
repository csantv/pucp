/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#include <iostream>

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