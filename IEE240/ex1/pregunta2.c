#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (512*1024*1024)

int main()
{
    FILE *out_file = fopen("tiempos_exp2.txt", "w"); // write only 

    struct timespec time1, time2;
    
    double tTime;
    int i, j, k;


    int *arr = (int*)malloc(MAX_SIZE * sizeof(int));

    /* ----------------------- */
    /* ---- Experimento 1 ---- */
    /* ----------------------- */
    for(k = 0; k < 5; k++){
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
        for (i = 0; i < MAX_SIZE; i++) arr[i] *= 3; /* LOOP 1 */
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
        tTime = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
        printf("CPU time for loop 1: %.5f secs.\n", tTime);
    }

    printf("\n");
    for (k = 1 ; k <= 1024 ; k <<= 1)
    {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
        for (i = 0; i < MAX_SIZE; i += k) arr[i] *= 3; /* LOOP 2 */
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
        tTime = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
        printf("CPU time for loop 2 (k = %d): %.5f secs.\n", k, tTime);
    }

    printf("\n");
    /* ----------------------- */
    /* ----------------------- */
    /* ----------------------- */

    /* ----------------------- */
    /* ---- Experimento 2 ---- */
    /* ----------------------- */
    for (k = 1 ; k <= 1024 ; k <<= 1)
    {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);

        // modificar 0xFFF segun las especificaciones de la pregunta d i)
        for (i = 0; i < MAX_SIZE; i += k) arr[i & 0x27FFFF] += 3; /* Loop 3 */  

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
        tTime = (double)((time2.tv_sec-time1.tv_sec) + (time2.tv_nsec-time1.tv_nsec)/1e9);
        fprintf(out_file, "%.6f\n", tTime); // write to file 
        printf("CPU time for loop 3 (k = %d): %.6f secs.\n", k, tTime);
                
    }
    /* ----------------------- */
    /* ----------------------- */
    /* ----------------------- */

    free(arr);

    return 0;
}
