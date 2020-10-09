/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#include "Laboratorio04_Funciones.h"

int main(int argc, char** argv)
{
    char** codigoMed, **medicos;
    double* tarifas;
    cargarMedicos(codigoMed, medicos, tarifas);
    reporteMedicos(codigoMed, medicos, tarifas);
    reporteDeIngresos(codigoMed, medicos, tarifas);
    return 0;
}