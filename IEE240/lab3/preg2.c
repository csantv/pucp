#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void init_matrix(int N, float *mat[N], int init_vals, int zero)
{
    int max = 150;
    for (int i = 0; i < N; i++) {
        mat[i] = malloc(N*sizeof(float));
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

void transp_row_major(int N, float *A[N], float *B[N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[j][i] = A[i][j];
        }
    }
}

void transp_col_major(int N, float *A[N], float *B[N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = A[j][i];
        }
    }
}

void swap(double *xp, double *yp) 
{ 
    double temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void bubbleSort(double arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++) {
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++) {
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]);
       }
   }  
} 

void free_mat(int N, float *arr[N])
{
    for (int i = 0; i < N; i++) {
        free(arr[i]);
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

int main(int argc, char const *argv[])
{
        
    /* ---------------------------------------------------------------------- */
    /* NO MODIFICAR: Esta variables son necesarias para la medición de tiempo */    
    double timeTranspose;
    struct timespec time1, time2;
    /* ---------------------------------------------------------------------- */

    /* FIXME: declaracion de variables */
    int N;
    double times[15], timeRM, timeCM;
    if (argc < 2) {
        printf("Error en ingreso de datos.\n");
        return 0;
    }

    /* FIXME: inicializacion de variables */
    N = atoi(argv[1]);
    float *A[N], *B[N], *C[N];
    srand(time(NULL));
    init_matrix(N, A, 1, 0);
    init_matrix(N, B, 0, 0);

    printf("\nRow Major\n");
    if (N < 8) {
        printf("Matriz original:\n");
        print_mat(N, A);
    }
 
    // Transpuesta (row-major)
    for (int i = 0; i < 15; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
        transp_row_major(N, A, B);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
        timeTranspose = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
        times[i] = timeTranspose;
    }

    if (N < 8) {
        printf("Matriz resultante:\n");
        print_mat(N, B);
    }

    bubbleSort(times, 15);
    timeTranspose = times[7];
    timeRM = timeTranspose;
    printf("El tiempo de ejecución es: %.5f s\n", timeTranspose);

    printf("\nCol Major\n");
    if (N < 8) {
        printf("Matriz original:\n");
        print_mat(N, A);
    }
    
    for (int i = 0; i < 15; i++) {
        // Transpuesta (col-major)
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
        transp_col_major(N, A, B);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
        timeTranspose = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
        times[i] = timeTranspose;
    }

    if (N < 8) {
        printf("Matriz resultante:\n");
        print_mat(N, B);
    }

    bubbleSort(times, 15);
    timeTranspose = times[7];
    timeCM = timeTranspose;
    printf("El tiempo de ejecución es: %.5f s\n", timeTranspose);

    /* Completar para el calculo del SpeedUP */
    printf("El speed-up es: %.2f \n", timeCM/timeRM);

    free_mat(N, A);
    free_mat(N, B);

    return 0;
}
