//
// Created by cst on 11/12/20.
//

#ifndef INF281_LISTACONENTEROS_HPP
#define INF281_LISTACONENTEROS_HPP

#include <fstream>

void *leeEntero(std::ifstream& arch);
int cmpEntero(const void *d1, const void *d2);
void imprimeEntero(void *d);
void eliminaEntero(void *d);

#endif //INF281_LISTACONENTEROS_HPP
