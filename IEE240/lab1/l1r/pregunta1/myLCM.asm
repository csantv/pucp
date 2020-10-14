; Escriba su código aqui. 
; Siga las intrucciones del README

; vi:ft=nasm

global main
extern scanf
extern printf

section .data

str1 db "Ingrese los valores de a y b:", 10, 0
str2 db "%d %d", 0
str3 db "El LCM de %d y %d es: %d", 10, 0
err1 db "Error en el ingreso de datos.", 10, 0

section .bss

a resb 4
b resb 4
r resb 4

section .text

main:
	; cadena de ingreso
	push str1
	call printf
	add esp, 4

	; ingreso de valores
	push b
	push a
	push str2
	call scanf
	add esp, 12

	; verificar que los datos son correctos
	call verificar

	call lcm
	
	; imprimir resultado
	push DWORD [r]
	push DWORD [b]
	push DWORD [a]
	push str3
	call printf
	add esp, 16

.exit:
	mov eax, 1
	mov ebx, 0
	int 80h

; halla el maximo de 2 numeros
; 1er -> eax
; 2do -> ebx
; max -> eax
max:
	cmp eax, ebx
	cmovb eax, ebx
	ret

; halla el minimo de 2 numeros
; 1er -> eax
; 2do -> ebx
; min -> eax
min:
	cmp eax, ebx
	cmova eax, ebx
	ret

verificar:
	; simple comparacion
	; si son <= 0, hay error
	cmp DWORD [a], 0
	jle .err
	cmp DWORD [b], 0
	jle .err
	jmp .noerr
.err:
	push err1
	call printf
	add esp, 4
	jmp main.exit
.noerr:
	ret

lcm:
	xor eax, eax
	xor ebx, ebx

	mov eax, [a]
	mov ebx, [b]
	
	; eax <- i
	; ebx <- mimin
	; ecx <- mymax
	push eax
	call max
	mov ecx, eax
	pop eax
	call min
	mov ebx, eax
	mov eax, ecx
.loop:
	xor edx, edx
	push eax
	div ebx
	pop eax
	cmp edx, 0
	je .exit
	add eax, ecx
	jmp .loop

.exit:
	mov [r], eax
	ret
