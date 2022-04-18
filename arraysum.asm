code segment
assume cs : code
start :
mov cx, 05h
mov ax, 0000h
mov ax, 0000h
mov si, 1000h
REPEAT:
    mov bl, [si]
    add ax, bx
    inc si
    dec cx
    jnz REPEAT
mov di, 1011h
mov [di], ax
hlt

 code ends
 end start