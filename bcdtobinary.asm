code segment
assume cs : code
start :
mov ax ,0720 h
mov DS , ax
mov bx ,20 h
mov al ,[ bx ]
mov dl , al
 and dl ,0 fh
 mov cl ,04 h
 shr al , cl
 mov ch ,0 ah
 mul ch
 add al , dl
 mov bx ,21 h
 mov [ bx ] , al
 hlt

 code ends
 end start