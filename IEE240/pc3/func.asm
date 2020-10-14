; vi:ft=nasm
default rel

global weight_sum:function
global weight_sum2:function

section .bss

x resb 8
zero resb 8
four resb 8

section .text

; rdi -> N
; rsi -> M
; rdx -> x
; rcx -> b
weight_sum2:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	mov r8, rsi 	; M
	mov r9, rdx 	; x
	mov r10, rcx 	; b

	mov rax, rdi
	mov rbx, 4
	mul rbx
	push rax 		; N * 4
	mov rax, rdi
	mul rax
	mov rcx, rax
	pop rax

	; rax -> N * 4
	; rcx -> N * N

	;mov rcx, rdi
	xorps xmm0, xmm0
	xor ebx, ebx
	xor r11d, r11d
	mov qword [x], r9
	mov qword [zero], 0
	mov qword [four], 4
.loop:
	movss xmm0, [r8]
	mulss xmm0, [r9]
	addss xmm0, [r10]
	movss [r10], xmm0
	add r8, 4
	add r9, 4
	add rbx, 4
	cmp rbx, rax
	cmove rbx, [zero]
	cmove r11, [four]
	cmovne r11, [zero]
	cmove r9, [x]
	add r10, r11
	loop .loop


	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret

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
