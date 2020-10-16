#include "Funcioneslaboratorio05.h"

int main(int argc, char** argv)
{
    char ***almacenes, **codigoProd, **nombreProd;
    leerPalets(almacenes);
    imprimirPalets(almacenes);
    leerProductos(codigoProd, nombreProd);
    imprimirProductos(codigoProd, nombreProd);
    ordenaproductos(codigoProd, nombreProd);
    imprimirProductos(codigoProd, nombreProd);
    cuentaproductos(almacenes, codigoProd, nombreProd);
    return 0;
}