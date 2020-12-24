//
// Created by cst on 12/18/20.
//

#ifndef INF281_PLLISTA_HPP
#define INF281_PLLISTA_HPP

#include "PlNodo.hpp"
#include <fstream>

template<typename T>
class PlLista {
private:
    PlNodo<T> *lista;
    void imprimirRecPriv(std::ofstream &, PlNodo<T>*);

public:
    PlLista();
    virtual ~PlLista();

    void crear(const char *);
    void insertar(const T&);
    void imprimir(const char *);
    void imprimirRec(const char*);
};

template<typename T>
PlLista<T>::PlLista()
{
    lista = nullptr;
}

template<typename T>
PlLista<T>::~PlLista()
{
    PlNodo<T> *sale;

    while (lista) {
        sale = lista;
        lista = lista->sig;
        delete sale;
    }
}

template<typename T>
void PlLista<T>::imprimirRecPriv(std::ofstream &, PlNodo<T> *) {

}

template<typename T>
void PlLista<T>::crear(const char *nombArch)
{
    using namespace std;

    ifstream arch(nombArch, ios::in);
    if (!arch) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }

    T dato;
    while (true) {
        arch >> dato;
        if (arch.eof()) break;
        insertar(dato);
    }
}

template<typename T>
void PlLista<T>::insertar(const T &dato)
{
    PlNodo<T> *p = lista, *ant = nullptr, *nuevo;

    nuevo = new PlNodo<T>;
    nuevo->dato = dato;

    while (p) {
        if (p->dato > dato) break;
        ant = p;
        p = p->sig;
    }
    nuevo->sig = p;
    if (ant != nullptr) ant->sig = nuevo;
    else lista = nuevo;
}

template<typename T>
void PlLista<T>::imprimir(const char *)
{

}

template<typename T>
void PlLista<T>::imprimirRec(const char *)
{

}

#endif //INF281_PLLISTA_HPP
