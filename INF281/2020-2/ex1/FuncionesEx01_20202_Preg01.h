/*
 *  NOMBRE: TORO VERA CARLOS SANTOS
 *  CODIGO: 20171878
 */

#ifndef INF281_FUNCIONESEX01_20202_PREG01_H
#define INF281_FUNCIONESEX01_20202_PREG01_H

#include <fstream>

// funciones primarias
void leerDatos(void *&pedidos, void *&stock);
void atiende(void *&pedidos, void *&stock);
void imprimirDatos(void *&pedidos);

// funciones secundarias
void leer_pedidos(void *&pedidos);
void leer_stock(void *&stock);
void insert_stock(void *&stock, int codprod, int numdisp);
void insert_pedido(void *&pedidos, int fecha, int ruc, int codprod, char *nomprod, int cantprod);
int actualizar_stock(void *&stock, int codprod, int pedido);

// funciones reportes
void reporte_stock(void *stock);
void reporte_pedidos(void *pedidos, const char* filename);
void imprimir_pedido(void *reg, std::ofstream& reporte);

// funciones para ordenar
void sort_fechas(void *&pedidos, int izq, int der);
void sort_ruc(void *&pedidos, int izq, int der);
void cambiar(void *el, int i, int k);

// funciones auxiliares
std::ifstream iopen_file(const char* name, std::ios_base::openmode mode = std::ios_base::in);
std::ofstream oopen_file(const char* name, std::ios_base::openmode mode = std::ios_base::out);

// funciones para cadenas
int strlen(const char* arr);
void strcpy(char* dest, const char* src);
int strcmp(const char* s1, const char* s2);

#endif