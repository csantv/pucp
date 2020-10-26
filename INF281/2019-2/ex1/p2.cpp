#include "FuncionesParte02Ex1.h"

int main(void)
{
    int *dni;
    char **conductor, ***placas;
    double *multas, ***montosXMultas;
    leerConductores(dni, conductor, placas);
    imprimirConductores(dni, conductor, placas);
    leerMultas(multas);
    imprimirMultas(multas);
    leerInfraccionesCometidas(dni, placas, multas, montosXMultas);
    imprimirInfracCometidas(dni, conductor, placas, montosXMultas);
    return 0;
}