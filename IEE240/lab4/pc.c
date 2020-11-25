#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void instructionTest(float *v, float *u, float *w, int N);
void genVectors(float *v, int N);
void printVectors(float *v, int N);

int main(int argc, char **argv)
{
	srand(time(NULL));
	float *v, *u, *w;
	int N = 8;
	posix_memalign((void**)&v, 16, N * sizeof(float));
	posix_memalign((void**)&u, 16, N * sizeof(float));
	posix_memalign((void**)&w, 16, N * sizeof(float));

	genVectors(v, N);
	genVectors(u, N);

	printVectors(v, N);
	// printVectors(u, N);

	instructionTest(v, u, w, N);

	printVectors(w, N);

	return 0;
}

void genVectors(float *v, int N)
{
	float ele;
	for (int i = 0; i < N; i++) {
		ele = (float)(rand() % 100);
		v[i] = ele;
	}
}

void printVectors(float *v, int N)
{
	for (int i = 0; i < N; i++) {
		printf("%.2f ", v[i]);
	}
	printf("\n");
}


