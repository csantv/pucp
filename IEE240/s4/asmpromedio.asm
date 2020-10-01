; vi:ft=nasm
global asmPromedio

section .text

asmPromedio:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	; len: rdi, *v: rsi, *prom rdx
	xorps xmm0, xmm0
	xorps xmm1, xmm1
	xorps xmm2, xmm2

	cvtsi2ss xmm2, rdi
	cmp rdi, 0
	je exit
	
bucle:
	movss xmm0, [rsi]
	addss xmm1, xmm0
	add rsi, 4
	dec rdi
	jnz bucle

	divss xmm1, xmm2

exit:

	movss [rdx], xmm1
	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret
