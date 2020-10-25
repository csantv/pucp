#include "FuncionesParte01Ex1.h"

int main(void)
{
    void *ventas, *productos, *clientes;

    leeVentas(ventas);
    imprimeVentas(ventas);
    leeProductos(productos);
    imprimeProductos(productos);
    leerClientes(clientes);
    imprimeClientes(clientes);
    liquidaVentas(clientes, ventas, productos);
    return 0;
}