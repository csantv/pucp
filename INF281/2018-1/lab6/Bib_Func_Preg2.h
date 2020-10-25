#ifndef INF281_BIB_FUNC_PREG2_H
#define INF281_BIB_FUNC_PREG2_H

void leerPrestamos(void *&usuarios);
void imprimirPrestamos(void *usuarios);

void insertar_prestamo(void *&usuarios, int codigo, char *codLibro, char *fecha);
int inc_num_prestamos(void *&usuarios, int ind);
int buscar_usuario(void *usuarios, int codigo);
void init_num_prestamos(void *&usuarios);

#endif //INF281_BIB_FUNC_PREG2_H
