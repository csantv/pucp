#include <iostream>
#include <iomanip>

#include "funciones.h"

using namespace std;

void crear_binario()
{
    int dd, mm, aa, serie, secuencia, referencia; char car, tipoDoc[4], codCli[9]; double monto;
    ifstream archReg = iopen_file("REGISTRO.txt", ios::in);
    ofstream archBin = oopen_file("Registro.bin", ios::out | ios::binary);
    while (true) {
        // lectura del archivo de datos
        archReg >> codCli;
        if (archReg.eof()) break;
        archReg >> dd >> car >> mm >> car >> aa;
        archReg >> tipoDoc;
        archReg >> serie >> car >> secuencia;
        archReg >> monto >> referencia;
        // grabar en el archivo binario
        archBin.write(reinterpret_cast<const char*>(&dd), sizeof(int));
        archBin.write(reinterpret_cast<const char*>(&mm), sizeof(int));
        archBin.write(reinterpret_cast<const char*>(&aa), sizeof(int));
        archBin.write(reinterpret_cast<const char*>(&codCli), sizeof(char) * 9);
        archBin.write(reinterpret_cast<const char*>(&tipoDoc), sizeof(char) * 4);
        archBin.write(reinterpret_cast<const char*>(&serie), sizeof(int));
        archBin.write(reinterpret_cast<const char*>(&secuencia), sizeof(int));
        archBin.write(reinterpret_cast<const char*>(&monto), sizeof(double));
        archBin.write(reinterpret_cast<const char*>(&referencia), sizeof(int));
    }
}

void actualizar_nc()
{
    int dd, mm, aa, serie, secuencia, referencia; char tipoDoc[4], codCli[9]; double monto;
    fstream archBin = open_file("Registro.bin", ios::in | ios::out | ios::binary);
    while (true) {// lectura del archivo de datos
        int ini_pos = archBin.tellg();  // inicio del registro
        archBin.read(reinterpret_cast<char*>(&dd), sizeof(int));
        archBin.read(reinterpret_cast<char*>(&mm), sizeof(int));
        archBin.read(reinterpret_cast<char*>(&aa), sizeof(int));
        archBin.read(reinterpret_cast<char*>(&codCli), sizeof(char) * 9);
        archBin.read(reinterpret_cast<char*>(&tipoDoc), sizeof(char) * 4);
        archBin.read(reinterpret_cast<char*>(&serie), sizeof(int));
        archBin.read(reinterpret_cast<char*>(&secuencia), sizeof(int));
        archBin.read(reinterpret_cast<char*>(&monto), sizeof(double));
        archBin.read(reinterpret_cast<char*>(&referencia), sizeof(int));
        int end_pos = archBin.tellg();  // fin del registro
        if (tipoDoc[0] == 'N') {
            monto = buscar_total_devolucion(mm, aa, referencia);
            archBin.seekg(ini_pos);   // avanzar hasta el monto
            archBin.seekg(5 * sizeof(int) + 13 * sizeof(char), ios::cur);
            archBin.write(reinterpret_cast<const char*>(&monto), sizeof(double));
            archBin.seekg(end_pos);
        }
        if (archBin.eof()) break;
    }
}

double buscar_total_devolucion(int mm, int yy, int ref)
{
    ifstream archDevl = iopen_file("devolucion.txt", ios::in);
    int my_ref, my_dd, my_mm, my_yy, my_cod; char _;
    double total = 0, my_num;
    while (true) {
        archDevl >> my_ref >> my_dd >> _ >> my_mm >> _ >> my_yy
                 >> my_cod >> my_num;
        if (archDevl.eof()) break;
        if (my_mm == mm && my_yy == yy && my_ref == ref) {
            total += buscar_precio(mm, yy, my_cod) * my_num;
        }
    }
    return total;
}

double buscar_precio(int mm, int yy, int cod)
{
    ifstream archPrec = iopen_file("precios.txt", ios::in);
    int my_mm, my_yy, my_cod; char _; double price = -1;
    while (true) {
        archPrec >> my_cod;
        if (my_cod <= 12) {
            my_mm = my_cod;
            archPrec >> _ >> my_yy;
            continue;
        }
        archPrec >> price;
        if (archPrec.eof()) break;
        if (my_mm == mm && my_yy == yy && my_cod == cod) break;
    }
    return price;
}

std::ifstream iopen_file(const char* name, std::ios_base::openmode mode)
{
    ifstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}

std::ofstream oopen_file(const char* name, std::ios_base::openmode mode)
{
    ofstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}

std::fstream open_file(const char* name, std::ios_base::openmode mode)
{
    fstream file(name, mode);
    if (!file.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << name << endl;
        exit(1);
    }
    return file;
}