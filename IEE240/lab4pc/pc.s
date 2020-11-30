; vi:ft=nasm

default rel

global instructionTest:function

section .text

instructionTest:
	xorps xmm0, xmm0
	xorps xmm1, xmm1

	movaps xmm0, [rdi]
	;movaps xmm1, [rsi]
	;cmpps xmm0, xmm1, 01h
	;cmpltps xmm0, xmm1
	haddps xmm0, xmm0
	movaps [dat], xmm0
	movd xmm0, [dat+4]

	;haddps xmm0, xmm0
	;movaps [rdx], xmm0

	;add rdi, 16
	;movaps xmm0, [rdi]
	;movaps xmm1, [rdi]
	;shufps xmm0, xmm1, 00011011b
	;movaps [rdx], xmm0

	;sub rdi, 16
	;add rdx, 16

	;movaps xmm0, [rdi]
	;movaps xmm1, [rdi]
	;shufps xmm0, xmm1, 00011011b
	;movaps [rdx], xmm0


	;add rdi, 16
	;movaps xmm0, [rdi]
	;movaps xmm1, [rdi]
	;shufps xmm0, xmm1, 00011011b
	;movaps [rdx], xmm0

	;add rdi, 8
	;add rdx, 8
	;movups xmm0, [rdi]
	;movups xmm1, [rdi]
	;shufps xmm0, xmm1, 00011011b
	;movups [rdx], xmm0

	;add rdi, 8
	;add rdx, 8
	;movups xmm0, [rdi]
	;movups xmm1, [rdi]
	;shufps xmm0, xmm1, 00011011b
	;movups [rdx], xmm0

	ret

section .bss
align 16
dat resb 16
