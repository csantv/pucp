; vi:ft=nasm
default rel

global weight_sum:function

section .text

; rdi -> N
; rsi -> M
; rdx -> x
; rcx -> b
weight_sum:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	mov r8, rsi 	; M
	mov r9, rdx 	; x
	mov r10, rcx 	; b

	mov rcx, rdi
.loop:
	xorps xmm0, xmm0
	push rcx
	mov rcx, rdi
	push r9
	.loop2:
		movss xmm1, [r8]
		mulss xmm1, [r9]
		addss xmm0, xmm1
		add r8, 4
		add r9, 4
		loop .loop2
	pop r9
	pop rcx
	movss [r10], xmm0
	add r10, 4
	loop .loop


	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret
