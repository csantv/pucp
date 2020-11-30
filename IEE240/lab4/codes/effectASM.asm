; vi:ft=nasm

default rel

global effectASM:function

section .text

; rdi -> A
; rsi -> B
; rdx -> C
; rcx -> size
; xmm0 -> alpha
effectASM:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx
	
	xorps xmm1, xmm1
	xorps xmm2, xmm2
	xorps xmm3, xmm3
	movss xmm4, xmm0

.loop:
	; C = B + alpha * (B - A)
	movzx rax, byte [rdi]
	movzx rbx, byte [rsi]

	; calcular B - A
	cvtsi2ss xmm1, rax
	cvtsi2ss xmm2, rbx
	movss xmm0, xmm4
	movss xmm3, xmm2

	subss xmm2, xmm1
	mulss xmm0, xmm2
	addss xmm0, xmm3

	cvtss2si eax, xmm0
	mov [rdx], ax
	add rdi, 1
	add rsi, 1
	add rdx, 1
	loop .loop

	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret
