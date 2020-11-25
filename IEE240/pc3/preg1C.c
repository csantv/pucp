#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef unsigned long long int lint;

extern int func_ASM(lint *arr, int N, int P);
int func_c(lint *arr, int N, int P);
int func2_c(lint *arr, int N, int P);
void gen_fib(lint *arr, int N);
void print_arr(lint *arr, int N);
void swap(double *xp, double *yp);
void bubbleSort(double arr[], int n);

int main(int argc, char **argv)
{
	int N, P;
	if (argc < 3) {
		fprintf(stderr, "minimo 2 argumentos.\n");
		exit(1);
	}
	N = atoi(argv[1]) + 1;
	P = atoi(argv[2]);
	if (N < 2) {
		fprintf(stderr, "error de argumentos.\n");
		exit(1);
	}
    struct timespec time1, time2;
	double times[5], tTime, timec, timeasm, timec2;
	lint *arr = malloc(N * sizeof(lint));
	int res;

	// tiempo en C
	printf("\nfunc_c\n\n");
	for (int i = 0; i < 5; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		gen_fib(arr, N);
		res = func_c(arr, N, P);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
		times[i] = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
	}
	bubbleSort(times, 5);
	tTime = times[2] * 1e6;
	timec = tTime;
	print_arr(arr, N);
	printf("Resultado = %d\n", res);
	printf("Tiempo: %lf\n", timec);

	// para ASM
	printf("\nfunc_ASM\n\n");
	for (int i = 0; i < 5; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		gen_fib(arr, N);
		res = func_ASM(arr, N, P);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
		times[i] = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
	}
	bubbleSort(times, 5);
	tTime = times[2] * 1e6;
	timeasm = tTime;
	print_arr(arr, N);
	printf("Resultado = %d\n", res);
	printf("Tiempo: %lf\n", timeasm);
	printf("Speedup: %lf\n", timec/timeasm);

	// func2_c
	// tiempo en C
	printf("\nfunc2_c\n\n");
	for (int i = 0; i < 5; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		gen_fib(arr, N);
		res = func2_c(arr, N, P);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
		times[i] = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
	}
	bubbleSort(times, 5);
	tTime = times[2] * 1e6;
	timec2 = tTime;
	print_arr(arr, N);
	printf("Resultado = %d\n", res);
	printf("Tiempo: %lf\n", timec2);
	printf("Speedup respecto a func_c: %lf\n", timec2/timec);


	free(arr);

	return 0;
}

void print_arr(lint *arr, int N)
{
	printf("Arreglo = [%llu", arr[0]);
	for (int i = 1; i < N; i++) {
		printf(", %llu", arr[i]);
	}
	printf("]\n");
}

void gen_fib(lint *arr, int N)
{
	arr[0] = 0;
	arr[1] = 1;
	for (int i = 2; i < N; i++) {
		arr[i] = arr[i - 1] + arr[i - 2];
	}
}

int func_c(lint *arr, int N, int P)
{
	int total = 0;
	for (int i = 0; i < N; i++) {
		if (arr[i] > P) total++;
	}
	return total;
}

int func2_c(lint *arr, int N, int P)
{
	int total = 0;
	for (int i = 0; i < N; i += 3) {	
		if (arr[i] > P) total++;
		if (arr[i+1] > P) total++;
		if (arr[i+2] > P) total++;
	}
	return total;
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

