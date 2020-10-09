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
void cargarPacientes(char* codMed, int *& codigoPac, char **& pacientes, double *& porcentajes, int*& veces);
void reporteDelMedico(std::ofstream& reporte, char* codMed, char**& codigoMed, char**& medicos, double*& tarifas,
                      int *& codigoPac, char **& pacientes, double *& porcentajes, int*& veces);
void liberarEspacios(int *& codigoPac, char **& pacientes, double *& porcentajes, int*& veces);

void append_tarifas(double *& tarifas, double tarifa, int numDat);
void append_str(char **& arr, char* str, int numDat);
int buscarPac(char **& pacientes, char* nombre);
void append_int(int *& arr, int val, int numDat);
void append_double(double *& arr, double val, int numDat);
int strlen(const char* arr);
void strcpy(char* dest, const char* src);
int strcmp(const char* s1, const char* s2);

// funciones auxiliares para abrir archivos
std::ifstream iopen_file(const char* name, std::ios_base::openmode mode);
std::ofstream oopen_file(const char* name, std::ios_base::openmode mode);
std::fstream open_file(const char* name, std::ios_base::openmode mode);

#endif
