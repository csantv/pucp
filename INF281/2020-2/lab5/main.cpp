/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#include "Laboratorio05_Funciones.h"
#include "func-aux.h"

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    char **codMed, **nombMed, ***nombPac;
    int **codPac, **veces;
    double *tarifas, **porcPac;
    leerMedicos(codMed, nombMed, tarifas);
    repMedicos(codMed, nombMed, tarifas);
    leerAtenciones(codMed, codPac, nombPac, porcPac, veces);
//    repDeIngresos(codMed, nombMed, tarifas, codPac, nombPac, porcPac);
    int *arr = nullptr;
    append_int(arr, 3);
    append_int(arr, 4);
    append_int(arr, 5);
    append_int(arr, 6);
    for (int i = 0; arr[i]; ++i) {
        cout << arr[i] << endl;
    }
    return 0;
}