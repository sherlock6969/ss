#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{

    int startAddress, loc, sa_operand, 
    opcode_flag = 0, optab_value;
    FILE *inputPtr, *symptabPtr, *optabPtr, 
    *read_symtabPtr,*outputPtr;
    char label[100], opcode[100], operand[100], 
    optab_symbol[100];
    inputPtr = fopen("input.txt", "r");
    symptabPtr = fopen("symtab.txt", "w");
    read_symtabPtr = fopen("symtab.txt", "r");
    outputPtr=fopen("output.txt", "w");
    fscanf(inputPtr, "%s %s", label, opcode);
    if (strcmp(opcode, "START") == 0)
    {
        fscanf(inputPtr, "%d", &sa_operand);
        startAddress = sa_operand;
        loc = startAddress;
        printf("%s %s %d\n", label, opcode, sa_operand);
        fprintf(outputPtr,"\t%s %s %d\n",  label, 
        opcode, sa_operand);
        fscanf(inputPtr, " %s %s", label, opcode);

    }
    else
    {
        loc = 0;
        startAddress = 0;
    }
    while (!feof(inputPtr))
    {
        fscanf(inputPtr, "%s", operand);

        printf("%d %s %s %s\n", loc, label, opcode, operand);
        fprintf(outputPtr,"%d %s %s %s\n", loc, label, 
        opcode, operand);
        if (strcmp(opcode, "END") == 0)
        {
            goto a;
        }
        if (strcmp(label, "-") != 0)
        {
            char symb[100];
            int value, flag = 0;

            fscanf(read_symtabPtr, "%d %s", &value, symb);
            while (!feof(read_symtabPtr))
            {
                if (strcmp(symb, label) == 0)
                {
                    flag = 1;
                    printf("repeat\n");
                    break;
                }
                fscanf(read_symtabPtr, "%d %s", &value, symb);
            }
           

            if (flag == 0)
            {
                fprintf(symptabPtr, "%d %s\n", loc, label);
            }
        }
        optabPtr = fopen("optab.txt", "r");
        fscanf(optabPtr, "%s %d", optab_symbol, 
        &optab_value);
        while (!feof(optabPtr))
        {
            if (strcmp(optab_symbol, opcode) == 0)
            {
                opcode_flag = 1;
                loc += 3;
                break;
            }
            fscanf(optabPtr, "%s %d", optab_symbol, 
            &optab_value);
        }
        fclose(optabPtr);
        if (strcmp(opcode, "WORD") == 0)
        {
            opcode_flag = 1;
            loc += 3;
        }
        else if (strcmp(opcode, "RESW") == 0)
        {
            opcode_flag = 1;
            int value = atoi(operand);
            loc += 3 * value;
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            opcode_flag = 1;
            if (operand[0] == 'X')
            {
                int length = strlen(operand);
                int value = (length - 3) / 2;
                loc += value;
            }
            else
            {
                int length = strlen(operand);
                int value = (length - 3);
                loc += value;
            }
        }
        else if (strcmp(opcode, "RESB") == 0)
        {

            opcode_flag = 1;
            int value = atoi(operand);
            loc += value;
        }

        if (!opcode_flag)
        {
            printf("Invalid Opcode\n");
            exit(0);
        }
        opcode_flag = 1;
        fscanf(inputPtr, "%s %s", label, opcode);
    }
a:
    if (strcmp(opcode, "END") == 0)
    {
        printf("End of Program\n");
        printf("Program Length is %d\n", loc - startAddress);
    }

    fclose(symptabPtr);
    fclose(inputPtr);
     fclose(read_symtabPtr);
     fclose(outputPtr);
}