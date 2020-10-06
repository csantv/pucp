#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Prototipos de funciones de la pregunta 1 */
void avgFilter(float *c, float *v, int N);
extern void avgFilterASM(float *c, float *v, int N);
void genRandomValues(float *v, int tam);
void norm2(float *v, float *r, int N);

int main(int argc, char **argv)
{
    clock_t start, stop, t1, t2;

    float timeC, timeASM;
    float *x, *yC, *yASM;
    int N = 1024;

    srand(time(NULL)); // semilla para la funcion RAND

    /* Validar que el usuario ingreso el valor de N y que sea mayor a 0 */
    if (argc < 2){
        printf("Utilizando tamaño de vector N = 1024\n");
    } else{
        if (atoi(argv[1]) > 0){
            N = atoi(argv[1]);
            printf("Utilizando tamaño de vector N = %d\n", N);
        } else{
            printf("Utilizando tamaño de vector N = %d\n", N);
        }
    }

    /* FIXME: Reservar espacio de memoria en funcion a N */
    x = (float*)malloc(sizeof(float) * N);
    yC = (float*)malloc(sizeof(float) * N);
    yASM = (float*)malloc(sizeof(float) * N);
    /* FIXME: utilizar la función genRandomValues() para incializar el vector x */
    genRandomValues(x, N);
    /* FIXME: llamar a las funciones en C y ASM y medir los tiempos de cada una para calcular el SU */
    start = clock();
    avgFilter(x, yC, N);
    stop = clock();
    t1 = stop - start;

    start = clock();
    avgFilterASM(x, yASM, N);
    stop = clock();
    t2 = stop - start;
    printf("El speed-up es: %.2f\n", 1000000 * ((float)t1 - (float)t2)/CLOCKS_PER_SEC);
    /*
     * SPEED UPS
     * 512 -> 4 us
     * 1024 -> 8 us
     * 2048 -> 12 us
     * 4096 -> 41 us
     */
    
    /* Esta seccion del codigo verifica si sus implementaciones en ASM y C entregan resultados similares */
    norm2(yC,yASM,N);
    free(x);
    free(yC);
    free(yASM);
    return 0;
}

void genRandomValues(float *v, int tam){
/* Funcion para generar valores aleatorios reales */
    float e = 0.0;
    int i = 0;
    for(i = 0; i < tam; i++){
        e = (float)(rand() % tam);
        v[i] = (sinf(e) + cosf(e))*0.707106;
    }
}

void norm2(float *v, float *r, int N){
/* Funcion para revisar si sus calculos fueron correctos */
    float sum = 0.0;
    for (int i = 0; i < N; i++){
        sum += (v[i] - r[i])*(v[i] - r[i]);
    }
    printf("El error entre sus implementaciones es: %.2f\n", sqrt(sum));
}

void avgFilter(float *c, float *v, int N){
/* FIXME: completar la funcion para el algoritmo de filtro promedio movil */
    float n1, n2, n3;
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            n1 = c[i];
        } else {
            n1 = c[i - 1];
        }
        if (i == N - 1) {
            n3 = c[i];
        } else {
            n3 = c[i + 1];
        }
        n2 = c[i];
        v[i] = (n1 + n2 + n3) / 3;
    }
}
