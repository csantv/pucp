; vi:ft=nasm

default rel

global effectSIMD:function

section .text

; rdi -> A
; rsi -> B
; rdx -> C
; rcx -> size
; xmm0 -> alpha
effectSIMD:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx
	
	xorps xmm1, xmm1
	xorps xmm2, xmm2
	xorps xmm3, xmm3
	shufps xmm0, xmm0, 00000000b

.loop:
	; C = B + alpha * (B - A)
	pmovzxbd xmm1, [rdi]
	pmovzxbd xmm2, [rsi]
	cvtdq2ps xmm1, xmm1
	cvtdq2ps xmm2, xmm2
	movdqu xmm3, xmm2
	subps xmm2, xmm1
	mulps xmm2, xmm0
	addps xmm2, xmm3
	cvtps2dq xmm2, xmm2
	movaps [dat1], xmm2
	call saveimg	
	add rdi, 4
	add rsi, 4
	sub rcx, 4
	jrcxz .end
	jmp .loop
.end:
	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret

saveimg:
	mov eax, [dat1]
	mov [rdx], ax
	inc rdx
	mov eax, [dat1+4]
	mov [rdx], ax
	inc rdx
	mov eax, [dat1+8]
	mov [rdx], ax
	inc rdx
	mov eax, [dat1+12]
	mov [rdx], ax
	inc rdx
	ret

section .bss
align 16
dat1 resb 16
