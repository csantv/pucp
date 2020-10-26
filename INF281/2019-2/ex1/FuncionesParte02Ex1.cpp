#include "FuncionesParte02Ex1.h"
#include "func-aux.h"

#include <iostream>

#define INCREMENTOS 5

using namespace std;

void leerConductores(int *&dni, char **&conductor, char ***&placas)
{
    ifstream file = iopen_file("Conductores.csv");
    int rdni; char rnombre[100], _; int telefono; char placa[8];
    dni = nullptr; conductor = nullptr; placas = nullptr;
    while (true) {
        file >> rdni >> _;
        if (file.eof()) break;
        int ind = insert_dni(dni, rdni);
        file.getline(rnombre, 100, ',');
        insert_conductor(conductor, rnombre);
        file >> telefono >> _;
        insert_placas(placas);
        while (true) {
            file.getline(placa, 8);
            insert_placas(placas, placa, ind);
            if (!file.fail()) break;
            file.clear();
            file.get();
        }
    }
}

void insert_placas(char ***&placas)
{
    if (!placas) placas = new char**();
    int numEl = 0; while (placas[numEl]) numEl++;
    if ((numEl+1) % INCREMENTOS ==1) {
        char ***aux = new char**[numEl+1+INCREMENTOS]();
        for (int i = 0; i < numEl; ++i) aux[i] = placas[i];
        placas = aux;
    }
}

void insert_placas(char ***&placas, char *placa, int ind)
{
    if (!placas[ind]) placas[ind] = new char*();
    int numEl = 0; while (placas[ind][numEl]) numEl++;
    if ((numEl+1) % INCREMENTOS == 1) {
        char **aux = new char*[numEl+1+INCREMENTOS]();
        for (int i = 0; i < numEl; ++i) aux[i] = placas[ind][i];
        aux[numEl] = new char[strlen(placa)+1];
        strcpy(aux[numEl], placa);
        placas[ind] = aux;
    } else {
        placas[ind][numEl] = new char[strlen(placa)+1];
        strcpy(placas[ind][numEl], placa);
    }
}

int insert_dni(int *&dni, int rdni)
{
    if (!dni) dni = new int();
    int numEl = 0; while (dni[numEl]) numEl++;
    if ((numEl + 1) % INCREMENTOS == 1) {
        int *aux = new int[numEl+INCREMENTOS+1]();
        for (int i = 0; i < numEl; ++i) aux[i] = dni[i];
        aux[numEl] = rdni;
        delete dni;
        dni = aux;
    } else {
        dni[numEl] = rdni;
    }
    return numEl;
}

void insert_conductor(char **&conductor, char *rnombre)
{
    if (!conductor) conductor = new char*();
    int numEl = 0; while (conductor[numEl]) numEl++;
    if ((numEl + 1) % INCREMENTOS == 1) {
        char **aux = new char*[numEl+1+INCREMENTOS]();
        for (int i = 0; i < numEl; ++i) aux[i] = conductor[i];
        aux[numEl] = new char[strlen(rnombre)+1];
        strcpy(aux[numEl], rnombre);
        conductor = aux;
    } else {
        conductor[numEl] = new char[strlen(rnombre) + 1];
        strcpy(conductor[numEl], rnombre);
    }
}

void imprimirConductores(int *dni, char **conductor, char ***placas)
{
    ofstream reporte = oopen_file("ReporteConductores.txt");
    for (int i = 0; dni[i] != 0; ++i) {
        for (int j = 0; placas[i][j] ; ++j) {
            reporte << dni[i] << " " << conductor[i] << " " << placas[i][j] << endl;
        }
    }
}

void leerMultas(double *&multas)
{
    ifstream file = iopen_file("Infracciones.csv");
    int codigo; char descripcion[300], gravedad[15], _; double monto;
    multas = nullptr;
    while (true) {
        file >> codigo >> _;
        if (file.eof()) break;
        file.getline(descripcion, 300, ',');
        file.getline(gravedad, 15, ',');
        file >> monto;
        insert_multa(multas, codigo, monto);
    }
}

void insert_multa(double *&multas, int codigo, double monto)
{
    if (!multas) multas = new double{-1};
    int numEl = 0; while (multas[numEl] != -1) numEl++;
    if (codigo > numEl - 1) {
        double *aux = new double[codigo+2]();
        for (int i = 0; i < numEl; ++i) aux[i] = multas[i];
        aux[codigo] = monto;
        aux[codigo+1] = -1;
        delete multas;
        multas = aux;
    } else {
        multas[codigo] = monto;
    }
}

void imprimirMultas(double *multas)
{
    ofstream reporte = oopen_file("ReporteMultas.txt");
    for (int i = 0; multas[i] != -1; ++i) {
        if (multas[i] != 0) {
            reporte << i << " " << multas[i] << endl;
        }
    }
}

void leerInfraccionesCometidas(int *&dni, char ***&placas, double *&multas, double ***&montosXMultas)
{
    montosXMultas = nullptr;
    init_montosxmultas_arr(placas, montosXMultas);
    ifstream file = iopen_file("Registro_de_Faltas.csv");
    int rdni, codigo; char placa[8], _;
    while (true) {
        file >> rdni >> _;
        if (file.eof()) break;
        file.getline(placa, 8, ',');
        file >> codigo;
        int cond_ind = find_cond_ind(dni, rdni);
        int veh_id = find_veh_ind(placas, cond_ind, placa);
        double monto = multas[codigo];
        montosXMultas[cond_ind][0][veh_id] += monto;
        *montosXMultas[cond_ind][1] += monto;
    }
}

int find_cond_ind(int *dni, int rdni)
{
    for (int i = 0; dni[i]; ++i) {
        if (dni[i] == rdni) return i;
    }
    return -1;
}

int find_veh_ind(char ***placas, int cond_ind, char *placa)
{
    for (int i = 0; placas[cond_ind][i] != nullptr; ++i) {
        if (!strcmp(placas[cond_ind][i], placa)) return i;
    }
    return -1;
}

void init_montosxmultas_arr(char ***&placas, double ***&montosXMultas)
{
    // numero de conductores
    int numCon = 0; while (placas[numCon]) numCon++;
    montosXMultas = new double**[numCon+1]();
    // vehiculos por conductor
    for (int i = 0; i < numCon; ++i) {
        int numVeh = 0; while (placas[i][numVeh]) numVeh++;
        montosXMultas[i] = new double*[2];
        montosXMultas[i][0] = new double[numVeh+1]();
        montosXMultas[i][1] = new double();
    }
}

void imprimirInfracCometidas(int *dni, char **conductor, char ***placas, double ***montosXMultas)
{
    ofstream reporte = oopen_file("ReporteInfracciones.txt");
    for (int i = 0; dni[i]; ++i) {
        for (int j = 0; placas[i][j]; ++j) {
            reporte << dni[i] << " " << conductor[i] << " "
                    << placas[i][j] << " " << montosXMultas[i][0][j] << endl;
        }
    }
}