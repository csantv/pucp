/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#include "Laboratorio05_Funciones.h"

int main(int argc, char** argv)
{
    char **codMed, **nombMed, ***nombPac;
    int **codPac, **veces;
    double *tarifas, **porcPac;
    leerMedicos(codMed, nombMed, tarifas);
    repMedicos(codMed, nombMed, tarifas);
    leerAtenciones(codMed, codPac, nombPac, porcPac, veces);
//    repDeIngresos(codMed, nombMed, tarifas, codPac, nombPac, porcPac);
    return 0;
}