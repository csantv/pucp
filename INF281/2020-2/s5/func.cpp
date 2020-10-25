#include <iostream>
#include <iomanip>
#include <cstring>

#include "func.h"

using namespace std;

enum Registro {DNI, NOMBRE, SUELDO};

void leeRegistro(void *&persona)
{
	int *dni, d;
	char *nombre, buff[100];
	double *sueldo;

	cin >> d;
	if (cin.eof()) {
		persona = nullptr;
		return;
	}
	dni = new int;
	*dni = d;
	cin.get(); 	// sacar la coma
	cin.getline(buff,100,',');
	nombre = new char[strlen(buff)+1];
	strcpy(nombre, buff);
	sueldo = new double;
	cin >> *sueldo;

	void **registro = new void*[3];
	registro[DNI] = dni;
	registro[NOMBRE] = nombre;
	registro[SUELDO] = sueldo;

	persona = registro;
}

void imprimeRegistro(void *persona)
{
	int *dni;
	char *nombre;
	double *sueldo;
	void **registro = reinterpret_cast<void**>(persona);
	dni = reinterpret_cast<int*>(registro[DNI]);
	nombre = reinterpret_cast<char*>(registro[NOMBRE]);
	sueldo = reinterpret_cast<double*>(registro[SUELDO]);

	cout.precision(2);
	cout << fixed;
	cout << left << setw(10) << *dni << setw(40) << nombre << right
		 << setw(12) << *sueldo << endl;
}

void liberaEspacios(void *persona)
{
	int *dni;
	char *nombre;
	double *sueldo;
	void **registro = reinterpret_cast<void**>(persona);
	dni = reinterpret_cast<int*>(registro[DNI]);
	nombre = reinterpret_cast<char*>(registro[NOMBRE]);
	sueldo = reinterpret_cast<double*>(registro[SUELDO]);

	delete dni;
	delete nombre;
	delete sueldo;
	delete registro;
}

void* leeRegistro()
{
	int *dni, d;
	char *nombre, buff[100];
	double *sueldo;

	cin >> d;
	if (cin.eof()) return nullptr;

	dni = new int;
	*dni = d;
	cin.get(); 	// sacar la coma
	cin.getline(buff,100,',');
	nombre = new char[strlen(buff)+1];
	strcpy(nombre, buff);
	sueldo = new double;
	cin >> *sueldo;

	void **registro = new void*[3];
	registro[DNI] = dni;
	registro[NOMBRE] = nombre;
	registro[SUELDO] = sueldo;

	return registro;
}
