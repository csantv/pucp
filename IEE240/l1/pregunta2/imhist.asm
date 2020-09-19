; vi:ft=nasm
global imhist

section	.text

imhist:
    ; Prólogo para calling conventions en 32 bits
    push ebp
    mov ebp, esp
    push esi
    push edi
    push ebx

    ; Limpiar los registros a utilizar
    xor eax,eax
    xor ebx,ebx
    xor ecx,ecx
    xor edx,edx

    ; Punteros iniciales (esto se inicializa en el archivo laboratorio0.c)
	mov edi,[ebp + 8]   ; edi <- img
    mov esi,[ebp + 12]  ; esi <- hist
    mov ecx,[ebp + 16]  ; ecx <- N_size

; -------------------------------------------- ;
; -------------------------------------------- ;
; ---------- Escriba aqui su código ---------- ;
; -------------------------------------------- ;
; -------------------------------------------- ;

.loop:
	; movzx eax, byte [edi]
	movzx eax, byte [edi]
	push esi
	add esi, eax
	mov edx, [esi]
	inc edx
	mov [esi], edx
	pop esi
	inc edi
	loop .loop

; -------------------------------------------- ;
; -------------------------------------------- ;
; ------------- Fin de su código ------------- ;
; -------------------------------------------- ;
; -------------------------------------------- ;
    ; Epílogo de calling conventions de 32 bits
    mov eax,1
    pop ebx
    pop edi
    pop esi 
    mov esp,ebp
    pop ebp
    ret
