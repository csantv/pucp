#include <stdio.h>
#include <stdlib.h>
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

void matmulNaive(int N, float* A[N], float *B[N], float *C[N])
{
/* FIXME: Completar el método de multiplicacion NAIVE */
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


void matmulBlocking(int N, int bsize, float* A[N], float *B[N], float *C[N])
{
    /* FIXME: Completar el método de multiplicacion utilizando blocking */
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

void free_mat(int N, float *arr[N])
{
    for (int i = 0; i < N; i++) {
        free(arr[i]);
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

int main(int argc, char **argv)
{
    /* FIXME: declaracion de variables */
    int bsize, N;
    if (argc < 3) {
        printf("Error en ingreso de datos.\n");
        return 0;
    }
    /* FIXME: inicializacion de variables */
    N = atoi(argv[1]);
    bsize = atoi(argv[2]);
    float *A[N], *B[N], *C[N];
    srand(time(NULL));
    init_matrix(N, A, 1, 0);
    init_matrix(N, B, 1, 0);
    init_matrix(N, C, 1, 1);

    /* ---------------------------------------------------------------------- */
    /* NO MODIFICAR: Esta variables son necesarias para la medición de tiempo */
    struct timespec time1, time2;
    double timeBlocking, timeNaive;
    /* ---------------------------------------------------------------------- */
    
    if (N < 8) {
        printf("Metodo Blocking:\n");
        printf("Matriz A:\n");
        print_mat(N, A);
        printf("Matriz B:\n");
        print_mat(N, B);
    }
    
    /* Este es un ejemplo del uso de la función clock_gettime */ 
    /* Revisar las instrucciones --> debe calcula la mediana de 15 ejecuciones de su funcion!! */
    double times[15];
    double medianBlocking;
    for (int i = 0; i < 15; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
        matmulBlocking(N, bsize, A, B, C);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
        timeBlocking = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
        times[i] = timeBlocking;
    }
    bubbleSort(times, 15);
    medianBlocking = times[7];
    if (N < 8) { 
        printf("Matriz resultado:\n");
        print_mat(N, C);
    }
    printf("El tiempo con blocking es: %.5f s\n", medianBlocking); 

    if (N < 8) {
        printf("Metodo Naive:\n");
        printf("Matriz A:\n");
        print_mat(N, A);
        printf("Matriz B:\n");
        print_mat(N, B);
    }

    /* Este es un ejemplo del uso de la función clock_gettime */ 
    /* Revisar las instrucciones --> debe calcula la mediana de 15 ejecuciones de su funcion!! */
    double medianNaive;
    for (int i = 0; i < 15; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
        matmulNaive(N, A, B, C);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
        free_mat(N, C);
        init_matrix(N, C, 1, 1);
        timeNaive = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
        times[i] = timeNaive;
    }
    bubbleSort(times, 15);
    medianNaive = times[7];
    if (N < 8) { 
        printf("Matriz resultado:\n");
        print_mat(N, C);
    }
    printf("El tiempo naive es: %.5f s\n", medianNaive); 

    /* Completar para el calculo del SpeedUP */
    printf("El speed-up es: %.2f \n", medianNaive / medianBlocking);

    free_mat(N, A);
    free_mat(N, B);

    return 0;

}
