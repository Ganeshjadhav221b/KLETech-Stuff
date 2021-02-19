#include "pass1.h"
void pass1()
{
    FILE *fp;
    char str[100];
    char col1[50];
    char str1[50];
    char col2[50];
    char col3[50];
    char opcode[50];
    int value;
    FILE *fp1;
    FILE*fp2;
    FILE *fp4;
    int count;
    FILE *fp3;
    int LOCCTR;
    int start_addr;
    int last_addr;
    fp=fopen("input1.txt","r");
    fp1=fopen("symtab.txt","w");
    //fprintf(fp1,"HELLO");
    fp2=fopen("optab.txt","r");
    fp3=fopen("intermediate.txt","w");
    int op;
    int x;
    int i;
    int word_count=0;
    char previous='~';
    //char a[10]="Hello";
    fgets(str,30,fp);
    //fprintf(fp3,"%s",str);
    sscanf(str,"%s %s %d",col1,col2,&x);
    //fprintf(fp3,"%s",a);
    if(strcmp(col2,"START")==0)
    {
        //fprintf(fp3,"%s",str);
        printf("Starting address is %X\n",LOCCTR=x);
        start_addr=LOCCTR;                 //Starting address is stored;
        fprintf(fp3,"%X\t",LOCCTR);        //writing first line to intermediate file
        //printf("%X\t",LOCCTR);
        fprintf(fp3,"%s",str);
        //printf("%s",str);
    }
    else
    {
        LOCCTR=0;
        //#printf("START opcode not found\n");
        //#printf("Starting address is %X",LOCCTR);
        //exit(0);
    }
    while(fgets(str,30,fp))
    {
         word_count=0;
         int flag=0;
        fprintf(fp3,"%X\t",LOCCTR);
        fprintf(fp3,"%s",str);
        //printf("%s",str);
        for(i=0;str[i]!='\0';i++)
        {
            if(isspace(str[i]))
            {
                if(!isspace(previous))
                    word_count++;

                previous=32;
            }
            else

                previous=str[i];
        }
        //printf("%d word(s) are present\n",word_count);
        if(word_count==3)
        {
             sscanf(str,"%s %s %d",col1,col2,&x);
             fprintf(fp1,"%X\t%s\n",LOCCTR,col1);
             rewind(fp2);
                while(!feof(fp2))                  //search optab for opcode
                {
                    fgets(str1,30,fp2);
                    sscanf(str1,"%s %d",&opcode,value);
                    //printf("%s\n",opcode);
                    if(strcmp(col2,opcode)==0)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    LOCCTR=LOCCTR+3;
                }
                else
                {
                   if(strcmp(col2,"WORD")==0)
                    {
                        //printf("%s\n",col2);
                        LOCCTR=LOCCTR+3;
                        //printf("%X\t",LOCCTR);
                        //break;
                    }
                    else if(strcmp(col2,"RESW")==0)
                    {
                        sscanf(str,"%s %s %d",&col1,&col2,&op);
                        LOCCTR=LOCCTR+(op*3);
                        //break;
                    }
                    else if(strcmp(col2,"RESB")==0)
                    {
                        sscanf(str,"%s %s %d",&col1,&col2,&op);
                        LOCCTR=LOCCTR+op;
                        //break;
                    }

                    else if(strcmp(col2,"BYTE")==0)
                    {
                        //count=0;
                        //printf("%s",str);
                        sscanf(str,"%s %s %s",&col1,&col2,&col3);
                        //printf("%s",col3);
                        if(col3[0]=='C')
                        {

                            for(i=2;col3[i]!='\0';i++)
                                continue;

                            int d=i-3;

                        }
                        int d;
                        if(col3[0]=='X')
                        {
                            for(i=2;col3[i]!='\0';i++)
                            {
                                continue;
                            }
                             d=(i-3)/2;
                            //printf("%d is count\n",d);
                        }
                        LOCCTR=LOCCTR+d;
                    }
                    else
                    {
                        printf("No such opcode %s found\n",col2);
                    }

                }
            }
            if(word_count==2)
            {
                sscanf(str,"%s %s",col2,col3);
             //fprintf(fp1,"%X\t%s\n",LOCCTR,col1);
             rewind(fp2);
                while(!feof(fp2))                  //search optab for opcode
                {
                    fgets(str1,30,fp2);
                    sscanf(str1,"%s %d",&opcode,value);
                    //printf("%s\n",opcode);
                    if(strcmp(col2,opcode)==0)
                    {
                        flag=1;
                        break;
                    }
                }
                    if(flag==1)
                    {
                        LOCCTR=LOCCTR+3;
                    }
                    else
                    {
                        printf("%s not found\n",col2);
                    }

            }
            if(word_count==1)
            {
                sscanf(str,"%s",col2);
                if(strcmp(col2,"END")==0)
                {
                    last_addr=LOCCTR;
                    break;
                }
                else
                {
                    LOCCTR=LOCCTR+3;
                }
            }
        }
    //printf("%d is last value\n",LOCCTR);
    //printf("%d is start",start_addr);
    int len=LOCCTR-start_addr;
    printf("%X is the length of the program\n",len);
    fp4=fopen("length.txt","w");
    fprintf(fp4,"%X",len);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fp=fopen("symtab.txt","a");
    fprintf(fp,"2039\tRDREC\n");
    fprintf(fp,"2061\tWRREC\n");
    fclose(fp);
    }



