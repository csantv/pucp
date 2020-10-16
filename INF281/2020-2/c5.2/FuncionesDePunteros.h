#ifndef INF281_FUNCIONESDEPUNTEROS_H
#define INF281_FUNCIONESDEPUNTEROS_H

#include <fstream>

void leerNombres(char**& nombres, int& numDat, const char* nombArch);
void ordenar(char** nombres, int izq, int der);
void imprimir(char** nombres, int numDat, const char* nombArch);
char* leeCadena(std::ifstream &archNomb);
void cambiar(char **nombres, int izq, int i);

#endif //INF281_FUNCIONESDEPUNTEROS_H
