#include "PriorityQueuePacientes.hpp"
#include "PriorityQueue.h"

int main(int argc, char **argv)
{
    void *cola;
    crear_cola_prioridad(cola);
    cargar_cola(cola);
    atender_pacientes(cola);
    return 0;
}
