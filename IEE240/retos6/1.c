#include <stdio.h>
#include <math.h>
#include <gc/gc.h>
#include <stdlib.h>
#include <time.h>

void init_matrix(int N, float *mat[N], int init_vals, int zero)
{
    int max = 5;
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

void naive_mult(int N, float* A[N], float *B[N], float *C[N])
{
    for (int i = 0; i < N; i++) {
        for (int n = 0; n < N; n++) {
            float sum = 0;
            for (int j = 0; j < N; j++) {
                sum += A[i][j] * B[j][n];
            }
            C[i][n] = sum;
        }
    }
}

void blocking_mult(int N, int bsize, float* A[N], float *B[N], float *C[N])
{
    int cols = N / bsize;
    for (int i = 0; i < N; i++) {
        // 1 bloque de A * cada bloque de B
        for (int bega = 0; bega < N; bega += bsize) {
            for (int j = 0; j < cols; j++) {
                int begb = j * bsize;
                int oldbegac = bega;
                for (int k = begb; k < begb + bsize; k++) {
                    float sum = 0;
                    int oldbega = bega;
                    for (int l = begb; l < begb + bsize; l++) {
                        sum += A[i][oldbega++] * B[l][k];
                    }
                    C[i][oldbegac++] += sum;
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    int N = 2048, bsize = 32;
    float *A[N], *B[N], *C[N];
    clock_t begin, end, tnaive, tblocking;
    printf("N = %d\nbsize = %d\n\n", N, bsize);

    srand(time(NULL));
    init_matrix(N, A, 1, 0);
    init_matrix(N, B, 1, 0);
    init_matrix(N, C, 1, 1);

    begin = clock();
    naive_mult(N, A, B, C);
    end = clock();
    tnaive = end - begin;
    printf("Tiempo en C naive: %.0f us\n", 1000000.0 * (float)tnaive / CLOCKS_PER_SEC);

    init_matrix(N, C, 1, 1);

    begin = clock();
    blocking_mult(N, bsize, A, B, C);
    end = clock();
    tblocking = end - begin;
    printf("Tiempo en C blocking: %.0f us\n", 1000000.0 * (float)tblocking / CLOCKS_PER_SEC);

    printf("Speedup: %.2f\n", (float)tnaive / (float)tblocking);

    return 0;
}
