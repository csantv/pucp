#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
    int dd, mm, aa, serie, secuencia, referencia;
    char car, tipoDoc[4], codCli[9];
    double monto = 0, totalFac = 0, totalNC = 0, saldoFinal = 0;

    ofstream reporte("Reporte.txt", ios::out);
    if (!reporte) {
        cout << "ERROR: no se pudo abrir el archivo Reporte.txt" << endl;
        exit(1);
    }

    ifstream archBin("Registro.bin", ios::in | ios::binary);
    if (!archBin) {
        cout << "ERROR: no se pudo abrir el archivo Registro.bin" << endl;
        exit(1);
    }

    while (true) {
        // lectura del archivo binario
        archBin.read(reinterpret_cast<char*>(&dd), sizeof(int));
        if (archBin.eof()) break;

        archBin.read(reinterpret_cast<char*>(&mm), sizeof(int));
        archBin.read(reinterpret_cast<char*>(&aa), sizeof(int));
        archBin.read(reinterpret_cast<char*>(&codCli), sizeof(char) * 9);
        archBin.read(reinterpret_cast<char*>(&tipoDoc), sizeof(char) * 4);
        archBin.read(reinterpret_cast<char*>(&serie), sizeof(int));
    }

    return 0;
}