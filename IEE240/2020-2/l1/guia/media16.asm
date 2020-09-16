; vi:ft=nasm
bits 16
org 0x7c00
MSG_MEDIA: db "Media: ", 0
vNum1 equ 3
vNum2 equ 7
vNum3 equ 8

boot:
	mov ax, 0
	mov bx, MSG_MEDIA
	call print_string
	mov ax, vNum1
	add ax, vNum2
	add ax, vNum3
	mov bx, 3
	div bx
	mov ah, 0x0e
	mov dx, ax
	mov al, dl
	add al, '0'
	int 0x10
	jmp $

print_string:
	pusha
	mov ah, 0x0e
	lazo2:
		mov al, [bx]
		cmp al, 0
		je return
		int 0x10
		inc bx
		jmp lazo2
		return:
			popa
			ret

times 510 - ($-$$) db 0
dw 0xaa55
