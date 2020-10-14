; Escriba su código aqui. 
; Siga las intrucciones del README

; vi:ft=nasm

global main
extern scanf
extern printf

section .data

str1 db "Ingrese los valores de a y b:", 10, 0
str2 db "%d %d", 0
str3 db "El GCM de %d y %d es: %d", 10, 0
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

	; hallar el maximo comun divisor
	call gcm

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


gcm:
	xor eax, eax
	xor ebx, ebx
	
	; r0 <- eax
	; r1 <- ebx
	; r2 <- edx

	mov eax, [a]
	mov ebx, [b]

.loop:
	xor edx, edx
	div ebx			; r2 <- r0 % r1
	mov eax, ebx	; r0 <- r1
	mov ebx, edx	; r1 <- r2

	cmp ebx, 0
	jne .loop
	
	mov [r], eax
	ret
