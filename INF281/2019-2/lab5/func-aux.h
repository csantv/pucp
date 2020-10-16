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

#endif
