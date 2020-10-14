; vi:ft=nasm

global main
extern printf

segment .data

SYS_READ equ 3
SYS_WRITE equ 4
SYS_EXIT equ 1
STDIN equ 0
STDOUT equ 1

message db "Hello, %d", 10, 0

segment .text

main:
	
	mov ecx, 10
	push ecx

	; imprimir
	push ecx
	push message		; aca ecx cambia
	call printf
	add esp, 8

	; devolver el valor de ecx
	pop ecx

	; ecx = 10 otra vez aca
	push ecx
	push message
	call printf

_end:
	mov eax, SYS_EXIT
	mov ebx, STDIN
	int 80h

