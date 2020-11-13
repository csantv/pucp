#ifndef INF281_PRIORITYQUEUEPACIENTES_HPP
#define INF281_PRIORITYQUEUEPACIENTES_HPP

#include <fstream>

void cargar_cola(void *&cola);
void atender_pacientes(void *&cola);
void *get_pac_reg(int dni, char *nombre, char tipo, int codigo, double tarifa, double descuento);
int get_prio(char tipo);
int comp_pac(const void* a, const void* b);
double imprime_paciente(std::ofstream &reporte, void *pac);
const char* get_tipo(char tipo);
double get_pago(void *pac);
double get_tarifa(int codigo);

std::ifstream iopen_file(const char* name, std::ios_base::openmode mode = std::ios_base::in);
std::ofstream oopen_file(const char* name, std::ios_base::openmode mode = std::ios_base::out);

#endif //INF281_PRIORITYQUEUEPACIENTES_HPP
