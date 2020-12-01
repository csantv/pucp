/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#ifndef INF281_FUNC_AUX_H
#define INF281_FUNC_AUX_H

#include <fstream>
#include "Medico.h"
#include "Paciente.h"

// funciones auxiliares para abrir archivos
std::ifstream iopen_file(const char* name, std::ios_base::openmode mode = std::ios_base::in);
std::ofstream oopen_file(const char* name, std::ios_base::openmode mode = std::ios_base::out);
std::fstream open_file(const char* name, std::ios_base::openmode mode);

// funciones para arreglos dinamicos
void append_str(char **& arr, char* str);
void append_char(char *&arr, char ch);
void append_double(double*& arr, double val);
void append_int(int*& arr, int val);

int get_fecha(int dd, int mm, int yy);

#endif
