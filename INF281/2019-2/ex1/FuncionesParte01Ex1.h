#ifndef INF281_FUNCIONESPARTE01EX1_H
#define INF281_FUNCIONESPARTE01EX1_H

#include <fstream>

void leeVentas(void *&ventas);
void imprimeVentas(void *ventas);
void leeProductos(void *&productos);
void imprimeProductos(void *productos);
void leerClientes(void *&clientes);
void imprimeClientes(void *clientes);
void liquidaVentas(void *clientes, void* ventas, void *productos);

void insert_venta(void *&ventas, int fecha, int ruc, char *codigo, int cantidad);
void insert_producto(void *&productos, char *codigo, char *nombre, double precio);
void insert_cliente(void *&clientes, int codigo, char *nombre);
void gen_liquidacion(void *&liquidacion, void *ventas, void *productos, int ruc, int mes);
void get_nom_prod(void *productos, char* codigo, char *&nombre);
void gen_rep_liquid(std::ofstream& reporte, void *liquidacion, void *productos);
void get_nom_client(void *clientes, int ruc, char *&nombre);
double get_prod_precio(char *codigo, void *productos);
int get_ind_prod(void *liquidacion, char *codigo);
int insert_prod_liquid(void *&liquidacion, char *codigo);

#endif
