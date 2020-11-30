; vi:ft=nasm
; FIXME: completar el codigo ASM. Recuerda los calling conventions de GCC!

global avgFilterASM

section .text

; rdi -> *c
; rsi -> *v
; rdx -> N
avgFilterASM:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	mov rcx, rdx
.loop:
	; centro
	movss xmm0, [rdi]
	; anterior
	cmp rcx, rdx
	je .if_prim
	jne .else_prim
.if_prim:
	lea rax, [rdi]
	jmp .end_prim
.else_prim:
	lea rax, [rdi - 4]
.end_prim:
	movss xmm1, [rax]
	addss xmm0, xmm1
	; siguiente
	cmp rcx, 1
	je .if_fin
	jne .else_fin
.if_fin:
	lea rax, [rdi]
	jmp .end_fin
.else_fin:
	lea rax, [rdi + 4]
.end_fin:
	movss xmm1, [rax]
	addss xmm0, xmm1
	; dividir
	mov rax, 3
	cvtsi2ss xmm1, rax
	divss xmm0, xmm1
	movss [rsi], xmm0
	add rdi, 4
	add rsi, 4
	loop .loop

	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret
