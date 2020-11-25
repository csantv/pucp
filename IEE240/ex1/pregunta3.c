#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gen_pi_est(double *piest, int iter, int n, double d);
extern void gen_pi_est_asm(double *piest, int iter, int n, double d);

void print_arr(double *arr, int n);
void swap(double *xp, double *yp);
void bubbleSort(double arr[], int n);

int main(int argc, char **argv)
{
	int k = 5;
	if (argc >= 2) {
		k = atoi(argv[1]);
	}
	printf("Usando %d iteraciones.\n\n", k);
	k+=1; 		// n iteraciones devuelven n + 1 resultados
    struct timespec time1, time2;

	// valores iniciales
	int n = 4; double d = sqrt(2);
	double *piest = malloc(k * sizeof(double));
	double times[3], tTime, timec, timeasm;

	// calculo para C
	for (int i = 0; i < 3; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		gen_pi_est(piest, k, n, d);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
		times[i] = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
	}
	bubbleSort(times, 3);
	tTime = times[1] * 1e6;
	timec = tTime;
	printf("Resultados en C:\n");
	print_arr(piest, k);
	printf("Tiempo: %lf us\n", tTime);

	printf("\n");

	// calculo para ASM
	for (int i = 0; i < 3; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		gen_pi_est_asm(piest, k, n, d);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
		times[i] = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
	}
	bubbleSort(times, 3);
	tTime = times[1] * 1e6;
	timeasm = tTime;
	printf("Resultados en ASM:\n");
	print_arr(piest, k);
	printf("Tiempo: %lf us\n", tTime);

	printf("\nSpeedup: %lf\n", timec / timeasm);

	free(piest);
	return 0;
}

void gen_pi_est(double *piest, int iter, int n, double d)
{
	for (int i = 0; i < iter; i++) {
		piest[i] = n * d / 2;
		n *= 2;
		d = sqrt(2 - 2 * sqrt(1 - (pow(d, 2) / 4)));
	}
}

void print_arr(double *arr, int n)
{
	for (int i = 0; i < n; i++) {
		printf("%lf ", arr[i]);
	}
	printf("\n");
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
