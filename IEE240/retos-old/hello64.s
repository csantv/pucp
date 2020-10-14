; vi:ft=nasm

default rel

global main:function

extern printf:function
extern scanf:function
extern exit:function

section .bss

name resb 50

section .rodata

msg1 db "Hola %s", 10, 0
msg2 db "Nombre: ", 0
fmt db "%s", 0

section .text

main:
	push rbx

	lea rdi, [msg2]
	xor eax, eax
	call printf wrt ..plt

	lea rdi, [fmt]
	lea rsi, [name]
	call scanf wrt ..plt

	lea rdi, [msg1]
	lea rsi, [name]
	call printf wrt ..plt

	pop rbx

	xor edi, edi
	call exit wrt ..plt
