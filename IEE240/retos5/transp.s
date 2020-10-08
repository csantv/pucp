; vi:ft=nasm
default rel

global transvasm:function
extern printf:function

section .text

; rdi -> N
; rsi -> orig
; rdx -> dest
transvasm:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	; guardar N en memoria
	mov qword [N], rdi

	mov r9, 0 		; indice horizontal

	mov rcx, rdi
	mov rdi, rdx
	xor eax, eax
.loop1:
	push rcx
	mov rcx, [N]
	.loop2:
		push rdx
		push rax
		mul qword [N]
		mov rdx, rdi
		add rax, r9
		add rdx, rax
		mov ebx, [rsi]
		mov [rdx], ebx
		add rsi, 4 		; siguiente elemento
		pop rax
		add rax, 4
		pop rdx 		; restaurar indice
		loop .loop2
	add r9, 4
	xor eax, eax
	pop rcx
	loop .loop1

	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret

section .rodata

fmt db "%d", 10, 0

section .bss

N resb 8

