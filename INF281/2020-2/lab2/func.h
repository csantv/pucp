/*
 * CODIGO: 20171878
 * NOMBRE: TORO VERA CARLOS SANTOS
 */

#ifndef INF281_FUNC_H
#define INF281_FUNC_H

#include <fstream>

void generar_notas_bin();
void insert_notas_bin(int, int, int, char*, int, double, int, int, int);
void generar_alumnos_bin();
void insert_alumnos_bin(std::ostream& alumnBin, int cod, int yy, int fac, char* name_alumn, char* name_fac,
                        double total_cur, double total_cred_apro, double total_cred_des, double sum_nota_aprob,
                        double sum_nota_des, double prom_gen_cur, double prom_gen_apro, double relacion_aprob_cred);
void generar_reporte_notas();
void generar_reporte_alumnos();
void completar_camp_num_alumnos();
void read_notas_bin(std::istream& notasBin, int& cod, int& yy_in, int& fac, char* nom_cur,
                    int& cur_fac, int& nota, int& sem, int& yy,
                    double& cred);
void read_alumn_bin(std::istream& alumnBin, int& cod, int& yy, int& fac, char* name_alumn, char* name_fac,
                    double& total_cur, double& total_cred_apro, double& total_cred_des, double& sum_nota_aprob,
                    double& sum_nota_des, double& prom_gen_cur, double& prom_gen_apro, double& relacion_aprob_cred);

#endif
