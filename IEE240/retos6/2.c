#include <stdio.h>
#include <gc/gc.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void init_matrix(int N, float *mat[N], int init_vals, int zero)
{
    int max = 20;
    for (int i = 0; i < N; i++) {
        mat[i] = GC_malloc(N*sizeof(float));
        if (init_vals) {
            for (int j = 0; j < N; j++) {
                float val = 0;
                if (!zero) {
                    val = rand() % max;
                }
                mat[i][j] = val;
            }
        }
    }
}

void naive_transp(int N, float *orig[N], float *dest[N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dest[j][i] = orig[i][j];
        }
    }
}

void blocking_transp(int N, int bsize, float* orig[N], float *dest[N])
{
    for (int i = 0; i < N; i += bsize) {
        for (int j = 0; j < N; j += bsize) {
            for (int m = i; m < i + bsize; m++) {
                for (int n = j; n < j + bsize; n++) {
                    dest[n][m] = orig[m][n];
                }
            }
        }
    }
}

void print_mat(int N, float *arr[N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3.0f ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    int N = 4096;
    int bsize = 16;
    srand(time(NULL));
    clock_t begin, end, tnaive, tblocking;
    printf("N = %d\nbsize = %d\n\n", N, bsize);

    // iniciar matrices
    float *orig[N], *dest[N];
    init_matrix(N, orig, 1, 0);
    init_matrix(N, dest, 0, 0);

    begin = clock();
    naive_transp(N, orig, dest);
    end = clock();
    tnaive = end - begin;

    init_matrix(N, dest, 0, 0);
    begin = clock();
    blocking_transp(N, bsize, orig, dest);
    end = clock();
    tblocking = end - begin;

    // imprimir tiempos
    printf("Tiempo en C naive: %.0f us\n", 1000000.0 * (float)tnaive / CLOCKS_PER_SEC);
    printf("Tiempo en C blocking: %.0f us\n", 1000000.0 * (float)tblocking / CLOCKS_PER_SEC);
    printf("Speedup: %.2f\n", (float)tnaive / (float)tblocking);

    return 0;
}
