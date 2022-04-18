#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char* decToHex(int decimal)
{
    int tmp,i=0;
    char hex[8] = "0";
    
    while(decimal!=0) 
    {
        tmp = decimal % 16;
        if(tmp<10)
            hex[i++] = tmp + 48;
        else
            hex[i++] = tmp + 55;
            
        decimal/=16;
    }
    
    int len = strlen(hex)-1;
    i=0;
    
    while(i<len)
    {
        char tmpc = hex[i];
        hex[i++] = hex[len];
        hex[len--] = tmpc;
    }
    
    char *ret = malloc(8);
    ret = hex;
    return ret;
}

int hexToDec(char* hex)
{
    int i,decimal=0;
    int len=strlen(hex);
    for(i=0;i<strlen(hex);++i)
    {
        if(hex[i]>='0' && hex[i]<='9')
            decimal+=(hex[i]-48)*pow(16,len-i-1);
        
        else
            decimal+=(hex[i]-55)*pow(16,len-i-1);
    }
    
    return decimal;
}

void main() {
    FILE *objectcode;
    char record[100], address[10], pname[10], code[2], length[10], startAddress[10];

    objectcode = fopen("objectcode.txt", "r");

    // Reading header record
    fscanf(objectcode, "%[^^]^%[^^]^%[^^]^%[^\n]", code, pname, startAddress, length);
    
    // Verify program name and length
    char programlength[3];
    programlength[0] = length[4];
    programlength[1] = length[5];
    printf("Program Name: %s\n", pname);
    printf("Length: %s\n\n", programlength);

    // Reading text record
    fscanf(objectcode, "\n%[^^]^%[^^]^%[^^]^%[^\n]", code, address, length, record);
    char currentAddress[5];
    for(int k=0; k<4; k++) {
        currentAddress[k] = address[k+2];
    }
    currentAddress[4] = '\0';

    printf("Address\t  Value\n\n");
    while(code[0] != 'E') {  
        int i = 0;
        int int_address;

        // Moving object code to specified memory location
        while(record[i] != '\0') {
            if (record[i] == '^') {
                i++;
                continue;
            }
            printf(" %s\t   %c%c\n", currentAddress, record[i], record[i+1]);
            int_address = hexToDec(currentAddress);
            strcpy(currentAddress, decToHex(int_address + 1));
            i+=2;
        }
        
        fscanf(objectcode, "\n%[^^]^%[^^]^%[^^]^%[^\n]", code, address, length, record);
    }

    // Jump to address specified in END record
    for(int k=0; k<4; k++) {
        currentAddress[k] = address[k+2];
    }
    currentAddress[4] = '\0';
    printf("\nJumping to address: %s\n", currentAddress);

    fclose(objectcode);
}