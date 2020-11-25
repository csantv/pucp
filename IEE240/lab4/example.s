; vi:ft=nasm
default rel

global asmVecSum:function
global partialAsmVecSum

section .text

asmVecSum:
	xorpd xmm0, xmm0
	xorpd xmm1, xmm1
	cmp rcx, 0
	je done
.next:
	movaps xmm0, [rdi]
	movaps xmm1, [rsi]
	addps xmm0, xmm1
	movaps [rdx], xmm0
	add rdi, 16
	add rsi, 16
	add rdx, 16
	sub rcx, 4
	jnz .next
done:
	ret

partialAsmVecSum:
	xorpd xmm0, xmm0
	xorpd xmm1, xmm1
	movaps xmm0, [rdi]
	movaps xmm1, [rsi]
	addps xmm0, xmm1
	movups [rdx], xmm0
	ret
