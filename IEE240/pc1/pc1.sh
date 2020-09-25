nasm -f elf32 -o integral.o integral.asm
gcc -m32 -march=i686 -g main.c integral.o -o practica1
./practica1 2 8