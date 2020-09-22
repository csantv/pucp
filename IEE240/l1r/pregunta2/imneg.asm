; vi:ft=nasm
global imneg

section	.text

imneg:
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
    mov esi,[ebp + 12]  ; esi <- outimg
    mov ecx,[ebp + 16]  ; ecx <- N_size

; -------------------------------------------- ;
; -------------------------------------------- ;
; ---------- Escriba aqui su código ---------- ;
; -------------------------------------------- ;
; -------------------------------------------- ;

.loop:
    mov eax, 255
	mov edx, [edi]
	sub eax, edx
	mov [esi], eax
    inc edi
    inc esi
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
