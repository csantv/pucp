; vi:ft=nasm

default rel

global imhist:function

section	.text

; rdi <- img
; rsi <- hist
; rdx <- N_size
imhist:
	push rbp
	mov rbp, rsp
	push rsi
	push rdi
	push rdx

    ; Limpiar los registros a utilizar
    xor eax,eax
    xor ebx,ebx
    xor ecx,ecx

    ; Punteros iniciales (esto se inicializa en el archivo laboratorio0.c)
	;mov edi,[ebp + 8]   ; edi <- img
    ;mov esi,[ebp + 12]  ; esi <- hist
    ;mov ecx,[ebp + 16]  ; ecx <- N_size

; -------------------------------------------- ;
; -------------------------------------------- ;
; ---------- Escriba aqui su código ---------- ;
; -------------------------------------------- ;
; -------------------------------------------- ;
	mov rcx, rdx
	mov rbx, 4

.loop:
	; cargar cada byte de la imagen
	movzx rax, byte [rdi]
	mov [reg], eax
	inc rdi
	movzx rax, byte [rdi]
	mov [reg+4], eax
	inc rdi
	movzx rax, byte [rdi]
	mov [reg+8], eax
	inc rdi
	movzx rax, byte [rdi]
	mov [reg+12], eax
	inc rdi
	movdqa xmm0, [reg]

	;movzx [reg], byte [rdi]
	;inc rdi
	;movzx [reg+4], byte [rdi]
	;inc rdi
	;movzx [reg+8], byte [rdi]
	;inc rdi
	;movzx [reg+12], byte [rdi]

	push rsi
	movzx rax, byte [rdi]
	mul rbx
	add rsi, rax
	inc DWORD [rsi]
	inc rdi
	pop rsi

	sub rcx, 4
	jrcxz .end
	jmp .loop

.end:
; -------------------------------------------- ;
; -------------------------------------------- ;
; ------------- Fin de su código ------------- ;
; -------------------------------------------- ;
; -------------------------------------------- ;
    ; Epílogo de calling conventions de 32 bits
    mov rax,1

	pop rbx
	pop rdi
	pop rsi
	mov rsp, rbp
	pop rbp
    ret

section .bss

align 16
reg resb 16
align 16
reg1 resb 16

