#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int integral(int *a, int N);

void func (int a, int b, int *arr, int N){
//; -------------------------------------------- ;
//; ---------- Escriba aqui su código ---------- ;
//; -------------------------------------------- ;

    if (a == b) {
        arr[0] = 0;
        return;
    }
    arr[0] = 3 * a * a;
    int i = 0, j = 0;
    for (i = a + 1, j = 1; i < b; i++, j++) {
        arr[j] = 6 * i * i;
    }
    arr[j] = 3 * b * b;

//; -------------------------------------------- ;
//; ------------- Fin de su código ------------- ;
//; -------------------------------------------- ;
}

int main (int argc, char **argv){
    int a, b, i, N, r1;
    int *arr;

    if (argc < 3){
        a = 2;
        b = 8;
        N = (b-a)+1;
        printf("Considerando a = 2 y b = 8! ...\n");
    } else{
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        N = (b-a)+1;
    }

    arr = (int*) malloc(N*sizeof(int));
    func(a,b,arr,N);  

    r1 = integral(arr, N);

    printf("La integral de la funcion 3*x^2 es: %d\t",r1);
    
    printf("\n");
    free(arr);

    return 0;
}
