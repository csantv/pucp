#include <iostream>
#include <iomanip>

#define MAX_SEP_CNT 100

using namespace std;

/*
 * Convierte entre las monedas utilizando los factores
 */
double convert_money(double c_dolar, double c_euro, char orig, char dest, double amount)
{
    if (orig == 'S') {
        if (dest == '$') return amount / c_dolar;
        if (dest == '&') return amount / c_euro;
    }
    if (orig == '$') {
        if (dest == 'S') return amount * c_dolar;
        if (dest == '&') return (amount * c_dolar) / c_euro;
    }
    if (orig == '&') {
        if (dest == 'S') return amount / c_euro;
        if (dest == '$') return (amount * c_euro) / c_dolar;
    }
    return -1;
}

int main()
{
    char ch = -1;
    double c_dolar, c_euro;

    cin >> ws;
    cin >> c_dolar >> ws >> c_euro;

    cout << "ESTADO DE CUENTAS DEL BANCO ABCD" << endl;

    cout.fill('=');
    cout << setw(MAX_SEP_CNT) << "" << endl;

    cout.fill(' ');
    cout << "CLIENTE" << setw(28) << ""
         << "CODIGO DE CUENTA" << setw(8) << ""
         << "MONEDA" << setw(13) << ""
         << "SALDO INICIAL" << endl;

    // imprimir nombre
    int numsp = 0, numchr = 0, totalchr = 0;
    while (true) {
        cin >> ch;
        cin >> noskipws;
        if (ch == ' ') {
            numsp++;
            numchr = 0;
        } else {
            numchr++;
            numsp = 0;
        }
        if (numsp > 1) break;
        if (numchr > 1) ch += 32;
        cout << ch;
        totalchr++;
    }
    cin >> skipws;

    // leer informacion inicial
    char cuenta_moneda = -1;
    int codigo = -1;
    double saldo_inicial = -1;
    cin >> codigo >> cuenta_moneda >> saldo_inicial;

    // imprimir informacion
    cout << setw(40 - totalchr) << "";
    cout << codigo;

    // cuenta_moneda
    cout << setw(13) << "";
    cout << left << setw(6);
    if (cuenta_moneda == '$') {
        cout << "DOLAR";
    } else if (cuenta_moneda == '&') {
        cout << "EUROS";
    } else {
        cout << "SOLES";
    }

    // saldo inicial
    cout << setw(13) << "";
    cout << cuenta_moneda;
    cout << right << setw(11);
    cout << fixed << setprecision(2) << saldo_inicial;
    cout << endl;

    cout.fill('=');
    cout << setw(MAX_SEP_CNT) << "" << endl;

    cout << "FECHA";
    cout.fill(' ');
    cout << setw(10) << "";
    cout << left;
    if (cuenta_moneda == '$') {
        cout << setw(22);
        cout << "RETIROS DOLARES";
        cout << setw(24);
        cout << "DEPOSITO DOLARES";
        cout << setw(23);
        cout << "SALDO DOLARES";
    } else if (cuenta_moneda == '&') {
        cout << setw(22);
        cout << "RETIROS EUROS";
        cout << setw(24);
        cout << "DEPOSITO EUROS";
        cout << setw(23);
        cout << "SALDO EUROS";
    } else {
        cout << setw(22);
        cout << "RETIROS SOLES";
        cout << setw(24);
        cout << "DEPOSITO SOLES";
        cout << setw(23);
        cout << "SALDO SOLES";
    }
    cout << "OBSERVACION" << endl;

    cout.fill('-');
    cout << setw(MAX_SEP_CNT) << "" << endl;

    // llenar todos los retiros
    int dd, mm, yy;
    char tipo_mov, moneda_mov;
    double amount_mov;

    cout.fill('=');
    cout << setw(MAX_SEP_CNT) << "" << endl;
    cout << "RESUMEN:" << endl;
    cout << "CANTIDAD TOTAL DE RETIROS:" << endl;
    cout << "CANTIDAD TOTAL DE DEPOSITOS:" << endl;
    cout << "SALDO FINAL:" << endl;

    return 0;

    while (true) {

        if (cin.eof()) break;

        cout << endl;
    }

    return 0;
}
