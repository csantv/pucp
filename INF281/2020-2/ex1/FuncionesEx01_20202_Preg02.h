/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#ifndef INF281_FUNCIONESEX01_20202_PREG02_H
#define INF281_FUNCIONESEX01_20202_PREG02_H

#include <fstream>

// funciones principales
void leerDatos(char **&clientes, int ***&productos, char ***&strProductos);
void imprimirDatos(char **clientes, int ***productos, char ***strProductos);

// funciones secundarias
int insert_cliente(char **&clientes, char *nomcliente);
int insert_intproductos(int ***&productos, int codprod, int cantprod, int clientind);
int insert_intproductos(int ***&productos);
void insert_strprod(char ***&strProductos, char* nomprod, int clientid, int prodind);
void insert_strprod(char ***&strProductos);

// funciones auxiliares
std::ifstream iopen_file(const char* name, std::ios_base::openmode mode = std::ios_base::in);
std::ofstream oopen_file(const char* name, std::ios_base::openmode mode = std::ios_base::out);

// funciones para cadenas
int strlen(const char* arr);
void strcpy(char* dest, const char* src);
int strcmp(const char* s1, const char* s2);

#endif //INF281_FUNCIONESEX01_20202_PREG02_H
