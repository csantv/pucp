#ifndef INF281_FUNCIONESPARTE02EX1_H
#define INF281_FUNCIONESPARTE02EX1_H

void leerConductores(int *&dni, char **&conductor, char ***&placas);
void imprimirConductores(int *dni, char **conductor, char ***placas);
void leerMultas(double *&multas);
void imprimirMultas(double *multas);
void leerInfraccionesCometidas(int *&dni, char ***&placas, double *&multas, double ***&montosXMultas);
void imprimirInfracCometidas(int *dni, char **conductor, char ***placas, double ***montosXMultas);

int insert_dni(int *&dni, int rdni);
void insert_conductor(char **&conductor, char *rnombre);
void insert_placas(char ***&placas);
void insert_placas(char ***&placas, char *placa, int ind);
void insert_multa(double *&multas, int codigo, double monto);
void init_montosxmultas_arr(char ***&placas, double ***&montosXMultas);
int find_cond_ind(int *dni, int rdni);
int find_veh_ind(char ***placas, int cond_ind, char *placa);

#endif //INF281_FUNCIONESPARTE02EX1_H
