#ifndef ALGORITHMS_N_QUEENS_H
#define ALGORITHMS_N_QUEENS_H

typedef enum {false, true} bool;

bool is_safe(int n, int [n][n], int, int);
bool solve_nq(int n, int [n][n], int);
void print_board(int n, int [n][n]);

#endif
