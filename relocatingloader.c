#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct {
    char address[10];
    char data[3];
} Memory;

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

int get_memindex(Memory memory[], char key[], int len) {
    int index = -1;
    for (int i=0; i<len; i++) {
        if (strcmp(memory[i].address, key) == 0) {
            index = i;
            break;
        }
    }
    return index;
}

void main() {
    FILE *objectcode;
    char record[100], address[10], pname[10], type[2], length[10], startAddress[10];
    Memory memory[100];
    int int_address;
    char refinedAddr[5], currentAddress[5];

    objectcode = fopen("objectcode.txt", "r");

    // Reading header record
    fscanf(objectcode, "%[^^]^%[^^]^%[^^]^%[^\n]", type, pname, address, length);
    for(int k=0; k<4; k++) {
        startAddress[k] = address[k+2];
    }
    startAddress[4] = '\0';
    
    // Input locationg to relocate:
    char newAddr[10], effAddr[10];
    printf("Input the location to which the program is to be relocated (> %s): ", startAddress);
    scanf("%s", newAddr);

    if (hexToDec(startAddress) > hexToDec(newAddr)) {
        printf("Start Address > Relocated Address !!\nExiting...\n");
        exit(0);
    }

    // Calculating the effective address
    int_address = hexToDec(newAddr) - hexToDec(startAddress);
    strcpy(effAddr, decToHex(int_address));

    // Reading text record
    fscanf(objectcode, "\n%[^^]^%[^^]^%[^^]^%[^\n]", type, address, length, record);
    for(int k=0; k<4; k++) {
        currentAddress[k] = address[k+2];
    }
    currentAddress[4] = '\0';

    // Change Current Address
    int_address = hexToDec(effAddr) + hexToDec(currentAddress);
    strcpy(currentAddress, decToHex(int_address));

    int m = 0;
    while(type[0] != 'E') {  
        int i = 0;

        if (type[0] == 'T') {
            // Moving object code to specified memory location
            while(record[i] != '\0') {
                if (record[i] == '^') {
                    i++;
                    continue;
                }

                strcpy(memory[m].address, currentAddress);
                memory[m].data[0] = record[i];
                memory[m].data[1] = record[i+1];
                memory[m++].data[2] = '\0';

                int_address = hexToDec(currentAddress);
                strcpy(currentAddress, decToHex(int_address + 1));
                i+=2;
            }
        }
        else if (type[0] == 'M') {
            for(int k=0; k<4; k++) {
                refinedAddr[k] = address[k+2];
            }
            refinedAddr[4] = '\0';

            int len = hexToDec(length);

            int_address = hexToDec(effAddr) + hexToDec(refinedAddr);
            strcpy(refinedAddr, decToHex(int_address));
            int ind = get_memindex(memory, refinedAddr, m);
            if (ind == -1) {
                printf("Invalid memory location given!!\nExiting...\n");
                exit(0);
            }

            // Get data to be updated
            char data[len + 1];
            int k = 0, temp = len;
            if (temp % 2 == 1) {
                data[k++] = memory[ind].data[1]; // If odd half bytes..
                ind++;
                temp--;
            }
            for (int i=0; i<temp; i+=2) {
                data[k++] = memory[ind].data[0];
                data[k++] = memory[ind].data[1];
                ind++;
            }
            data[k] = '\0';

            // Update data
            int updated_data = hexToDec(data) + hexToDec(effAddr);
            strcpy(data, decToHex(updated_data));

            // Saving the updated data
            ind = get_memindex(memory, refinedAddr, m);
            k = 0;
            if (len % 2 == 1) {
                memory[ind].data[1] = data[k++];
                ind++;
                len--;
            }
            for (int i=0; i<len; i+=2) {
                memory[ind].data[0] = data[k++];
                memory[ind].data[1] = data[k++];
                ind++;
            }
        }

        // Reading next line
        fscanf(objectcode, "\n%[^\n]", record); 
        fseek(objectcode, -strlen(record), SEEK_CUR);
        if (record[0] == 'M') {
            fscanf(objectcode, "\n%[^^]^%[^^]^%[^\n]", type, address, length);
        } else {
            fscanf(objectcode, "\n%[^^]^%[^^]^%[^^]^%[^\n]", type, address, length, record);
        }
        
    }

    printf("Relocating...\n\n");

    printf("Address\t  Value\n\n");
    for (int i = 0; i<m; i++) {
        printf(" %s\t   %s\n", memory[i].address, memory[i].data);
    }

    // Jump to address specified in END record
    for(int k=0; k<4; k++) {
        currentAddress[k] = address[k+2];
    }
    currentAddress[4] = '\0';
    int_address = hexToDec(effAddr) + hexToDec(currentAddress);
    strcpy(currentAddress, decToHex(int_address));
    printf("\nJumping to address: %s\n", currentAddress);

    fclose(objectcode);
}