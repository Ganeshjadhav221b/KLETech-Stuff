#include"header.h"

void objectCode()
{
    FILE *fp1,*fp2,*fp3,*fp4;
    fp1 = fopen("intermediate.txt","r");
    fp2 = fopen("optab.txt","r");
    fp3 = fopen("symtab.txt","r");
    fp4 = fopen("objectCode.txt","w");
    char str[50],str1[50],str2[50];

    int addr=0,i,c;
    int length= 0;
    int startAddr=0;
    while(fgets(str,50,fp1))
    {

        int count = word_count(str);
        //printf("%d\t%s", count, str);
        char operand[50],opcode[50],label[50],op[50], addr[50];
        int address;
        int opValue;
        int flag =0;

        if (count == 4)
        {
            sscanf(str,"%s%s%s%s",addr,label,opcode,operand);
            address = atoi(addr);
            if(strcmp(opcode,"START")==0)
            {
                fprintf(fp4,"%s\t%s\t%s\t%s\n",addr,label,opcode,operand);
                continue;
            }

            else if(strcmp(opcode,"RESW")==0 || strcmp(opcode,"RESB")==0 )
            {
                fprintf(fp4,"%s\t%s\t%s\t%s\n",addr,label,opcode,operand);
                continue;
            }

            else if(strcmp(opcode,"BYTE")==0)
            {
                fprintf(fp4,"%s\t%s\t%s\t%s\t",addr,label,opcode,operand);
                if(operand[0] == 'C')
                {
                    for(i=2;operand[i] != '\'';i++)
                        fprintf(fp4,"%x",operand[i]);
                }
                else
                {
                    for(i=2;operand[i] != '\'';i++)
                     fprintf(fp4,"%c",operand[i]);
                }
                fprintf(fp4,"\n");
                continue;
            }
            else if(strcmp(opcode,"WORD")==0)
            {
                fprintf(fp4,"%s\t%s\t%s\t%s\t",addr,label,opcode,operand);
                for(i=0;i<5;i++)
                        fprintf(fp4,"0");
                for(i=0;operand[i] != '\0';i++)
                    fprintf(fp4,"%c",operand[i]);
                fprintf(fp4,"\n");
                continue;
            }

            else
            {
                //printf("Here\n");
                rewind(fp2);
                while(fgets(str1,50,fp2))
                {
                    char op[50],opValue[50];
                    int opVal;
                    sscanf(str1,"%s%s",op,opValue);
                    opVal = atoi(opValue);
                    //printf("In optab: Comparing %s with %s\n",opcode,op);
                    if(strcmp(opcode,op)==0)
                    {
                        //printf("Found %s\n",op);
                        rewind(fp3);
                        while(fgets(str2,50,fp3))
                        {
                            char symbol[50],symValue[50];
                            int symVal;
                            sscanf(str2,"%s%s",symValue,symbol);
                            //printf("He--%s%s\n",symValue,symbol);
                            symVal = atoi(symValue);
                            //printf("In symtab: Comparing %s with %s\n",operand,symbol);
                            if(strcmp(operand,symbol)==0)
                            {
                                //printf("Found %s\n",label);
                                fprintf(fp4,"%s\t%s\t%s\t%s\t%d%d\n",addr,label,opcode,operand,opVal,symVal);
                                break;
                            }
                        }
                    }
                }
            }
        }

        else if (count == 3)
        {
            sscanf(str,"%s%s%s",addr,opcode,operand);
            address = atoi(addr);
            rewind(fp2);
            while(fgets(str1,50,fp2))
            {
                char op[50],opValue[50];
                int opVal;
                sscanf(str1,"%s%s",op,opValue);
                opVal = atoi(opValue);
                //printf("In optab: Comparing %s with %s\n",opcode,op);
                if(strcmp(opcode,op)==0)
                {
                    //printf("Found %s\n",op);
                    rewind(fp3);
                    while(fgets(str2,50,fp3))
                    {
                        char symbol[50],symValue[50];
                        int symVal;
                        sscanf(str2,"%s%s",symValue,symbol);
                        //printf("He--%s%s\n",symValue,symbol);
                        symVal = atoi(symValue);
                        //printf("In symtab: Comparing %s with %s\n",operand,symbol);
                        if(strcmp(operand,symbol)==0)
                        {
                            //printf("Found %s\n",label);
                            fprintf(fp4,"%s\t\t%s\t%s\t%s%s\n",addr,opcode,operand,opValue,symValue);
                            break;
                        }
                    }
                    break;
                }
            }
        }

        else if (count == 2)
        {
            sscanf(str,"%s%s",addr,opcode);
            address = atoi(addr);
            fprintf(fp4,"%s",str);
            if(strcmp(opcode,"END")==0)
                break;
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    //fclose(fp5);
}

