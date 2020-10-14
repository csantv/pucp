#include <stdio.h>
#include <stdlib.h>

extern int es_fuerte(int);

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        if (es_fuerte(num)) {
            printf("El numero %d es fuerte.\n", num);
        } else {
            printf("El numero %d no es fuerte.\n", num);
        }
    }
    return 0;
}
