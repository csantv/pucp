; vi:ft=nasm
global main
extern scanf
extern printf

segment .data

prueba dd 123
str1 db "Numero: ", 0
str2 db "%d", 0
str3 db "El numero %d es fuerte.", 10, 0
str4 db "El numero %d no es fuerte.", 10, 0

segment .bss

entrada resw 2

segment .text

main:
	push str1
	call printf
	add esp, 4

	push entrada
	push str2
	call scanf
	add esp, 8

	push DWORD [entrada]
	call es_fuerte
	
.end:
	mov eax, 1
	mov ebx, 0
	int 80h


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

	pop eax
	cmp eax, ebx
	push eax
	je .es_fuerte
	jne .no_es_fuerte
.es_fuerte:
	push str3
	jmp .imprimir
.no_es_fuerte:
	push str4
.imprimir:
	call printf
	add esp, 8

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
