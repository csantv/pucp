#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void genRandom(int len, int max, float* v);
void promedio(int len, float* v, float* prom);
extern void asmPromedio(int len, float* v, float* prom);

int main()
{
    srand(time(NULL));
    
    clock_t start, stop;

    float *v;
    int len = 912823, max = 100;
    float asmpromedio;
    float cpromedio;

    v = malloc(len*sizeof(float));

    genRandom(len, max, v);
    start = clock();
    asmPromedio(len, v, &asmpromedio);
    stop = clock();
    printf("El promedio en asm es: %.4f\n", asmpromedio);
    printf("El tiempo de asmpromedio es: %.4fus\n", 1e6*(float)(stop - start)/CLOCKS_PER_SEC);
    

    start = clock();

    promedio(len, v, &cpromedio);
    stop = clock();
    printf("El promedio en asm es: %.4f\n", cpromedio);
    printf("El tiempo de asmpromedio es: %.4fus\n", 1e6*(float)(stop - start)/CLOCKS_PER_SEC);

    free(v);

    return 0;
}

void promedio(int len, float* v, float* prom)
{
    float sum = 0;
    for (int i = 0; i < len; i++) {
        sum += v[i];
    }
    *prom = sum / (float)len;
}

void genRandom(int len, int max, float *v)
{
    for (int i = 0; i < len; i++) {
        v[i] = rand() % max;
    }
}
