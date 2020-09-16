// Code I've written whilst in college
// Copyright (C) 2020   Carlos Toro

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>
#include <iomanip>

#define MAX_CAR_LIN 101

using namespace std;

int main(int argc, char** argv) {
    int dd, mm, yy, serie, secuencia, referencia;
    char _, tipo_doc, cliente[9];
    double monto = 0, total_fac = 0, total_nc = 0, saldo_final;

    // titulo
    cout << "REGISTRO DE VENTAS" << endl;
    cout.fill('=');
    cout << setw(MAX_CAR_LIN) << " " << endl;
    cout.fill(' ');
    cout << "FECHA" << setw(11) << " "
         << "CLIENTE" << setw(7) << " "
         << "TIPO" << setw(13) << " "
         << "SECUENCIA" << setw(3) << " "
         << "SERIE" << setw(4) << " "
         << "FACTURAS" << setw(6) << " "
         << "N/C" << setw(5) << " "
         << "REFERENCIA" << endl;
    cout.fill('-');
    cout << setw(MAX_CAR_LIN) << " " << endl;

    while (true) {
        cin >> dd >> _ >> mm >> _ >> yy >> ws;
        cin >> cliente >> ws;
        cin >> tipo_doc >> ws;
        cin >> serie >> _ >> secuencia >> ws;
        cin >> monto >> ws;
        cin >> referencia;

        if (cin.eof()) break;

        // fecha
        cout.fill('0');
        cout << setw(2) << dd << "/"
             << setw(2) << mm << "/" << yy;
        cout.fill(' ');
        cout << setw(6) << " ";

        // cliente
        cout << cliente;
        cout << setw(5) << " ";

        // tipo
        cout << setw(20) << left;
        if (tipo_doc == 'F') {
            cout << "FACTURA";
            total_fac += monto;
        } else {
            cout << "NOTA DE CREDITO";
            total_nc += monto;
        }

        // secuencia
        cout.fill('0');
        cout << right << setw(5) << secuencia;
        cout.fill(' ');
        cout << setw(6) << " ";

        // serie
        cout.fill('0');
        cout << setw(4) << serie;


        // facturas
        cout.fill(' ');
        cout << right << setw(12);
        if (tipo_doc == 'F') {
            cout << fixed << setprecision(2) << monto;
        } else {
            cout << " ";
        }

        // nota de credito
        cout << right << setw(12);
        if (tipo_doc == 'N') {
            cout << fixed << setprecision(2) << monto;
        } else {
            cout << " ";
        }

        // referencia
        cout << setw(5) << " ";
        cout.fill('0');
        cout << right << setw(5) << referencia;

        cout << endl;
    }

    cout.fill('=');
    cout << setw(MAX_CAR_LIN) << " " << endl;

    // totales
    cout << "TOTALES:";
    cout.fill(' ');
    cout << right << setw(68);
    cout << fixed << setprecision(2) << total_fac;
    cout << setw(12) << total_nc << endl;

    // saldo final
    saldo_final = total_fac - total_nc;
    cout << "SALDO FINAL: " << saldo_final << endl;

    return 0;
}
