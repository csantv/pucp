nasm -f elf64 -g -F dwarf geometricSerieASM.asm -o geometricSerieASM.o
gcc -g -O0 geometricSerieASM.o preg2.c -o preg2 -lm
./preg2 0.2 3 100