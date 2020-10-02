/*
 * NOMBRE: CARLOS SANTOS TORO VERA
 * CODIGO: 20171878
 */

#include <iostream>

#include "MedicosPacientes.h"

using namespace std;

int main()
{
    struct StMedico med;
    struct StPaciente pac;
    ifstream prueba("prueba.txt", ios::in);

    prueba >> med;
    for (int i = 0; i < 5; ++i) {
        prueba >> pac;
        med + pac;
    }

    med++;

    cout << med;

    med + 20200117;
    med++;
    cout << med;

    med - 20200502;
    cout << med;
}

