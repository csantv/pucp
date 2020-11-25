; vi:ft=nasm
default rel

global gen_pi_est_asm:function

extern pow:function
extern sqrt:function

section .text

; rdi -> *piest
; rsi -> iter
; rdx -> n
; xmm0 -> d
gen_pi_est_asm:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	cmove rsi, rax

	mov rcx, rsi
	mov [n], rdx
	movdqu oword [d], xmm0

.loop:
	movdqu xmm0, oword [d]
	mov rax, 2
	cvtsi2sd xmm1, rax
	divsd xmm0, xmm1
	mov rax, [n]
	cvtsi2sd xmm1, rax
	mulsd xmm0, xmm1
	movsd [rdi], xmm0
	add rdi, 8
	call get_new_n
	call get_new_d
	loop .loop

	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret

get_new_n:
	mov rax, [n]
	mov rdx, 2
	mul rdx
	mov [n], rax
	ret

get_new_d:
	push rdi
	push rcx
	movdqu xmm0, oword [d]
	mov rax, 2
	cvtsi2sd xmm1, rax
	call pow wrt ..plt
	mov rax, 4
	cvtsi2sd xmm1, rax
	divsd xmm0, xmm1
	mov rax, -1
	cvtsi2sd xmm1, rax
	mulsd xmm0, xmm1
	mov rax, 1
	cvtsi2sd xmm1, rax
	addsd xmm0, xmm1
	call sqrt wrt ..plt
	mov rax, -2
	cvtsi2sd xmm1, rax
	mulsd xmm0, xmm1
	mov rax, 2
	cvtsi2sd xmm1, rax
	addsd xmm0, xmm1
	call sqrt wrt ..plt
	movdqu oword [d], xmm0
	pop rcx
	pop rdi
	ret

section .bss

n resb 8
d resb 8
