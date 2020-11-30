; FIXME: completar el codigo ASM. Recuerda los calling conventions de GCC!
; vi:ft=nasm

default rel

global geometricSerieASM:function
extern pow:function

section .bss

fl0 resb 16
fl2 resb 16

align 16
dat1 resb 16
align 16
dat2 resb 16

ind resb 8

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
	mov [ind], rcx

	; guardar x en memoria
	movdqu oword [fl0], xmm0

.loop:
	push rcx
	; primer exponente
	movdqu xmm0, oword [fl0]
	cvtsi2sd xmm1, [ind]
	call pow wrt ..plt
	movq [dat2], xmm0 		; extraer double
	dec qword [ind]

	; segundo exponente
	movdqu xmm0, oword [fl0]
	cvtsi2sd xmm1, [ind]
	call pow wrt ..plt
	movq [dat2+8], xmm0
	dec qword [ind]

	; sumar con simd, guardar valor en xmm2
	haddpd xmm2, [dat2]
	movapd [dat2], xmm2
	movq xmm2, [dat2]

	; guardar xmm2 en memoria
	movdqu oword [fl2], xmm2

	; devolver rcx del stack
	pop rcx
	jrcxz .end
	sub rcx, 2
	jmp .loop

.end:
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
