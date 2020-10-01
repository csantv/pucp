; vi:ft=nasm
global asm_calc_lim
global binpow_lim

section .text
; n -> rdi
asm_calc_lim:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	xor eax, eax
	mov rax, rdi
	inc rax
	cvtsi2ss xmm0, rax
	cvtsi2ss xmm1, rdi
	divss xmm0, xmm1
	movss xmm1, xmm0
	mov rcx, rdi
.loop:
	dec rcx
	jrcxz .exit
	mulss xmm0, xmm1
	jmp .loop
.exit:
	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret

;long long binpow(long long a, long long b) {
;    if (b == 0)
;        return 1;
;    long long res = binpow(a, b / 2);
;    if (b % 2)
;        return res * res * a;
;    else
;        return res * res;
;}

; 2 ^ 100
; res = binpow(2, 50)
; res = binpow(2, 25) 	
; res = binpow(2, 12) 	64 * 64
; res = binpow(2, 6) 	8 * 8
; res = binpow(2, 3) 	2 * 2 * 2
; res = binpow(2, 1) 	1 * 1 * 2
; res = 1
binpow_lim:	
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx
; a -> rdi
; b -> rsi
; 2 ^ 100
	mov rax, 2
	mov r9, rax
	cvtsi2ss xmm0, rax
	mov rax, 3
	mov rbx, 2
.recur:
	xor rdx, rdx
	div rbx
	cmp rdx, 0
	je .exit
	cmove rcx, r8
	cmovne rcx, r9
	; guardar al stack
	sub rsp, 16
	movdqu oword [rsp], xmm0
	; guardar al stack
	sub rsp, 16
	movdqu oword [rsp], xmm0
	; decidir que valor pushear ultimo
	cvtsi2ss xmm1, rcx
	sub rsp, 16
	movdqu oword [rsp], xmm1
	mov rcx, 3
.mult:
	; devolver del stack
	movdqu  xmm1, oword [rsp]
	add rsp, 16
	mulss xmm0, xmm1
	loop .mult
	jmp .recur

.exit:
	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret
