//
// Created by Carlos on 11/13/2020.
//

#include "PriorityQueue.h"

void crear_cola_prioridad(void *&cola)
{
    void **reg = new void*[2];
    void **nodo = new void*[3]();
    reg[INI] = nodo;
    reg[FIN] = nodo;
    cola = reg;
}

void encolar(void *&cola, void *prio, void *val, int (*comp) (const void*, const void*))
{
    void **&reg = reinterpret_cast<void**&>(cola), **run = static_cast<void**>(reg[FIN]), **ant = nullptr;
    void **nododato = new void*[2], **nodo = new void*[3]();
    nododato[PRIO] = prio;
    nododato[VAL] = val;
    nodo[DATO] = nododato;
    if (!*run) {
        run[DATO] = nododato;
        return;
    }
    while (run) {
        if (comp(run[DATO], nododato) >= 0) break;
        ant = run;
        run = static_cast<void**>(run[ANT]);
    }
    if (!run) {
        nodo[SIG] = ant;
        ant[ANT] = nodo;
        reg[INI] = nodo;
    } else if (!ant) {
        nodo[ANT] = run;
        run[SIG] = nodo;
        reg[FIN] = nodo;
    } else {
        nodo[SIG] = ant;
        nodo[ANT] = run;
        run[SIG] = nodo;
        ant[ANT] = nodo;
    }
}

void* desencolar(void *&cola)
{
    void **&reg = reinterpret_cast<void**&>(cola);
    if (*reg) {
        void **nodo = reinterpret_cast<void**>(reg[INI]);
        reg[INI] = nodo[SIG];
        return nodo;
    }
    return nullptr;
}

void prueba(void *&cola, void (*print) (const void*))
{
    void **reg = static_cast<void**>(cola);
    void **run = static_cast<void**>(reg[INI]);
    while (run) {
        print(run[DATO]);
        run = static_cast<void**>(run[SIG]);
    }
}