/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#ifndef LABORATORIO05_FUNCIONES_H_H
#define LABORATORIO05_FUNCIONES_H_H

void leerMedicos(char **&codMed, char **&nombMed, double *&tarifas);
void repMedicos(char **&codMed, char **&nombMed, double *&tarifas);
void leerAtenciones(char **&codMed, int **&codPac, char ***&nombPac, double **&porcPac, int **&veces);
void repDeIngresos(char **&codMed, char **&nombMed, double *&tarifas,
                   int **&codPac, char ***&nombPac, double **&porcPac);

int get_med_index(char **&codMed, char* codigo);
void insert_codpac(int **&codPac, int indMed, int codigo);
void insert_porcpac(double **&porcPac, int indMed, double porc);
int get_total_med(char **&codMed);
void init_pac_arrays(int total, int **&codPac, char ***&nombPac, double **&porcPac, int **&veces);
bool register_veces(int **&codPac, int indMed, int rcodPac, int **&veces);
void insert_nombpac(char ***&nombPac, int indMed, char *namePac);

#endif