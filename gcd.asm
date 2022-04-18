mov bx, 1100h
mov di, 1200h
mov ax, [bx]
mov cx, [bx+2]
rpt:
cmp ax, cx
je store
jnc SKIP
xchg ax, cx
skip:
mov dx, 0000h
div cx
cmp dx, 0000h
je store
mov ax, dx
jmp rpt
store:
mov [di],cx
hlt