code segment
assume cs : code
start :
mov ax ,0720 h
mov DS , ax
mov bx ,20 h
mov al ,[ bx ]
mov dl ,64 h
 mov ah ,00 h
 div dl
 mov bx ,21 h
 mov [ bx ] , al
 mov al , ah
 mov ah ,00 h
 mov dl ,0 ah
 div dl
 mov cl ,04 h
 shl al , cl
 or al , ah
 mov bx ,22 h
 mov [ bx ] , al
 hlt

 code ends
 end start