mov si, 1100h
mov di, 1200h
mov cl, [si]
inc si
mov al, [si]
dec cl
again:
inc si
mov bl, [si]
cmp al, bl
jnc ahead
mov al, bl
ahead:
dec cl
jnz again
mov [di],al
hlt