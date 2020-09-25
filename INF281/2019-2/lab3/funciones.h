#ifndef INF281_FUNCIONES_H
#define INF281_FUNCIONES_H

#include <fstream>

void crear_binario();
void actualizar_nc();
void generar_reporte();
double buscar_precio(int mm, int yy, int cod);
double buscar_total_devolucion(int mm, int yy, int ref);

// funciones auxiliares para abrir archivos
std::ifstream iopen_file(const char*, std::ios_base::openmode);
std::ofstream oopen_file(const char*, std::ios_base::openmode);
std::fstream open_file(const char*, std::ios_base::openmode);

#endif //INF281_FUNCIONES_H
