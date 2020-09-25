#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    int dd, mm, aa, serie, secuencia, referencia;
    char car, tipoDoc[4], codCli[9];
    double monto = 0, totalFac = 0, totalNC = 0, saldoFinal = 0;
    ifstream archReg ("REGISTRO.txt", ios::in);
    if (!archReg) {
        cout << "ERROR: no se pudo abrir el archivo Registro.txt" << endl;
        exit(1);
    }

    ofstream archBin ("Registro.bin", ios::out | ios::binary);
    if (!archBin) {
        cout << "ERROR: no se pudo abrir el archivo Registro.bin" << endl;
        exit(1);
    }

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

    return 0;
}