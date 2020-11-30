/* This is a template. */
/* Author: Gabriel J. */
/* IEE240 - Organizacion y Arquitectura de Computadoras */
/* C-wrapper for assembly functions */

#include <stdio.h>
#include <stdlib.h>
#include "readimglib.h"

/* FIXME: Colocar los prototipos de sus funciones */
extern void effectASM(unsigned char *A, unsigned char *B, unsigned char *res, int size, float alpha);
extern void effectSIMD(unsigned char *A, unsigned char *B, unsigned char *res, int size, float alpha);
void effectC(unsigned char *A, unsigned char *B, unsigned char *res, int size, float alpha);
void swap(double *xp, double *yp); 
void bubbleSort(double arr[], int n);

/* ---------------------------------------------- */

int main (int argc, char **argv){ 

    char filenameA[] = "./data/baboon.pgm";
    char filenameB[] = "./data/lena.pgm";

    int Nrows, Ncols, size;
    unsigned char *A, *B, *effasm, *effsimd, *effc;

	float alpha = 1.75;
    struct timespec time1, time2;

	if (argc >= 2) alpha = atof(argv[1]); 

    // Extraer parametros de la imagen --> ambas imagenes tienen el mismo tamaño: no es necesario declarar Nrows y Ncols por imagen!
    read_headppm(filenameA, &Nrows, &Ncols,"P5");
	size = Ncols * Nrows;

    A = calloc(size, sizeof(unsigned char)); /* FIXME: reserva Ncols*Nrows elementos en memoria */
    B = calloc(size, sizeof(unsigned char));/* FIXME: reserva Ncols*Nrows elementos en memoria */
    effasm = calloc(size, sizeof(unsigned char));/* FIXME: reserva Ncols*Nrows elementos en memoria */
    effsimd = calloc(size, sizeof(unsigned char));/* FIXME: reserva Ncols*Nrows elementos en memoria */
    effc = calloc(size, sizeof(unsigned char));/* FIXME: reserva Ncols*Nrows elementos en memoria */
    
    // Leo las imagenes
    read_ppm2uchar(filenameA, A, Nrows*Ncols, "P5");
    read_ppm2uchar(filenameB, B, Nrows*Ncols, "P5");

    /* FIXME: colocar sus funciones */
	double times[5], timec, timeasm, timesimd, tTime;

	for (int i = 0; i < 5; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		effectC(A, B, effc, size, alpha);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
		times[i] = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
	}
	bubbleSort(times, 5);
	tTime = times[2] * 1e6;
	timec = tTime;

	for (int i = 0; i < 5; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		effectASM(A, B, effasm, size, alpha);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
		times[i] = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
	}
	bubbleSort(times, 5);
	tTime = times[2] * 1e6;
	timeasm = tTime;

	for (int i = 0; i < 5; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
		effectSIMD(A, B, effsimd, size, alpha);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
		times[i] = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
	}
	bubbleSort(times, 5);
	tTime = times[2] * 1e6;
	timesimd = tTime;

    // Guardar las imagenes --> Ejemplo:
    write_uchar2ppm("outputImgASM.pgm", effasm, Nrows, Ncols, "P5"); // Guardo en el archivo outputImg,pgm la imagen en A.
    write_uchar2ppm("outputImgSIMD.pgm", effsimd, Nrows, Ncols, "P5"); // Guardo en el archivo outputImg,pgm la imagen en A.
    write_uchar2ppm("outputImgC.pgm", effc, Nrows, Ncols, "P5"); // Guardo en el archivo outputImg,pgm la imagen en A.

	printf("Speedup de ASM respecto de C: %f\n", timec/timeasm);
	printf("Speedup de SIMD respecto de C: %f\n", timec/timesimd);
	printf("Speedup de SIMD respecto de ASM: %f\n", timeasm/timesimd);

    free(A);
    free(B);
    /* FIXME: liberar memoria!! */
	free(effasm);
	free(effc);
	free(effsimd);

    return 0;
}

void effectC(unsigned char *A, unsigned char *B, unsigned char *res, int size, float alpha)
{
	unsigned char alchar = alpha * 255;
	for (int i = 0; i < size; i++) {
		res[i] = B[i] - alpha * (B[i] - A[i]);
	}
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


