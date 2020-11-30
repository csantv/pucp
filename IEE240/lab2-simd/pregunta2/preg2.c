#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern float geometricSerieASM (int a, int N, float x);
float geometricSerie (int a, int N, float x);

int main(int argc, char const *argv[]){
    
    clock_t start, stop, t1, t2;

    float timeC, timeASM;
    float yC, yASM;
    int N = 100;
    int a = 3;
    float x = 0.2;

    /* Validar que el usuario ingreso el valor de N y que sea mayor a 0 */
    if (argc < 4){
        printf("Utilizando valores default x = 0.2, a = 3, N = 100\n");
    } else{
        x = atof(argv[1]);
        a = atoi(argv[2]);
        N = atoi(argv[3]);
        // verificaciones
        if (x >= 1) {
            printf("Error: por condicion de desigualdad no se acepta x.\n");
            return 1;
        }
        if (N <= 0) {
            printf("Error: N debe ser mayor e igual que 0.\n");
            return 1;
        }
        printf("Utilizando valores x = %.2f, a = %d, N = %d\n", x, a, N);
    }

    /* FIXME: llamar a las funciones en C y ASM y medir los tiempos de cada una para calcular el SU */
    float cres, asmres, realres;
    start = clock();
    cres = geometricSerie(a, N, x);
    stop = clock();
    t1 = (float)(stop - start);

    start = clock();
    asmres = geometricSerieASM(a, N, x);
    stop = clock();
    t2 = (float)(stop - start);
    /* FIXME: cálculo del valor de la sumatoria utilizando la división a/1-x */
    realres = a / (1 - x);
    

    /* FIXME: impresiones de diferencia de resultados y SU */
    printf("La diferencia utilizando la funcion en C es de %.4f\n", realres - cres);
    printf("La diferencia utilizando la funcion en ASM es de %.4f\n", realres - asmres);
    printf("El speed-up es: %.2f\n", 1000000.0 * (t1-t2) / CLOCKS_PER_SEC);

    return 0;
}


float geometricSerie (int a, int N, float x){
/* FIXME: calcular la sumatoria de la serie geometrica */
	float sum = 0;
    for (int i = 0; i <= N; i++) {
        sum += pow(x, i);
    }
    return sum * a;
}
