#ifndef INF281_FUNCIONESLABORATORIO05_H
#define INF281_FUNCIONESLABORATORIO05_H

void leerPalets(char ***&almacenes);
void imprimirPalets(char *** const &almacenes);
void leerProductos(char **&codigoProd, char **&nombreProd);
void imprimirProductos(char **&codigoProd, char **&nombreProd);
void ordenaproductos(char **&codigoProd, char **&nombreProd);
void cuentaproductos(char ***&almacenes, char **&codigoProd, char **&nombreProd);

void appendAlmacen(char ***&almacenes, char* codAl, char* oldCodAl, char* codProd);
void append_str(char **& arr, char* str);
void cambiar(char **str1, char** str2, int i, int k);
void sort_str(char **&codigoProd, char **&nombreProd, int izq, int der);

#endif //INF281_FUNCIONESLABORATORIO05_H
