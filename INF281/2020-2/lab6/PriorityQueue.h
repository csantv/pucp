//
// Created by Carlos on 11/13/2020.
//

#ifndef INF281_PRIORITYQUEUE_H
#define INF281_PRIORITYQUEUE_H

enum NODO {DATO, ANT, SIG};
enum DATONODO {PRIO, VAL};
enum COLA {INI, FIN};

void crear_cola_prioridad(void *&cola);
void encolar(void *&cola, void *prio, void *val, int (*comp) (const void*, const void*));
void* desencolar(void *&cola);
void prueba(void *&cola, void (*print) (const void*));

#endif //INF281_PRIORITYQUEUE_H
