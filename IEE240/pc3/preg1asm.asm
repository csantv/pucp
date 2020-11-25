; vi:ft=nasm
default rel

global func_ASM:function

section .text

; rdi -> arr
; rsi -> N
; rdx -> P
func_ASM:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	xor ebx, ebx
	mov rcx, rsi

.loop:
	cmp [rdi], rdx
	jb .inc
	add rbx, 1
.inc:
	add rdi, 8
	loop .loop

	mov rax, rbx

	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret
