#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int search_optab(char opcode[10], char *optabvalue){
    FILE *optab = fopen("optab.txt", "r");
    char op[20];
    int opvalue;
    while(!feof(optab)){
        fscanf(optab, "%s %s", op, optabvalue);
        if(strcmp(op, opcode)==0){
            fclose(optab);
            return 1;
        }
    }
    fclose(optab);
    return 0;
}
int search_symtab(char operand[20], char *operandadd){
    FILE *symtab = fopen("symtab.txt", "r");
    char symbolname[20];
    while(!feof(symtab)){
        fscanf(symtab, "%s %s", symbolname, operandadd);
        if(strcmp(operand, symbolname)==0){
            fclose(symtab);
            return 1;
        }
    }
    fclose(symtab);
    return 0;
}
int main(){
    FILE *ifile, *length, *objectcodefile, *listingfile;
    char programname[20], opcode[20], operand[20], label[20], optabvalue[20], operandadd[20], objcode[20], textrec[60],trash;
    int startingadd, flen, loc, txtcnt=60;
    strcpy(textrec, "");
    ifile = fopen("ifile.txt", "r");
    listingfile = fopen("listingfile.txt", "w");
    objectcodefile = fopen("output.txt", "w");
    length = fopen("length.txt", "r");
    fscanf(length, "%d", &flen);
    fscanf(ifile, "%s %s %s %x", trash, programname, opcode, &startingadd);
    if(strcmp(opcode,"START")==0){
        fprintf(listingfile, "\t%s\t%s\t%x", programname, opcode, startingadd);
        fscanf(ifile, "%x %s %s %s", &loc, label, opcode, operand);
    }
    fprintf(objectcodefile, "H^%-6s%06x%06x\nT%06x", programname, startingadd, flen, startingadd);
    while(strcmp(opcode, "END")!= 0){
        if(search_optab(opcode, optabvalue)){
            strcpy(objcode, optabvalue);
            if(strcmp(operand,"_")!=0){
                if(search_symtab(operand, operandadd)){
                    strcat(objcode, operandadd);
                }
                else{
                    strcat(objcode, "0000");
                    printf("UNDEFINED LABEL");
                }
            }
            else{
                strcat(objcode, "0000");
            }
        }
        else if(strcmp(opcode, "BYTE")==0){
            for(int i=2; i<strlen(operand)-1;i++){
                char hex[2];
                sprintf(hex, "%X", operand[i]);
                strcat(objcode, hex);
            }
        }
        else if(strcmp(opcode, "WORD")==0){
            char hex[7];
            sprintf(hex, "%06lx", strtoul(operand,NULL,16));
            strcat(objcode, hex);
        }
        if(strlen(objcode)>0){
            if(txtcnt-strlen(objcode)>0){
                strcat(textrec,objcode);
                fprintf(listingfile, "\n%x\t%s\t%s\t%s\t%s", loc, label, opcode, operand, objcode);
                strcpy(objcode,"");
            }
            else{
                txtcnt=60;
                fprintf(objectcodefile, "%2lx%s\nT%x", strlen(textrec)/2, textrec, loc);
                strcpy(textrec, "");
                strcpy(objcode,"");
                fprintf(listingfile, "\n%x\t%s\t%s\t%s\t%s", loc, label, opcode, operand, objcode);
            }
        }
        else{
            fprintf(listingfile, "\n%x\t%s\t%s\t%s", loc, label, opcode,operand);
        }
        fscanf(ifile, "%x %s %s %s", &loc, label, opcode, operand);
    }
    fprintf(objectcodefile, "%2lX%s", strlen(textrec)/2, textrec);
    fprintf(listingfile, "\n%x\t%s\t%s\t%s", loc, label, opcode,operand);
    fprintf(objectcodefile, "\nE%x\n", startingadd);
    fprintf(listingfile, "\tE%x\n", startingadd);
}