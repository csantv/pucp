/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#include <iostream>

#include "func-aux.h"

using namespace std;

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