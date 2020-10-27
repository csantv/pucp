/*
 *  NOMBRE: TORO VERA CARLOS SANTOS
 *  CODIGO: 20171878
 */

#include "FuncionesEx01_20202_Preg01.h"

int main(int argc, char** argv) {
    void *pedidos, *stock;
    leerDatos(pedidos, stock);
    atiende(pedidos, stock);
    imprimirDatos(pedidos);
    return 0;
}