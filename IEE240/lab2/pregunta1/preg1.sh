nasm -f elf64 -g -F dwarf avgFilterASM.asm -o avgFilterASM.o
gcc -g -O0 avgFilterASM.o preg1.c -o preg1 -lm
./preg1 10
