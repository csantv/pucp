/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#include <fstream>
#include <iomanip>

#include "func.h"
#include "func-aux.h"

using namespace std;

void generar_alumnos_bin()
{
    ifstream alumn = iopen_file("Alumnos.txt", ios::in);
    oopen_file("Alumnos.bin", ios::out | ios::binary);  // crear el archivo binario
    int cod, yy, fac; char name_alumn[50], name_fac[50], _;
    while (true) {
        alumn >> cod >> _ >> yy >> _ >> fac >> name_alumn >> name_fac;
        if (alumn.eof()) break;
        insert_alumnos_bin(cod, yy, fac, name_alumn, name_fac);
    }
    generar_reporte_alumnos();
}

void generar_reporte_alumnos()
{
    ofstream reporte = oopen_file("Reporte-Alumnos.txt", ios::out);
    ifstream alumnBin = iopen_file("Alumnos.bin", ios::in | ios::binary);
    int cod, yy, fac; char name_alumn[50], name_fac[30], _;
    double total_cur, total_cred_apro, total_cred_des, sum_nota_aprob, sum_nota_des,
        prom_gen_cur, prom_gen_apro, relacion_aprob_cred;
    reporte << "CODIGO  "
            << "AÑO  "
            << left << "FACULTAD  "
            << setw(50) << "NOMBRE  "
            << setw(30) << "NOMBRE FACULTAD  "
            << "TOTAL_CURSOS_REGISTRADOS  "
            << "TOTAL_CREDITOS_APROBADOS  "
            << "TOTAL_CREDITOS_DESAPROBADOS  "
            << "SUMA_NOTAS_APROBADAS  "
            << "PROMEDIO_GENERAL_DEL CURSO  "
            << "PROMEDIO_CURSOS_APROBADOS  "
            << "RELACION_CREDITOS_APROBADOS/CREDITOS_TOTALES  " << endl;
    reporte << setfill('=') << setw(300) << "" << endl;
    while (true) {
        alumnBin.read(reinterpret_cast<char*>(&cod), sizeof(int));
        alumnBin.read(reinterpret_cast<char*>(&yy), sizeof(int));
        alumnBin.read(reinterpret_cast<char*>(&fac), sizeof(int));
        alumnBin.read(reinterpret_cast<char*>(&name_alumn), sizeof(char) * 50);
        alumnBin.read(reinterpret_cast<char*>(&name_fac), sizeof(char) * 30);
        alumnBin.read(reinterpret_cast<char*>(&total_cur), sizeof(double));
        alumnBin.read(reinterpret_cast<char*>(&total_cred_apro), sizeof(double));
        alumnBin.read(reinterpret_cast<char*>(&total_cred_des), sizeof(double));
        alumnBin.read(reinterpret_cast<char*>(&sum_nota_aprob), sizeof(double));
        alumnBin.read(reinterpret_cast<char*>(&sum_nota_des), sizeof(double));
        alumnBin.read(reinterpret_cast<char*>(&prom_gen_cur), sizeof(double));
        alumnBin.read(reinterpret_cast<char*>(&prom_gen_apro), sizeof(double));
        alumnBin.read(reinterpret_cast<char*>(&relacion_aprob_cred), sizeof(double));
        if (alumnBin.eof()) break;
        reporte << left << setfill(' ') << setw(7) << cod
                << setw(7) << yy
                << setw(7) << fac
                << name_alumn << setw(50 - string(name_alumn).length()) << ""
                << name_fac << setw(50 - string(name_fac).length()) << ""
                << setw(25) << total_cur
                << setw(25) << total_cred_apro
                << setw(25) << total_cred_des
                << setw(25) << sum_nota_aprob
                << setw(25) << sum_nota_des
                << setw(25) << prom_gen_cur
                << setw(25) << prom_gen_apro
                << setw(25) << relacion_aprob_cred;
        reporte << endl;
    }
}

void insert_alumnos_bin(int cod, int yy, int fac, char* name_alumn, char* name_fac)
{
    double dummy = 0;
    ofstream alumnBin = oopen_file("Alumnos.bin", ios::app | ios::binary);
    alumnBin.write(reinterpret_cast<const char*>(&cod), sizeof(int));
    alumnBin.write(reinterpret_cast<const char*>(&yy), sizeof(int));
    alumnBin.write(reinterpret_cast<const char*>(&fac), sizeof(int));
    alumnBin.write(reinterpret_cast<const char*>(name_alumn), sizeof(char) * 50);
    alumnBin.write(reinterpret_cast<const char*>(name_fac), sizeof(char) * 30);
    for (int i = 0; i < 8; ++i) {
        alumnBin.write(reinterpret_cast<const char*>(&dummy), sizeof(double));
    }
}

void generar_notas_bin()
{
    ifstream alumnCur = iopen_file("Alumnos-Cursos.txt", ios::in);
    oopen_file("NotasFinales.bin", ios::out | ios::binary); // crear el archivo binario
    int cod, bak_cod, yy_in, fac, cur_fac, nota, dd, mm, yy; double cred;
    char nom_cur[7], _;
    while (true) {
        alumnCur >> cod >> _ >> yy_in >> _ >> fac;
        if (cod != 0) bak_cod = cod;
        if (alumnCur.eof()) break;
        if (alumnCur.fail()) {
            alumnCur.clear();
            alumnCur >> nom_cur >> cur_fac >> cred >> nota >> dd >> _ >> mm >> _ >> yy;
            insert_notas_bin(bak_cod, yy_in, fac, nom_cur, cur_fac, cred, nota, dd, mm, yy);
        }
    }
    generar_reporte_notas();
}

void insert_notas_bin(int cod, int yy_in, int fac, char* nom_cur, int cur_fac,
                      double cred, int nota, int dd, int mm, int yy)
{
    ofstream notasBin = oopen_file("NotasFinales.bin", ios::app | ios::binary);
    if (yy < yy_in) return;
    notasBin.write(reinterpret_cast<const char*>(&cod), sizeof(int));
    notasBin.write(reinterpret_cast<const char*>(&yy_in), sizeof(int));
    notasBin.write(reinterpret_cast<const char*>(&fac), sizeof(int));
    notasBin.write(reinterpret_cast<const char*>(nom_cur), sizeof(char) * 7);
    notasBin.write(reinterpret_cast<const char*>(&cur_fac), sizeof(int));
    notasBin.write(reinterpret_cast<const char*>(&cred), sizeof(double));
    notasBin.write(reinterpret_cast<const char*>(&nota), sizeof(int));
    notasBin.write(reinterpret_cast<const char*>(&yy), sizeof(int));
    int sem = 0;
    if (3 <= mm && mm <= 7) {
        sem = 1;
    } else if (8 <= mm && mm <= 12){
        sem = 2;
    }
    notasBin.write(reinterpret_cast<const char*>(&sem), sizeof(int));
}

void generar_reporte_notas()
{
    ifstream notasBin = iopen_file("NotasFinales.bin", ios::in | ios::binary);
    ofstream reporte = oopen_file("NotasFinales-Reporte.txt", ios::out);
    int cod, yy_in, fac, cur_fac, nota, sem, yy; double cred;
    char nom_cur[7];
    while (true) {
        notasBin.read(reinterpret_cast<char*>(&cod), sizeof(int));
        notasBin.read(reinterpret_cast<char*>(&yy_in), sizeof(int));
        notasBin.read(reinterpret_cast<char*>(&fac), sizeof(int));
        notasBin.read(reinterpret_cast<char*>(&nom_cur), sizeof(char) * 7);
        notasBin.read(reinterpret_cast<char*>(&cur_fac), sizeof(int));
        notasBin.read(reinterpret_cast<char*>(&cred), sizeof(double));
        notasBin.read(reinterpret_cast<char*>(&nota), sizeof(int));
        notasBin.read(reinterpret_cast<char*>(&yy), sizeof(int));
        notasBin.read(reinterpret_cast<char*>(&sem), sizeof(int));
        reporte << cod << " " << yy_in << " " << fac << " "
                << nom_cur << " " << cur_fac << " "
                << cred << " " << nota << " "
                << yy << " " << sem << endl;
        if (notasBin.eof()) break;
    }
}

void completar_camp_num_alumnos()
{
    fstream alumnBin = open_file("Alumnos.bin", ios::in | ios::out | ios::binary);
    ifstream notasBin = iopen_file("NotasFinales.bin", ios::in | ios::binary);
}