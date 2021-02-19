#include "sicxe.h"
int search_optab(char col1[50])
{
    FILE *fp1;
    int flag=0;
    char opcode[100],str1[100],value[50];
    fp1=fopen("optab.txt","r");
    while(!feof(fp1))                  ///search optab for opcode
    {
        fgets(str1,30,fp1);
        sscanf(str1,"%s %d",&opcode,&value);
        if(strcmp(col1,opcode)==0)
        {
            flag=1;
            break;
        }
    }
    fclose(fp1);
    return flag;
}

int word_count(char str[100])
{
    char previous='~';
    int wc=0,i;
    for(i=0;str[i]!='\0';i++)
    {
        if(isspace(str[i]))
        {
            if(!isspace(previous))
            {
                wc++;
            }
            previous=32;
        }
        else
        {
            previous=str[i];
        }
    }

    return wc;
}
void pass1()
{
    FILE *fp,*fp1,*fp2,*fp3;
    fp=fopen("input1.txt","r");
    //fp=fopen("sic-xe-input.txt","r");
    fp1=fopen("symtab.txt","w");
    fp2=fopen("intermediate.txt","w");
    if(fp2==NULL)
    {
        printf("error opening file.");
        exit(0);
    }
    int wc, LOCCTR, i, coma, x, start_addr, flag, pos, op, last_addr;
    char str[100],col1[100],opcode[50],str1[50],col2[50],col3[50],R1,R2;
    fgets(str,30,fp);
    sscanf(str,"%s %s %d",col1,col2,&x);
    if(strcmp(col2,"START")==0)
    {
        printf("Starting address is %X\n",LOCCTR=x);
        start_addr=LOCCTR;
        fprintf(fp2,"%X\t",LOCCTR);
        fprintf(fp2,"%s",str);
    }
    else
    {
        LOCCTR=0;
        printf("START opcode not found\n");
        printf("Starting address is %X",LOCCTR);
    }
    while(fgets(str,30,fp))
    {
        //printf("%s",str);
        fprintf(fp2,"%X\t",LOCCTR);
        fprintf(fp2,"%s",str);
        wc=word_count(str);
         //printf("%d is word count\n",wc);
       if(wc==1)
        {
            sscanf(str,"%s",&col2);
            flag=search_optab(col2);
        //printf("%d is flag",flag);
            if(flag==1)
            {
                LOCCTR=LOCCTR+1;
            }
            else
            {
               printf("%s opcode not found\n",col2);
            }
        }
        else if(wc==2)
        {
            coma=0;
            sscanf(str,"%s %s",&col2,&col3);
            if(strcmp(col2,"END")==0)
            {
                last_addr=LOCCTR;
                break;
            }
            for(i=0;col3[i]!='\0';i++)
            {
                if(col3[i]==',')
                {
                    coma++;
                    pos=i;
                    break;
                }
            }
            //printf("%d is coma",coma);
            if(coma==0)
            {
                char temp[50];
                int k=0,j;
                if(col2[0]=='+')                ///format 4
                {
                    for(j=1;col2[j]!='\0';j++)
                    {
                        temp[k++]=col2[j];        ///temp is initialized with the opcode value except for '+'
                    }
                    temp[k]='\0';
                    //printf("%s is str",str);
                    //printf("%s is temp",temp);
                    flag=search_optab(temp);
                    if(flag==1)
                    {
                        LOCCTR=LOCCTR+4;
                    }
                    else
                    {
                        printf("%s opcode not found in optab\n",temp);
                    }
                }
                else            ///format 2 instruction with one register
                {
                    //printf("%s is col3",col3);
                    int len=0;
                    for(i=0;col3[i]!='\0';i++)
                    {
                        len++;
                    }
                    if(len==1)
                    {
                        R1=col3[0];
                        if(R1=='A'||R1=='X'||R1=='L'||R1=='B'||R1=='S'||R1=='T'||R1=='F')
                        {
                            //printf("\nValid register\n");
                            LOCCTR=LOCCTR+2;
                        }
                    }
                    else if(len>1)
                    {
                        flag=search_optab(col2);
                        if(flag==1)
                        {
                            LOCCTR=LOCCTR+3;
                        }
                        else
                        {
                            printf("error!!");
                        }
                    }
                    else
                    {
                        printf("Invalid register!!");
                    }
                }
            }
            else if(coma==1)
            {
                int len=0;
                for(i=0;col3[i]!='\0';i++)
                {
                    len++;
                }
                if(len==3)
                {
                   R1=col3[pos-1];
                    R2=col3[pos+1];
                    if((R1=='A'||R1=='X'||R1=='L'||R1=='B'||R1=='S'||R1=='T'||R1=='F')&&(R2=='A'||R2=='X'||R2=='L'||R2=='B'||R2=='S'||R2=='T'||R2=='F'))
                    {
                        //printf("\nValid registers\n");
                        LOCCTR=LOCCTR+2;
                    }
                    else
                    {
                        printf("\nInvalid registers\n");
                    }
                }
                else  if(len>3)                              /// else it is format 3 instruction.
                {
                    flag=search_optab(col2);
                    if(flag==1)
                    {
                        LOCCTR=LOCCTR+3;
                    }
                }
                else //if((coma!=0)||(coma!=1))
                {
                printf("Invalid instruction");   ///if more than one , then it's invalid instruction.
                }
            }
        }
        else if(wc==3)
        {
            coma=0;
            sscanf(str,"%s %s %s",&col1,&col2,&col3);
            fprintf(fp1,"%X\t%s\n",LOCCTR,col1);
            for(i=0;col3[i]!='\0';i++)
            {
                if(col3[i]==',')
                {
                    coma++;
                    pos=i;
                    break;
                }
            }
            if(coma==0)
            {
                char temp[50];
                int k=0,j;
                if(col2[0]=='+')                ///format 4
                {
                    for(j=1;col2[j]!='\0';j++)
                    {
                        temp[k++]=col2[j];        ///temp is initialized with the opcode value except for '+'
                    }
                    temp[k]='\0';
                    flag=search_optab(temp);
                    if(flag==1)
                    {
                        LOCCTR=LOCCTR+4;
                    }
                    else
                    {
                        printf("%s opcode not found in optab\n",temp);
                    }
                }

                else
                {
                    int len=0;
                    for(i=0;col3[i]!='\0';i++)
                    {
                        len++;
                    }
                    if(len==1)               ///format 2 instruction with one register
                    {
                        R1=col3[0];
                        if(R1=='A'||R1=='X'||R1=='L'||R1=='B'||R1=='S'||R1=='T'||R1=='F')
                        {
                            //printf("\nValid register\n");
                            LOCCTR=LOCCTR+2;
                        }
                        else                /// it can still have one character in col3 which can be RESW or RESB type of instructions
                        {
                            if(strcmp(col2,"RESW")==0)
                            {
                                sscanf(str,"%s %s %d",&col1,&col2,&op);
                                LOCCTR=LOCCTR+(op*3);
                            }
                            else if(strcmp(col2,"RESB")==0)
                            {
                                sscanf(str,"%s %s %d",&col1,&col2,&op);
                                LOCCTR=LOCCTR+op;
                            }
                        }
                    }

                    else if(len>1)
                    {
                        flag=search_optab(col2);
                        if(flag==1)
                        {
                            LOCCTR=LOCCTR+3;
                        }
                        else
                        {
                            if(strcmp(col2,"WORD")==0)
                            {
                                LOCCTR=LOCCTR+3;
                            }
                            else if(strcmp(col2,"RESW")==0)
                            {
                                sscanf(str,"%s %s %d",&col1,&col2,&op);
                                LOCCTR=LOCCTR+(op*3);
                            }
                            else if(strcmp(col2,"RESB")==0)
                            {
                                sscanf(str,"%s %s %d",&col1,&col2,&op);
                                LOCCTR=LOCCTR+op;
                            }
                            else if(strcmp(col2,"BYTE")==0)
                            {
                                sscanf(str,"%s %s %s",&col1,&col2,&col3);
                                if(col3[0]=='C')
                                {
                                    for(i=2;col3[i]!='\0';i++)
                                    {
                                        continue;
                                    }
                                    int d=i-3;
                                    LOCCTR=LOCCTR+d;
                                }
                                if(col3[0]=='X')
                                {
                                    for(i=2;col3[i]!='\0';i++)
                                    {
                                        continue;
                                    }
                                    int d=(i-3)/2;
                                    LOCCTR=LOCCTR+d;
                                }
                            }
                            else
                            {
                                printf("No such opcode %s found\n",col2);
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid register.");
                    }
                }
            }
            else if(coma==1)
            {
                int len=0;
                for(i=0;col3[i]!='\0';i++)
                {
                    len++;
                }
                if(len==3)
                {
                    R1=col3[pos-1];
                    R2=col3[pos+1];
                    if((R1=='A'||R1=='X'||R1=='L'||R1=='B'||R1=='S'||R1=='T'||R1=='F')&&(R2=='A'||R2=='X'||R2=='L'||R2=='B'||R2=='S'||R2=='T'||R2=='F'))
                    {
                        //printf("\nValid registers\n");
                        LOCCTR=LOCCTR+2;
                    }
                }
                else if(len>3)
                {
                    flag=search_optab(col2);
                    if(flag==1)
                    {
                        LOCCTR=LOCCTR+3;
                    }
                }
                else
                {
                    printf("\nInvalid registers\n");
                    exit(2);
                }
            }
            else if((coma!=0)||(coma!=1))
            {
               printf("Invalid instruction");
            }
            else                                /// else it is format 3 instruction.
            {
                flag=search_optab(col2);
                if(flag==1)
                {
                    LOCCTR=LOCCTR+3;
                }
            }
        }
    }
    int length=LOCCTR-start_addr;
    printf("Length of the program is %X\n",length);
    fclose(fp2);
    fclose(fp1);
    fclose(fp);
    /*fp3=fopen("input2.txt","r");
    while(fgets(str,30,fp3))
    {
        wc=call1(str);
        printf("%d is count\n",wc);
    }*/
}
