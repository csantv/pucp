#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float media(int N, float* arr);
void gen_random(int N, float* arr);
float varianza(int N, float* arr);
extern float asmvarianza(int N, float* arr);

int main()
{
    int N = 10000; float arr[N], var;
    clock_t start, end, total;
    
    srand(time(NULL));
    gen_random(N, arr);

    start = clock();
    var = varianza(N, arr);
    end = clock();
    total = end - start;
    printf("Varianza: %f\n", var);
    printf("Time: %.0f us\n", 1000000 * ((float)total/CLOCKS_PER_SEC));

    start = clock();
    var = asmvarianza(N, arr);
    end = clock();
    total = end - start;
    printf("Varianza: %f\n", var);
    printf("Time: %.0f us\n", 1000000 * ((float)total/CLOCKS_PER_SEC));

    return 0;
}

float varianza(int N, float* arr)
{
    float mu = media(N, arr);
    float va = 0;
    for (int i = 0; i < N; i++) {
        va += pow(arr[i] - mu, 2);
    }
    return va / N;
}

void gen_random(int N, float* arr)
{
    for (int i = 0; i < N; i++) {
        arr[i] = 10000.0 * (float)rand() / (float)RAND_MAX;
    }
}

float media(int N, float* arr)
{
    float m = 0;
    for (int i = 0; i < N; i++) {
        m += arr[i];
    }
    return m / N;
}

