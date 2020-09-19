/* This is a template. Do not modify! */
/* Author: Gabriel J. */
/* IEE240 - Organizacion y Arquitectura de Computadoras */
/* C-wrapper for assembly functions */

#include <stdio.h>
#include <stdlib.h>
#include "readimglib.h"

extern int imhist(char *img, int *hist, int N_size); // *img --> image, *hist --> histogram vector, N_size --> size of vectorized image

int main (int argc, char **argv){
    int i, r;
    int N_bins = 256;     
    int Nrows, Ncols, Ndata;
    char *In;
    int *hist;
    char *filename;

    if (argc < 2){
        strcpy(filename, "./data/goldhill_gray.pgm");
    } else{
        filename = calloc( strlen(argv[1])+1, sizeof(char));
        strcpy(filename, argv[1]);
    }

    // Extraer parametros de la imagen
    read_headppm(filename, &Nrows, &Ncols,"P5");

    In = (char*) malloc(Nrows * Ncols * sizeof(char));
    hist = (int*) calloc(N_bins, sizeof(int));
    Ndata = Nrows * Ncols;
    
    // Leo la imagen
    read_ppm2uchar(filename, In, Ndata, "P5");


    r = imhist(In, hist, Ndata);
    
    // Guardar histograma
    save_data(hist, N_bins, "hist.raw");

    free(In);
    free(hist);

    return 0;
}