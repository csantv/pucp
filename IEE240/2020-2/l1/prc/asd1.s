; vi:ft=nasm
section .data
SYS_READ equ 3
SYS_WRITE equ 4
SYS_EXIT equ 1
STDIN equ 0
STDOUT equ 1
array dd 10,8
array_size db 2
mensaje db "El promedio calculado es: %d",10,0

section .text
        global main
        extern printf
main:
        ;limpiamos los registros
        xor eax,eax
        xor ebx,ebx
        xor ecx,ecx
        xor edx,edx

        mov ebx,[array_size]
        push ebx
        mov esi, 0 ;con este registro nos movilizamos por el arreglo
        mov eax,[array+esi]
lazo:
        dec ebx
        add esi,4
        mov ecx,[array+esi]
        add eax,ecx
        cmp ebx,0
        jne lazo
imprimir:
        pop ebx
        div ebx
        push eax
        push mensaje
        call printf
end:
        mov eax,SYS_EXIT
        mov ebx, STDIN
        int 80h
