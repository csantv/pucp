//
// Created by cst on 12/18/20.
//

#ifndef INF281_PLNODO_HPP
#define INF281_PLNODO_HPP

#include "PlLista.hpp"

template <typename T>
class PlNodo {
private:
    T dato;
    PlNodo<T> *sig;

    friend PlLista<T>;
public:
    PlNodo();
    ~PlNodo();
};

template<typename T>
PlNodo<T>::PlNodo()
{
//    dato = nullptr;
    sig = nullptr;
}

template<typename T>
PlNodo<T>::~PlNodo()
{
    delete dato;
}

#endif //INF281_PLNODO_HPP
