; FIXME: completar el codigo ASM. Recuerda los calling conventions de GCC!
; vi:ft=nasm

default rel

global geometricSerieASM:function
extern pow:function

section .bss

fl0 resb 16
fl2 resb 16

section .text

; a -> rdi
; N -> rsi
; x -> xmm0
geometricSerieASM:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rbx

	xorps xmm2, xmm2
	; convertir xmm0 a double
	cvtss2sd xmm0, xmm0
	; guardar registros para el futuro
	push rdi
	mov rcx, rsi
.loop:
	push rcx
	; guardar xmm0 en stack
	;sub rsp, 16
	;movdqu oword [rsp], xmm0
	movdqu oword [fl0], xmm0
	; guardar xmm2 en stack
	;sub rsp, 16
	;movdqu oword [rsp], xmm2
	movdqu oword [fl2], xmm2
	; pasar valor de rcx a xmm1 como double
	cvtsi2sd xmm1, rcx
	call pow wrt ..plt
	; devolver xmm2 del stack
	movdqu xmm2, oword [fl2]
	;movdqu  xmm2, oword [rsp]
	;add rsp, 16
	; sumar xmm0 a xmm2
	addsd xmm2, xmm0
	; regresar xmm0 del stack
	;movdqu  xmm0, oword [rsp]
	;add rsp, 16
	movdqu xmm0, oword [fl0]
	; devolver rcx del stack
	pop rcx
	loop .loop
	pop rdi
	; convertir xmm2 a float en xmm0
	cvtsd2ss xmm0, xmm2 
	; sumar 1 porque el bucle no
	; ejecuta la operacion cuando n = 0
	mov rax, 1
	cvtsi2ss xmm1, rax
	addss xmm0, xmm1
	; multiplicar 'a' a xmm0
	cvtsi2ss xmm1, rdi
	mulss xmm0, xmm1


	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
	ret

; xmm1 -> base
; rax -> exp
; xmm2 -> res
asmpow:
	push rcx
	mov rcx, rax
	movss xmm2, xmm1
.loop:
	dec rcx
	jrcxz .exit
	mulss xmm2, xmm1
	jmp .loop
.exit:
	pop rcx
	ret
