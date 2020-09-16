#include <stdio.h>

extern int fib(int n);

int main(int argc, char** argv)
{
    printf("%d\n", fib(47));
    return 0;
}
