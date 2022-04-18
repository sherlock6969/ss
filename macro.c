#include<stdio.h>
#include<string.h>

typedef struct pair
{
    int start;
    int end;
}pair;

typedef struct map
{
    char key[100];
    char value[100];  
}map;

pair searchNamTab(char *opcode)
{
    pair val;
    FILE *namTab;
    namTab = fopen("namtab.txt","r");
    char label[100];
    int startIndex,endIndex;

    val.start=val.end=-1;
    
    while(!feof(namTab))
    {
        fscanf(namTab,"%s%d%d",label,&startIndex,&endIndex);
        if(strcmp(opcode,label)==0)
        {
            val.start=startIndex;
            val.end=endIndex;
            break;
        }
    }
    return val;
}

char* replaceArg(map argumentMap[],int argumentMapIndex,char *token,char* operand)
{
    for(int i=0;i<argumentMapIndex;++i)
    {
        char *tmp = NULL;
        tmp = strstr(operand,argumentMap[i].key);

        if(tmp!=NULL)
        {
            int lenMacroArg = strlen(argumentMap[i].key);

            *tmp='\0';
            char *end = tmp+lenMacroArg;
            strcat(operand,argumentMap[i].value);
            strcat(operand,end);
        }
    }
    return operand;
}

void main()
{
    FILE *input,*output,*deftab,*namtab,*argtab;
    input = fopen("input.txt","r");
    output = fopen("output.txt","w");
    argtab = fopen("argtab.txt","w");

    deftab = fopen("deftab.txt","w");
    fclose(deftab);
    namtab = fopen("namtab.txt","w");
    fclose(namtab);


    int lineNo,outputLineNo=0,deftabIndex=0;
    char label[100],opcode[100],operand[100];

    while(1)
    {
        fscanf(input,"%d%s%s%s",&lineNo,label,opcode,operand);

        if(strcmp(opcode,"END")==0)
            break;

        if(strcmp(opcode,"MACRO")==0)
        {
            deftab = fopen("deftab.txt","a");
            namtab = fopen("namtab.txt","a");
             
            fprintf(namtab,"%s\t\t%d\t\t",label,deftabIndex);
            fprintf(deftab,"%d\t\t%s\t\t%s\n",deftabIndex,label,operand);
            deftabIndex+=5;

            while(1)
            {
                fscanf(input,"%d%s%s%s",&lineNo,label,opcode,operand);

                if(strcmp(opcode,"MEND")==0)
                    break;

                fprintf(deftab,"%d\t\t%s\t\t%s\n",deftabIndex,opcode,operand);
                deftabIndex+=5;
            }
            fprintf(deftab,"%d\t\t%s\t\t%s\n",deftabIndex,opcode,operand);
            fprintf(namtab,"%d\n",deftabIndex);
            deftabIndex+=5;

            fclose(deftab);
            fclose(namtab);
        }
        
        else 
        {
            pair searchResult = searchNamTab(opcode);
            if(searchResult.start!=-1)
            {
                deftab = fopen("deftab.txt","r");

                int defLine=-1;
                int cflag=-1;

                map argumentMap[10];
                int argumentMapIndex=0;

                char arguments[100];
                strcpy(arguments,operand);

                char *token = strtok(operand,",");
                while(token!=NULL)
                {
                    strcpy(argumentMap[argumentMapIndex].value,token);
                    fprintf(argtab,"%s\n",token);
                    argumentMapIndex++;
                    token = strtok(NULL,",");
                }
                
                fprintf(output,"%d\t\t",outputLineNo);
                if(strcmp(label,"-")!=0)
                {
                    fprintf(output,".");
                    cflag=1;
                }
                fprintf(output,"%s\t\t",label);

                while(defLine!=searchResult.start)
                    fscanf(deftab,"%d%s%s",&defLine,opcode,operand);
                
                if(cflag==-1)
                    fprintf(output,".");
                
                char *token2 = strtok(operand,",");
                int i=0;
                while(token2!=NULL)
                {
                    strcpy(argumentMap[i++].key,token2);
                    token2 = strtok(NULL,",");
                }

                fprintf(output,"%s\t\t%s\n",opcode,arguments);
                outputLineNo+=5;

                fscanf(deftab,"%d%s%s",&defLine,opcode,operand);
                fprintf(output,"%d\t\t",outputLineNo);

                if(cflag==1)
                    fprintf(output,"%s\t\t",label);
                else
                    fprintf(output,"-\t\t");

                fprintf(output,"%s\t\t",opcode);
                strcpy(operand,replaceArg(argumentMap,argumentMapIndex,token,operand));
                fprintf(output,"%s",operand);

                fprintf(output,"\n");
                outputLineNo+=5;

                while(defLine!=searchResult.end-5)
                {
                    fscanf(deftab,"%d%s%s",&defLine,opcode,operand);
                    fprintf(output,"%d\t\t-\t\t%s\t\t",outputLineNo,opcode);
                    
                    strcpy(operand,replaceArg(argumentMap,argumentMapIndex,token,operand));
                    fprintf(output,"%s",operand);

                    fprintf(output,"\n");
                    outputLineNo+=5;
                }

                fclose(deftab);
            }
            else
            {
                fprintf(output,"%d\t\t%s\t\t%s\t\t%s\n",outputLineNo,label,opcode,operand);
                outputLineNo+=5;
            }
        }
    }

    fclose(input);
    fclose(output);
    fclose(argtab);
}