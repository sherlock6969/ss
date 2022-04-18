code segment
assume cs : code
start :
mov ax ,0720 h
mov ds , ax
mov dl ,00 h
mov bx ,20 h
mov ax ,[ bx ]
 mov bx ,22 h
 mov cx ,[ bx ]
 mov bx ,24 h
 sub ax ,[ bx ]
 mov bx ,26 h
 sbb cx ,[ bx ]
 jnc L1
 inc dl
 not ax
 not cx
 add ax ,01 h
 adc cx ,00 h
 L1 : mov bx ,28 h
 mov [ bx ] , ax
 mov bx ,2 ah
 mov [ bx ] , cx
 mov bx ,2 ch
 mov [ bx ] , dl
 hlt

 code ends
 end start