; vi:ft=nasm

default rel

global factimpASM:function
global powerimpASM:function

section .text

factimpASM:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	lea rcx, [rdi*2 + 1]
	mov rax, 1
	cvtsi2sd xmm0, rax

.loop:
	cvtsi2sd xmm1, rcx
	mulsd xmm0, xmm1
	loop .loop

	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret

; rdi -> x
; rsi -> n
powerimpASM:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	lea rcx, [rsi*2]
	cvtsi2sd xmm0, rdi
	movsd xmm1, xmm0

.loop:
	mulsd xmm0, xmm1
	loop .loop

	xor edx, edx
	mov rax, rsi
	mov rbx, 2
	div rbx
	mov rax, 1
	mov rbx, -1
	cmp rdx, 0
	cmovne rax, rbx

	cvtsi2sd xmm1, rax
	mulsd xmm0, xmm1

	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret
