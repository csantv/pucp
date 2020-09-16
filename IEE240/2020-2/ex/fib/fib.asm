; vi:ft=nasm
section .data

SYS_READ equ 3
SYS_WRITE equ 4
SYS_EXIT equ 1
STDIN equ 0
STDOUT equ 1

num db 10
mensaje db "%d\n", 10, 0
mensaje2 db "No es valido", 10, 0

section .text

global main
extern printf

main:
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx

	mov eax, [num]
	cmp eax, 0
	jl print_novalido

fibo:
	cmp eax, 0
	je f_cero
	cmp eax, 1
	je f_uno
	jmp f_loop

f_cero:
	jmp print_num
f_uno:
	jmp print_num

f_loop:
	mov ecx, 0
	mov ebx, 1
	mov eax, 0
	mov edx, 2

loop_calc:
	add eax, ebx
	cmp dl, byte [num]
	je print_num
	mov ecx, ebx
	mov ebx, eax
	mov eax, ecx
	inc edx
	jmp loop_calc

print_novalido:
	push mensaje2
	jmp print

print_num:
	push eax
	push mensaje

print:
	call printf
end:
	mov eax, SYS_EXIT
	mov ebx, STDIN
	int 80h
