DATA SEGMENT
    ARR DW 100 DUP(?)
    FIND DW ?  
    LENMSG DB "Enter length: $"
    ARRMSG DB 0AH,0DH,"Enter the elements: $"
    MSG DB 0AH,0DH,"Enter the number to be searched: $" 
    NEWLINE DB 0AH,0DH,"$"
    FMSG DB 0AH,0DH,"Number exists$"
    NMSG DB 0AH,0DH,"Number does not exist$" 
    LEN DW ?
DATA ENDS

DISPLAY MACRO ARG
    MOV AH,09H
    LEA DX,ARG
    INT 21H
ENDM

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA
START:
    MOV AX,DATA
    MOV DS,AX
       
    LEA SI,ARR 
    DISPLAY LENMSG
    CALL GET_INPUT
    MOV BH,BL
    CALL GET_INPUT 
    MOV LEN,BX 
    MOV CX,LEN  
    
    DISPLAY ARRMSG
IPARR: PUSH CX 
    CALL GET_INPUT 
    MOV BH,BL
    CALL GET_INPUT 
    MOV [SI],BX
    ADD SI,02H
    POP CX 
    DISPLAY NEWLINE 
    LOOP IPARR
    
    DISPLAY MSG    
    CALL GET_INPUT 
    MOV BH,BL
    CALL GET_INPUT 
    MOV FIND,BX
   
    LEA SI,ARR
    MOV CX,LEN 
L2: MOV DX,[SI]
    CMP FIND,DX
    JZ FOUND
    ADD SI,02H
    LOOP L2
    DISPLAY NMSG
    JMP SKIP
FOUND: DISPLAY FMSG 
SKIP:  MOV AH,01H
       INT 21H
       MOV AH,4CH
       INT 21H

GET_INPUT PROC 
    MOV AH,01H
    INT 21H
    SUB AL,30H
    CMP AL,09H
    JLE L1
    SUB AL,07H    
    
L1: MOV BL,AL
    MOV CL,04H
    SHL BL,CL  
    
    MOV AH,01H
    INT 21H
    SUB AL,30H
    CMP AL,09H
    JLE L3
    SUB AL,07H    
L3: ADD BL,AL
    RET
GET_INPUT ENDP

CODE ENDS
END START