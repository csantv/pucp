#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

extern void weight_sum(int N, float* M, float* x, float* b);

void ini_array(float *arr, int numel, float var, float media) {

	int i, k;
	float temp, desv;

	desv = (float) sqrt((double) var);

	srand(time(NULL));

	for(i=0; i<numel; ++i){
		temp=0;
		for (k=0;k<100;k++) temp += (float) rand()/RAND_MAX;
		arr[i] = desv*sqrt((float) 3/25)*(temp-(float)50) + media;
	}

	return;
}

void vec_sum(float *M, float *x, int numel) {
    for (int i = 0; i < numel; i++) {
        for (int j = 0; j < numel; j++) {
            M[j * 10 + i] *= x[i];
        }
    }
}

void weight_vec(float *M, float *b, int numel) {
    for (int i = 0; i < numel; i++) {
        float sum = 0;
        for (int j = 0; j < numel; j++) {
            sum += M[i * 10 + j];
        }
        b[i] = sum;
    }
}

int main() {
    int numel = 2048;
    clock_t start_t, end_t, total_t, timec, timeasm;

	// reserva de memoria
	float *M = (float *) calloc(numel*numel, sizeof(float));
	float *x = (float *) calloc(numel, sizeof(float));
	float *b = (float *) calloc(numel, sizeof(float));

    // inicializacion de M y x
	ini_array(M, numel*numel, 1.0, 0.0);
	ini_array(x, numel, 1.0, 0.0);

    // version optimizada
    start_t = clock();
    weight_sum(numel, M, x, b);
    end_t = clock();
    timeasm = end_t - start_t;
    printf("Tiempo en ASM: %.0f us\n", 1e6 * (float)timeasm / CLOCKS_PER_SEC);

	// medicion del tiempo empieza ahora
    start_t = clock();
	vec_sum(M, x, numel);
	weight_vec(M, b, numel);
    end_t = clock();
    timec = end_t - start_t;
	// medicion del tiempo termina ahora

	// imprimir tiempo aqui
    printf("Tiempo en C: %.0f us\n", 1e6 * (float)timec / CLOCKS_PER_SEC);

    // speedup
    printf("Speedup: %.2f\n", (float)timec / (float)timeasm);
	return 0;

}
