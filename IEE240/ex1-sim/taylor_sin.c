#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void swap(double *xp, double *yp);
void bubbleSort(double arr[], int n);

double factimpC(int n);
double powerimpC(int x, int n);

extern double factimpASM(int n);
extern double powerimpASM(int x, int n);

int main(int argc, char **argv)
{
	int N = atoi(argv[1]);
	int x = 5;
	float res;
	double times[5];
    struct timespec time1, time2;
    double timerun, errorrel;
	double sinref = sin(x);

	printf("sin(5) de math.h => %lf\n", sinref);

	for (int j = 0; j < 5; j++) {
    	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		res = x;
		for (int i = 1; i <= N; i++) {
			res += powerimpC(x, i) / factimpC(i);
		}
    	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    	timerun = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
		times[j] = timerun;
	}
	bubbleSort(times, 5);
	timerun = times[2];
	printf("Tiempo en C: %.2lf\n", timerun * 1e6);
	printf("sin(5) = %.10lf\n", res);
	errorrel = 100 * fabs((sinref - res)/sinref);
	printf("Error C: %.10lf\n", errorrel);

	for (int j = 0; j < 5; j++) {
    	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		res = x;
		for (int i = 1; i <= N; i++) {
			res += powerimpASM(x, i) / factimpASM(i);
		}
    	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    	timerun = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
		times[j] = timerun;
	}
	bubbleSort(times, 5);
	timerun = times[2];

	printf("Tiempo en ASM: %.2lf\n", timerun * 1e6);
	printf("sin(5) = %.10lf\n", res);
	errorrel = 100 * fabs((sinref - res)/sinref);
	printf("Error ASM: %.10lf\n", errorrel);

	return 0;
}

double factimpC(int n)
{
	double res = 1;
	for (int i = 2; i <= 2*n+1; i++) {
		res *= i;
	}
	return res;
}

double powerimpC(int x, int n)
{
	double res = x;
	for (int i = 1; i < 2*n+1; i++) {
		res *= x;
	}
	if (n % 2 != 0) res *= -1;
	return res;
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
