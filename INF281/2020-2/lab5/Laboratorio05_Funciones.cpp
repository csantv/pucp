/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#include "Laboratorio05_Funciones.h"
#include "../../func-aux.h"

#include <iostream>
#include <iomanip>

using namespace std;

void leerMedicos(char **&codMed, char **&nombMed, double *&tarifas)
{
    ifstream medicos = iopen_file("RelacionMedicos.csv", ios::in);
    char codigo[7], nombre[50], esp[50]; double tarifa;
    codMed = nullptr; nombMed = nullptr; tarifas = nullptr;
    while (true) {
        medicos.getline(codigo, 7, ',');
        append_str(codMed, codigo);
        medicos.getline(nombre, 50, ',');
        append_str(nombMed, nombre);
        medicos.getline(esp, 50, ',');
        medicos >> tarifa;
        append_double(tarifas, tarifa);
        medicos >> ws;
        if (medicos.eof()) break;
    }
}

void repMedicos(char **&codMed, char **&nombMed, double *&tarifas)
{
    ofstream reporte = oopen_file("ReporteMed.txt", ios::out);
    reporte << "CODIGO  " << left << setfill(' ') << setw(50) << "NOMBRE"
            << "TARIFA" << endl;
    reporte << setfill('=') << setw(64) << "" << endl;
    for (int i = 0; codMed[i] != nullptr; ++i) {
        reporte << codMed[i] << "  "
                << left << setfill(' ') << setw(50) << nombMed[i]
                << tarifas[i] << endl;
    }
}

void leerAtenciones(char **&codMed, int **&codPac, char ***&nombPac, double **&porcPac, int **&veces)
{
    ifstream atencion = iopen_file("Pacientes-Atencion.csv", ios::in);
    int dd, mm, yy; char estado; int rcodPac; char namePac[50], rcodMed[7], _; double porcentaje; bool repetido;
    int totalmed = get_total_med(codMed); init_pac_arrays(totalmed, codPac, nombPac, porcPac, veces);
    while (true) {
        atencion >> dd >> _ >> mm >> _ >> yy >> _;
        if (atencion.eof() || atencion.fail()) break;
        while (true) {
            atencion >> estado >> _ >> rcodPac >> _;
            if (atencion.fail()) { atencion.clear(); break; }
            atencion.getline(namePac, 50, ','); atencion >> porcentaje >> _;
            atencion.getline(rcodMed, 7, ','); atencion >> ws;
            int indMed = get_med_index(codMed, rcodMed);
            repetido = register_veces(codPac, indMed, rcodPac, veces);
            if (!repetido) {
                insert_nombpac(nombPac, indMed, namePac);
                insert_codpac(codPac, indMed, rcodPac);
                insert_porcpac(porcPac, indMed, porcentaje);
            }
        }
    }
}

void repDeIngresos(char **&codMed, char **&nombMed, double *&tarifas,
                   int **&codPac, char ***&nombPac, double **&porcPac)
{

}

int get_med_index(char **&codMed, char* codigo)
{
    int i = -1;
    for (int j = 0; codMed[j] != nullptr; ++j) {
        if (!strcmp(codMed[j], codigo)) i = j;
    }
    return i;
}

int get_total_med(char **&codMed)
{
    int i = 0;
    for (int j = 0; codMed[j] != nullptr; ++j) {
        i++;
    }
    return i;
}

void insert_codpac(int **&codPac, int indMed, int codigo)
{
    if (!codPac[indMed]) codPac[indMed] = new int {-1};
    int numEl = 0; while (codPac[indMed][numEl]) numEl++;
    int *aux;
    // calcular incrementos
    if ((numEl + 1) % 5 == 0) {
        aux = new int [numEl + 1]();
    } else {
        aux = new int [numEl + 5]();
    }
    for (int i = 0; i < numEl; ++i) aux[i] = codPac[indMed][i];
    aux[numEl] = codigo;
    delete codPac[indMed];
    codPac[indMed] = aux;
}

void insert_porcpac(double **&porcPac, int indMed, double porc)
{
    if (!porcPac[indMed]) porcPac[indMed] = new double {-1};
    int numEl = 0; while (porcPac[indMed][numEl] != 0) numEl++;
    double *aux;
    // calcular incrementos
    if ((numEl + 1) % 5 == 0) {
        aux = new double [numEl + 1]();
    } else {
        aux = new double [numEl + 5]();
    }
    for (int i = 0; i < numEl; ++i) aux[i] = porcPac[indMed][i];
    aux[numEl] = porc;
    delete porcPac[indMed];
    porcPac[indMed] = aux;
}

void init_pac_arrays(int total, int **&codPac, char ***&nombPac, double **&porcPac, int **&veces)
{
    codPac = new int*[total]();
    veces = new int*[total]();
    porcPac = new double*[total]();
    nombPac = new char**[total]();
}

bool register_veces(int **&codPac, int indMed, int rcodPac, int **&veces)
{
    if (!codPac[indMed]) codPac[indMed] = new int {-1};
    bool found = false;
    for (int i = 0; codPac[indMed][i] != -1; ++i) {
        if (codPac[indMed][i] == rcodPac) {
            found = true;
            veces[indMed][i]++;
            break;
        }
    }
    if (!found) append_int(veces[indMed], 1);
    return found;
}

void insert_nombpac(char ***&nombPac, int indMed, char *namePac)
{
    if (!nombPac[indMed]) nombPac[indMed] = new char* {nullptr};
    int numEl = 0; while (nombPac[indMed][numEl]) numEl++;
    char **aux;
    // calcular incrementos
    if ((numEl + 1) % 5 == 0) {
        aux = new char* [numEl + 1]();
    } else {
        aux = new char* [numEl + 5]();
    }
    for (int i = 0; i < numEl; ++i) aux[i] = nombPac[indMed][i];
    aux[numEl] = new char [strlen(namePac) + 1];
    strcpy(aux[numEl], namePac);
    nombPac[indMed] = aux;
}