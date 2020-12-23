#include <stdio.h>
#include <stdlib.h>

void saxpy(int n, float *y, float *x, float m);
extern void saxpyASM(int n, float *y, float *x, float m);
extern void saxpyASMSIMD(int n, float *y, float *x, float m);

void print_arr(float *arr, int n);

int main(int argc, char **argv)
{
	float m = 3;
	int max = 16, n = 16;

	float *y = calloc(n, sizeof(float)), *x = calloc(n, sizeof(float));
	for (int i = 0; i < max; i++) x[i] = i;

	saxpy(n, y, x, m);

	saxpyASM(n, y, x, m);

	free(y);
	free(x);

	return 0;
}

void saxpy(int n, float *y, float *x, float m)
{
	for (int i = 0; i < n; i++) {
		y[i] += x[i] * m;
	}
}

void print_arr(float *arr, int n)
{
	for (int i = 0; i < n; i++) {
		printf("%.2f ", arr[i]);
	}
	puts("");
}
