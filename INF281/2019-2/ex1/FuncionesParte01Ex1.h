#ifndef INF281_FUNCIONESPARTE01EX1_H
#define INF281_FUNCIONESPARTE01EX1_H

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

#endif
