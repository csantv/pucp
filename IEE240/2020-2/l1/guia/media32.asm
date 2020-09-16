; vi:ft=nasm

segment .data

	SYS_EXIT	equ 1
	SYS_READ	equ 3
	SYS_WRITE	equ 4
	STDIN		equ 0
	STDOUT		equ 1
	num1 dd 8
	num2 dd 4
	num3 dd 6
	message db "La media es: %d", 10, 0

segment .bss
segment .text
	global main
	extern printf
main:

;siempre limpiar
	mov eax, 0
	mov ebx, 0
	mov ecx, 0
	mov edx, 0
;-----------------
	mov eax, [num1]
	mov ebx, [num2]
	add eax, ebx
	mov ebx, [num3]
	add eax, ebx
	mov ebx, 3
	idiv ebx
	push eax
	push message
	call printf
	mov eax, SYS_EXIT
	xor ebx, ebx
	int 0x80
