#include <stdio.h>
#include <math.h>
#include <time.h>

float calc_lim(int n)
{
    return pow(1.0 + (float)1/n, n);
}

extern float asm_calc_lim(int n);
extern float binpow_lim(int n);

int main()
{
    int n = 1000; float lim;
    clock_t start, end, total;

    start = clock();
    lim = calc_lim(n);
    end = clock();
    total = end - start;
    printf("Limite: %f\n", lim);
    printf("Time: %.0f us\n", 1000000 * ((float)total/CLOCKS_PER_SEC));

    start = clock();
    lim = asm_calc_lim(n);
    end = clock();
    total = end - start;
    printf("Limite: %f\n", lim);
    printf("Time: %.0f us\n", 1000000 * ((float)total/CLOCKS_PER_SEC));

    start = clock();
    lim = binpow_lim(n);
    end = clock();
    total = end - start;
    printf("Limite: %f\n", lim);
    printf("Time: %.0f us\n", 1000000 * ((float)total/CLOCKS_PER_SEC));
    return 0;
}

