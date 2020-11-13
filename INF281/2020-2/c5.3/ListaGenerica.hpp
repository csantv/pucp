//
// Created by cst on 11/12/20.
//

#ifndef INF281_LISTAGENERICA_HPP
#define INF281_LISTAGENERICA_HPP

#include <fstream>

void crearLista(std::ifstream &arch, void *&lista,
                void* (*lee)(std::ifstream&),
                int (*comp) (const void*, const void*));
void imprimirLista(void *lista, void (*imprime) (void*));
void eliminarLista(void *lista, void (*elimina) (void*));
void insertarLista(void *&lista, void *dato,
                   int (*comp) (const void*, const void*));

#endif //INF281_LISTAGENERICA_HPP
