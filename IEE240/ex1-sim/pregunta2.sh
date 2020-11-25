#!/bin/bash
# Coloque debajo de este comentario los comandos para en ensamblar, compilar, y ejecutar sus codigos (nasm, gcc, ./)
nasm -f elf64 -g -Fdwarf taylor_sin.s -o taylor_sinasm.o
gcc -g -O0 taylor_sinasm.o taylor_sin.c -o preg2 -lm
./preg2 $@
