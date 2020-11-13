//
// Created by cst on 11/12/20.
//

#include "ListaGenerica.hpp"

enum Reg {DATO, SIG};

void crearLista(std::ifstream &arch, void *&lista,
                void* (*lee)(std::ifstream&),
                int (*comp) (const void*, const void*))
{
    void *dato;
    lista = nullptr;
    while (true) {
        dato = lee(arch);
        if (dato == nullptr) break;
        insertarLista(lista, dato, comp);
    }
}

void imprimirLista(void *lista, void (*imprime) (void*))
{
    void **ls = static_cast<void**>(lista);
    while (ls) {
        imprime(ls[DATO]);
        ls = static_cast<void**>(ls[SIG]);
    }
}

void eliminarLista(void *lista, void (*elimina) (void*))
{
    void **ls = static_cast<void**>(lista), **sale;
    while (ls) {
        sale = ls;
        ls = static_cast<void**>(ls[SIG]);
        elimina(sale[DATO]);
        delete sale;
    }
}

void insertarLista(void *&lista, void *dato,
                   int (*comp) (const void*, const void*))
{
    void **p = static_cast<void**>(lista), **ant = nullptr, **nuevo;
    nuevo = new void*[2]();
    nuevo[DATO] = dato;
    while (p) {
        if (comp(p[DATO], dato) > 0) break;
        ant = p;
        p = static_cast<void**>(p[SIG]);
    }
    nuevo[SIG] = p;
    if (!ant) lista = nuevo;
    else ant[SIG] = nuevo;
}