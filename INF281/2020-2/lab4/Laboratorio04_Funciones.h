/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#ifndef LABORATORIO04_FUNCIONES_H
#define LABORATORIO04_FUNCIONES_H

#include <fstream>

void cargarMedicos(char**& codigoMed, char**& medicos, double*& tarifas);
void reporteMedicos(char**& codigoMed, char**& medicos, double*& tarifas);
void reporteDeIngresos(char**& codigoMed, char**& medicos, double*& tarifas);

void append_tarifas(double *& tarifas, double tarifa, int numDat);
void append_str(char **& arr, char* str, int numDat);
int strlen(const char* arr);
void strcpy(char* dest, const char* src);

// funciones auxiliares para abrir archivos
std::ifstream iopen_file(const char* name, std::ios_base::openmode mode);
std::ofstream oopen_file(const char* name, std::ios_base::openmode mode);
std::fstream open_file(const char* name, std::ios_base::openmode mode);

#endif
