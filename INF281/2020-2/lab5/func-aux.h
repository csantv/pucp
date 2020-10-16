/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#ifndef INF281_FUNC_AUX_H
#define INF281_FUNC_AUX_H

#include <fstream>

// funciones auxiliares para abrir archivos
std::ifstream iopen_file(const char* name, std::ios_base::openmode mode);
std::ofstream oopen_file(const char* name, std::ios_base::openmode mode);
std::fstream open_file(const char* name, std::ios_base::openmode mode);

// funciones para arreglos dinamicos
void append_str(char **& arr, char* str);
void append_double(double*& arr, double val);
void append_int(int*& arr, int val);

// funciones para cadenas
int strlen(const char* arr);
void strcpy(char* dest, const char* src);
int strcmp(const char* s1, const char* s2);

#endif
