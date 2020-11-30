/* This is a template. Do not modify! */
/* Author: Gabriel J. */
/* IEE240 - Organizacion y Arquitectura de Computadoras */
/* C-wrapper for assembly functions */

#include <stdio.h>
#include <stdlib.h>
#include "readimglib.h"

extern int imneg(char *img, char *hist, int N_size); // *img --> image, *out --> output image, N_size --> size of vectorized image

int main (int argc, char **argv){
    int i, r;
    
    int Nrows, Ncols, Ndata;
    char *In, *Out;
    char *filename;

    if (argc < 2){
        filename = calloc( 25, sizeof(char));
        strcpy(filename, "./data/goldhill_gray.pgm");
    } else{
        filename = calloc( strlen(argv[1])+1, sizeof(char));
        strcpy(filename, argv[1]);
    }

    // Extraer parametros de la imagen
    read_headppm(filename, &Nrows, &Ncols,"P5");

    Ndata = Nrows * Ncols;
    In = (char*) malloc(Ndata * sizeof(char));
    Out = (char*) calloc(Ndata, sizeof(char));
    
    // Leo la imagen
    read_ppm2uchar(filename, In, Ndata, "P5");

    r = imneg(In, Out, Ndata);
    
    // Guardar imagen
    write_uchar2ppm("./output.pgm", Out, Nrows, Ncols, "P5");

    free(In);
    free(Out);

    return 0;
}
