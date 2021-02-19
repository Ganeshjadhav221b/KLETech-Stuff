#include "pass1.h"
void pass1()
{
    FILE *fp,*fp1,*fp2;
    fp=fopen("input1.txt","r");
    fp1=fopen("optab.txt","r");
    fp2=fopen("intermediate.txt","w");
    int word_count,LOCCTR,i,flag=0,coma,pos;
    char str[100],col1[100],opcode[50],str1[50],col2[50],str2[50];
    char previous='~',R1,R2;
    LOCCTR=4096;
    //printf("%X is start address\n",LOCCTR);
    printf("%X\t",LOCCTR);
    while(fgets(str,30,fp))
    {
    printf("%s\n",str);
        word_count=0;
        for(i=0;str[i]!='\0';i++)
        {
            if(isspace(str[i]))
            {
                if(!isspace(previous))
                {
                    word_count++;
                }
                previous=32;
            }
            else{
                previous=str[i];
            }
        }
        if(word_count==1)
        {
            sscanf(str,"%s",&col1);
            rewind(fp1);
            while(!feof(fp1))                  //search optab for opcode
            {
                fgets(str1,30,fp1);
                sscanf(str1,"%s",&opcode);
                //printf("%s\n",opcode);
                if(strcmp(col1,opcode)==0)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                LOCCTR=LOCCTR+1;
                printf("%X\t",LOCCTR);
                //printf("%X\t",LOCCTR);
                //printf("%s\n",col1);
            }
            else
            {
               printf("%s opcode not found\n",col1);
            }

        }
        if(word_count==2)
        {
            coma=0;
            sscanf(str,"%s %s",&col1,&col2);
            for(i=0;col2[i]!='\0';i++)
            {
                if(col2[i]==',')
                {
                    coma++;
                    pos=i;
                    break;
                }
            }
            if(coma==0)
            {
               if(col1[0]=='+')         ///format 4
               {
                   //printf("%s\n",str);
                   rewind(fp1);
                    while(!feof(fp1))                  //search optab for opcode
                    {
                        fgets(str1,30,fp1);
                        sscanf(str1,"%s",&opcode);
                        //printf("%s\n",opcode);
                        if(strcmp(col1,opcode)==0)
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==1)
                    {
                        LOCCTR=LOCCTR+4;
                        printf("%X\t",LOCCTR);
                        //printf("%s",col1);
                    }
                    else
                    {
                        printf("%s opcode not found\n",col1);
                    }
                    //printf("format4\n");
               }
               else             ///format 2 with one register
               {
                   //printf("1 register\n");
                    //printf("%s",str);
                    LOCCTR=LOCCTR+2;
                    printf("%X\t",LOCCTR);
                    R1=col2[0];
                    if(R1=='A'||R1=='X'||R1=='L'||R1=='B'||R1=='S'||R1=='T'||R1=='F')
                    {
                        //printf("\nValid register\n");
                    }
                    else
                    {
                        printf("\nInvalid register\n");
                    }
               }
            }
            else if(coma==1)        ///format 2 with 2 registers
            {
                //printf("2 registers\n");
                //printf("%s",str);
                LOCCTR=LOCCTR+2;
                printf("%X\t",LOCCTR);
                R1=col2[pos-1];
                R2=col2[pos+1];
                //printf("%c and %c\n",R1,R2);
                if((R1=='A'||R1=='X'||R1=='L'||R1=='B'||R1=='S'||R1=='T'||R1=='F')&&(R2=='A'||R2=='X'||R2=='L'||R2=='B'||R2=='S'||R2=='T'||R2=='F'))
                {
                    //printf("\nValid registers\n");
                }
                else
                {
                    printf("\nInvalid registers\n");
                }
            }
            else
            {
                printf("\nIncorrect instruction\n");
            }
        }
    }
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
}
/*int search_optab(char col1[50])
{
    FILE *fp1;
    //printf("%s",col1);
    int flag=0;
    char opcode[100],str1[100],value[50];
    fp1=fopen("optab.txt","r");
    while(!feof(fp1))                  //search optab for opcode
    {
        fgets(str1,30,fp1);
        sscanf(str1,"%s %d",&opcode,&value);
        //printf("%s\n",opcode);
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
    FILE *fp,*fp2,*fp3;
    fp=fopen("input.txt","r");
    fp2=fopen("intermediate.txt","w");
    int wc, LOCCTR, i, coma,x,start_addr,flag;
    char str[100],col1[100],opcode[50],str1[50],col2[50],str2[50];
    fgets(str,30,fp);
    sscanf(str,"%s %s %d",col1,col2,&x);
    if(strcmp(col2,"START")==0)
    {
        //printf("%d",x);
        printf("Starting address is %X\n",LOCCTR=x);
        start_addr=LOCCTR;
        //printf("%X\t",LOCCTR);
        //fprintf(fp2,"%X\t",LOCCTR);
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
        wc=word_count(str);
        if(wc==1)
        {
            sscanf(str,"%s",&col1);
            flag=search_optab(col1);
        //printf("%d is flag",flag);
            if(flag==1)
            {
                LOCCTR=LOCCTR+1;
            //printf("%X\t",LOCCTR);
                fprintf(fp2,"%X\t",LOCCTR);
            //printf("%s\n",col1);
                fprintf(fp2,"%s\n",LOCCTR);
            }
            else
            {
               printf("%s opcode not found\n",col1);
            }
        }
    }
    fclose(fp2);
    fclose(fp);
}*/
