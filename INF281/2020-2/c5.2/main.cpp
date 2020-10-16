#include "FuncionesDePunteros.h"

int main(int argc, char** argv)
{
    char** nombres;
    int numDat;

    leerNombres(nombres, numDat, "personas.txt");
    ordenar(nombres, 0, numDat - 1);
    imprimir(nombres, numDat, "Reporte.txt");
    return 0;
}