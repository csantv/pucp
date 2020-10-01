; vi:ft=nasm
global asmvarianza

section .text

; len -> rdi
; *arr -> rsi
asmvarianza:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx
	push rsi
	call asmmedia
	pop rsi
	movss xmm2, xmm0
	xorps xmm0, xmm0
	mov rcx, rdi
.loop:
	movss xmm1, [rsi]
	subss xmm1, xmm2
	mulss xmm1, xmm1
	addss xmm0, xmm1
	add rsi, 4
	loop .loop
	cvtsi2ss xmm1, rdi
	divss xmm0, xmm1
	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret

asmmedia:
	mov rcx, rdi
	cvtsi2ss xmm1, rdi
	xorps xmm0, xmm0
.loop:
	addss xmm0, [rsi]
	add rsi, 4
	loop .loop
	divss xmm0, xmm1
	ret
