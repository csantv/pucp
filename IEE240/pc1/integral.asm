; vi:ft=nasm
global integral

section	.text

integral:
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

    ; Punteros iniciales (esto se inicializa en el archivo main.c)
    mov esi,[ebp + 8]   ; esi <- *arr
    mov ecx,[ebp + 12]  ; ecx <- N
    
    ; La salida de la funcion se devuelve en el registro eax!!!!

; -------------------------------------------- ;
; -------------------------------------------- ;
; ---------- Escriba aqui su código ---------- ;
; -------------------------------------------- ;
; -------------------------------------------- ;

	mov ebx, 2
.loop:
	add eax, [esi]
	add esi, 4		; aparentemente, el tamaño de un puntero a int son 4 bytes
	loop .loop
	div ebx

; -------------------------------------------- ;
; -------------------------------------------- ;
; ------------- Fin de su código ------------- ;
; -------------------------------------------- ;
; -------------------------------------------- ;
    
    ; Epílogo de calling conventions de 32 bits
    pop ebx
    pop edi
    pop esi 
    mov esp,ebp
    pop ebp
    ret
