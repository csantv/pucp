#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gc/gc.h>

void genVectors(float *v, int TAM);
void cVecSum(float *v, float *u, float *w, int TAM);
extern void asmVecSum(float *v, float *u, float *w, int TAM);
extern void partialAsmVecSum(float *v, float *u, float *w);
void cAsmVecSum(float *v, float *u, float *w, int TAM);

int main()
{
	srand(time(NULL));
	float *v, *u, *wc, *wasm, *wcasm;
	int N = 16;
	int REPS = 20, j = 0;

	posix_memalign((void **)&v, 16, N * sizeof(float));
	posix_memalign((void **)&u, 16, N * sizeof(float));
	posix_memalign((void **)&wc, 16, N * sizeof(float));
	posix_memalign((void **)&wasm, 16, N * sizeof(float));
	posix_memalign((void **)&wcasm, 16, N * sizeof(float));

	genVectors(v, N);
	genVectors(u, N);
	cVecSum(v, u, wc, N);
	asmVecSum(v, u, wasm, N);
	cAsmVecSum(v, u, wcasm, N);

	for (j = 0; j < N; j++) {
		printf("%f\t%f\t%f\n", wc[j], wasm[j], wcasm[j]);
	}

	return 0;
}

void genVectors(float *v, int TAM)
{
	int i = 0;
	float ele = 0.0;
	for (i = 0; i < TAM; i++) {
		ele = (float)(rand()%100);
		ele = (sinf(ele) + cosf(ele)) / 1.4142;
		v[i] = ele;
	}
}

void cVecSum(float *v, float *u, float *w, int TAM)
{
	int i = 0;
	for (i = 0; i < TAM; i++) {
		w[i] = v[i] + u[i];
	}
}

void cAsmVecSum(float *v, float *u, float *w, int TAM)
{
	int i = 0;
	for (i = 0; i < TAM; i += 4) {
		partialAsmVecSum(&v[i], &u[i], &w[i]);
	}
}


