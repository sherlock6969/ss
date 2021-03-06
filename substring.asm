DATA SEGMENT
    STRING DB 0FFH DUP("$")  
    MSG DB "Enter the string: $"  
    NEWLINE DB 0AH,0DH,"$"
    LEN DB ?
    SUBLEN DB ?  
    SUBS DB 0FFH DUP("$")
    ISUB DB 0AH,0DH,"Enter substring: $" 
    FOUND DB 0AH,0DH,"Substring found$"
    NF DB 0AH,0DH,"Substring not found$"
DATA ENDS

EXTRA SEGMENT
    SUBSTRING DB 0FFH DUP(?)
EXTRA ENDS

DISPLAY MACRO ARG
    MOV AH,09H
    LEA DX,ARG
    INT 21H
ENDM 

GET_IN MACRO ARG
    MOV AH,0AH
    LEA DX,ARG
    MOV ARG,0FFH
    INT 21H 
ENDM

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA, ES:EXTRA
START:
    MOV AX,DATA
    MOV DS,AX 
    MOV AX,EXTRA
    MOV ES,AX    
    
    DISPLAY MSG 
    GET_IN STRING
    LEA SI,STRING
    MOV CL,[SI+1]
    MOV LEN,CL
    MOV CH,00
    
    DISPLAY ISUB 
    GET_IN SUBS      

    LEA SI,SUBS
    MOV CL,[SI+1]
    MOV SUBLEN,CL
    ADD SI,02H
    LEA DI,SUBSTRING 
    REP MOVSB
    
    LEA SI,STRING 
    ADD SI,02H 
    MOV DH,LEN
    ADD DH,02H
RE: DEC DH
    MOV CL,SUBLEN 
    LEA DI,SUBSTRING 
    CMP DH,00
    JZ FALSE
    REP CMPSB
    JNZ RE    
    CMP CL,00
    JNZ FALSE 
    DISPLAY FOUND
    JMP EOC
FALSE: DISPLAY NF

EOC:MOV AH,01H
    INT 21H  
    MOV AX,4CH
    INT 21H     

CODE ENDS
END START