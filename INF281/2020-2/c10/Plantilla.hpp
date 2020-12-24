#ifndef INF281_PLANTILLA_HPP
#define INF281_PLANTILLA_HPP

#include <iostream>

using namespace std;

template <typename T>
class Plantilla {
private:
    T dato;
public:
    Plantilla();

    T getDato() const;
    void setDato(const T &val);

    void leerDato();
    void imprimirDato();
};

template<typename T>
Plantilla<T>::Plantilla() = default;

template<typename T>
T Plantilla<T>::getDato() const
{
    return dato;
}

template<typename T>
void Plantilla<T>::setDato(const T &val)
{
    dato = val;
}

template<typename T>
void Plantilla<T>::leerDato()
{
    cin >> dato;
}

template<typename T>
void Plantilla<T>::imprimirDato()
{
    cout << dato << endl;
}

#endif //INF281_PLANTILLA_HPP
