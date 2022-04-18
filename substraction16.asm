code segment

assume code : cs
start :
mov ax ,0720 h
mov DS , ax
mov dl ,00 H
mov ax ,1111 H
mov cx ,3333 H
 sub ax , cx
 jnc L1
 inc dl
 not ax
 inc ax
 L1 : mov bx ,22 h
 mov [ bx ] , ax
 mov bx ,24 h
 mov [ bx ] , dl
 hlt

 code ends
 end start