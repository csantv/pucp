; vi:ft=nasm
global es_fuerte

segment .text

es_fuerte:
	push ebp
	mov ebp, esp
	push esi
	push edi
	push ebx

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx

	mov eax, [ebp + 8]
	push eax

	mov ebx, 10
.get_digitos:
	xor edx, edx
	div ebx
	push edx
	inc ecx
	test eax, eax
	jnz .get_digitos
	xor ebx, ebx
.acc_factorial:
	pop edx
	push ecx

	push edx
	call factorial
	add esp, 4
	
	pop ecx

	add ebx, eax
	loop .acc_factorial

	pop ecx
	xor eax, eax
	cmp ecx, ebx
	; para booleanos, el registro 'al' debe ser 11111111
	sete al
.exit:
	pop ebx
	pop edi
	pop esi
	mov esp, ebp
	pop ebp
	ret

factorial:
	push ebp
	mov ebp, esp
	push esi
	push edi
	push ebx

	xor eax, eax
	xor ecx, ecx

	mov ecx, [ebp + 8]
	mov eax, ecx
	cmp ecx, 1
	jle .end

	dec ecx
.loop:
	mul ecx
	loop .loop

.end:
	pop ebx
	pop edi
	pop esi
	mov esp, ebp
	pop ebp
	ret
