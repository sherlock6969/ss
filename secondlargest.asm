data segment
    arr dw 08h dup (?)  
    slar dw ?
    lar dw ?
    len db ?
    msg1 db 0ah,0dh,"Enter the number of elements : $"
    msg2 db 0ah,0dh,"Enter the elements : $"    
    msg3 db 0ah,0dh,"Second largest element : $"     
    msg4 db "  $"
data ends           

display macro arg
    mov ah,09h
    lea dx,arg
    int 21h
endm              

code segment
    assume cs:code,ds:data
    
start:
        mov ax,data
        mov ds,ax
        
        display msg1
        call input
        mov len,al   
        mov ch,len
        display msg2
        lea si,arr 
read:   call input
        mov bl,al
        mov cl,04h
        shl bl,cl 
        call input  
        add bl,al 
        
        call input
        mov dl,al
        mov cl,04h
        shl dl,cl
        call input
        add dl,al
        
        mov al,dl
        mov ah,bl
        mov [si],ax  
        add si,02h      
        dec ch
        display msg4   
        jnz read
        
        mov cl,len    
        dec cl
 
        lea si,arr 
        mov bx,[si]
        mov lar,bx
innerloop:mov ax,[si+2]
        cmp lar,ax  
        jnc skip
        mov lar,ax      
skip:   add si,02h        
        loop innerloop     
        
        lea si,arr    
        mov cl,len
        dec cl
        mov bx,[si]
        mov slar,bx
outerloop:mov ax,[si+2]   
        cmp slar,ax
        jnc skip2
        mov dx,lar
        cmp dx,ax
        je skip2
        mov slar,ax
skip2:  add si,02h
        loop outerloop             
        
        mov ah,4ch
        int 21h  
        input proc
            mov ah,01h
            int 21h   
            sub al,30h
            cmp al,0ah
            jl skip1
            sub al,07h
            skip1: 
            RET              
        input endp            
        
        
code ends
end start