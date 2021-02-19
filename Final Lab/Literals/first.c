#include"header.h"
int word_count(char str[])
{
    int i,count=0;
    char previous='~';
    for(i=0;str[i]!='\0';i++)
    {
        if(isspace(str[i])&&previous=='~' )
            continue;
        if(isspace(str[i]))
        {
            if(!isspace(previous))
                count++;           ///to keep the count of words in each line
            previous=32;
        }
        else
            previous=str[i];
    }
    return count;
}

void first()
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1 = fopen("input.txt","r");
    fp2 = fopen("optab.txt","r");
    fp3 = fopen("symtab.txt","w");
    fp4 = fopen("intermediate.txt","w");
    fp5 = fopen("littab.txt","w");
    char str[50],str1[50],str2[50];

    int addr=0,i,c;
    int length= 0;
    int startAddr=0;
    while(fgets(str,50,fp1))
    {
        int count = word_count(str);
        //printf("%d\t%s", count, str);
        char operand[50],opcode[50],label[50],op[50];
        int opValue;
        int flag =0;

        if (count == 3)
        {
            sscanf(str,"%s%s%s",label, opcode, operand);
            if(strcmp(opcode,"START")!=0)
            {
                //printf("%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
                fprintf(fp3,"%X\t%s\n",addr,label);
                fprintf(fp4,"%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
                flag=1;
            }
            if(strcmp(opcode,"START")==0)
            {
                addr = atoi(operand);
                printf("Starting address: %X\n",addr);
                startAddr = addr;
                //printf("Address: %d\n",startAddr);
                //printf("%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
                fprintf(fp3,"%X\t%s\n",addr,label);
                fprintf(fp4,"%X\t%s\t%s\t%s\n",addr,label,opcode,operand);
                continue;
            }

            else if(strcmp(opcode,"BYTE")==0)
            {
                if(operand[0] == 'C')
                {
                    c=0;
                    for(i=0 ; operand[i]!='\0';i++)
                        c++;
                    addr+= c-3;
                    flag = 1;
                }
                else
                {
                    c=0;
                    for(i=0 ; operand[i]!= '\0';i++)
                        c++;
                    addr+= (c-3)/2;
                    flag = 1;
                }
            }
            else if(strcmp(opcode,"WORD")==0)
            {
                addr+=3;
                flag = 1;
            }
            else if(strcmp(opcode,"RESW")==0)
            {
                //sscanf(operand,"%d",c);
                //printf("here");
                c= atoi(operand);
                addr = addr + c*3;
                flag = 1;
            }
            else if(strcmp(opcode,"RESB")==0)
            {
                c= atoi(operand);
                addr = addr+c;
                flag = 1;
            }

            else
            {
                rewind(fp2);
                while(fgets(str1,50,fp2))
                {
                    char opVal[50];
                    //printf("%s",str1);
                    sscanf(str1,"%s%s",op,opVal);
                    //printf("%s-%s\n",op,opcode);
                    if (strcmp(op,opcode) == 0)
                    {
                        flag = 1;
                        addr += 3;
                        //printf("Found %s in optab", opcode);
                        break;
                    }
                }
                if(operand[i] == '=')
                {
                    for(i=1;operand[i]!='\'';i+=)
                    {
                            fprintf(fp,);


                    }

                }
            }

            if(flag == 0 )
            {
                printf("No corresponding opcode for %s found in optab", opcode);
            }
           // else
        }

        //
        else if (count == 2)
        {
            flag=0;
            sscanf(str,"%s%s", opcode, operand);
            //printf("%X\t\t%s\t%s\n",addr,opcode,operand);
            fprintf(fp4,"%X\t\t%s\t%s\n",addr,opcode,operand);
            rewind(fp2);
            while(fgets(str1,50,fp2))
            {
                char opVal[50];
                sscanf(str1,"%s%s",op,opVal);
                //printf("%s-%s\n",op,opcode);
                if (strcmp(op,opcode) == 0)
                {
                    flag = 1;
                    addr += 3;
                    //printf("Found %s in optab", opcode);
                    break;
                }
            }
            if(flag == 0 )
            {
                printf("No corresponding opcode for %s found in optab", opcode);
            }
        }
        else if (count == 1)
        {
            flag=0;
            sscanf(str,"%s", opcode);
            //printf("%X\t\t%s\n",addr,opcode);
            fprintf(fp4,"%X\t\t%s\n",addr,opcode);
            rewind(fp2);
            while(fgets(str1,50,fp2))
            {
                char opVal[50];
               // printf("--%s",str1);
                sscanf(str1,"%s%s",op,opVal);
                //printf("%s-%s\n",op,opcode);
                if (strcmp(op,opcode) == 0)
                {
                    flag = 1;
                    addr += 3;
                    //printf("Found %s in optab", opcode);
                    break;
                }
            }
            //printf("sfs");

            if(flag == 0 )
            {
                printf("No corresponding opcode for %s found in optab", opcode);
            }
        }
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    //fclose(fp5);

    //printf("%d - %d\n",addr, startAddr);
}
