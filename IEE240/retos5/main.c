#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void transvasm(int N, int orig[N][N], int dest[N][N]);

void gen_random(int N, int arr[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = rand() % 101;
        }
    }
}

void print_mat(int N, int arr[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void transvc(int N, int orig[N][N], int dest[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dest[j][i] = orig[i][j];
        }
    }
}

int main(int argc, char** argv)
{
    int N = 512;
    int orig[N][N];
    srand(time(NULL));
    gen_random(N, orig);
    int transvarrc[N][N];
    int transvarrasm[N][N];
    time_t ini, end, ctime, asmtime;

    /*
    ini = clock();
    transvc(N, orig, transvarrc);
    end = clock();
    ctime = end - ini;
    printf("%.0f,", 1e6 * (float)ctime/CLOCKS_PER_SEC);*/
    
    ini = clock();
    transvasm(N, orig, transvarrasm);
    end = clock();
    asmtime = end - ini;
    printf("%.0f,", 1e6 * (float)asmtime/CLOCKS_PER_SEC);

    // printf("Speedup: %f\n", 1000000 * ((float)ctime / (float)asmtime)/CLOCKS_PER_SEC);
    // printf("Speedup: %f\n", (float)ctime / (float)asmtime);
    return 0;
}
