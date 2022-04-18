code segment
assume code : cs
start :
mov ax ,0700 h
mov ds , ax
mov dl ,00 h
mov bx ,0128 h
mov ax ,[ bx ]
 mov bx ,012 ah
 mov cx ,[ bx ]
 add ax , cx
 jnc L1
 inc dl
 L1 : mov bx ,012 ch
 mov [ bx ] , ax
 mov bx ,012 eh
 mov [ bx ] , dl
 hlt

 code ends
 end start