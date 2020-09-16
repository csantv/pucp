; vi:ft=nasm
global main
extern scanf
extern printf

segment .data

str1 db "Ingrese el numero: ", 0
str2 db "El numero es: %d ", 10, 0
str3 db "%d", 0

segment .bss

entrada resw 1

segment .text

main:
	push str1
	call printf
	add esp, 4

	push entrada
	push str3
	call scanf
	add esp, 8

	push DWORD [entrada]
	push str2
	call printf

_end:
	mov eax, 1
	mov ebx, 0
	int 80h
