/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "Medico.h"
#include "Paciente.h"
#include "func-aux.h"

using namespace std;

int main(int argc, char **argv)
{
    ifstream medfile = iopen_file("pruebamed.txt");
    ifstream pacfile = iopen_file("pruebapac.txt");
    Medico med;
    Paciente pac;
    medfile >> med;
    int dd, mm, yy; char _;
    pacfile >> dd >> _ >> mm >> _ >> yy;
    while (true) {
        pacfile >> pac;
        if (pacfile.eof()) break;
        int fecha = get_fecha(dd, mm, yy);
        pac.setFecha(fecha);
        med + pac;
    }
    med++;
    cout << med;
    return 0;
}