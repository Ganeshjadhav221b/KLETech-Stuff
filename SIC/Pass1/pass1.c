#include"pass1.h"

int findWords(char str[])
{
   int i,j,k;
   int wordCount=0;
   static char previous = '~';
   for(i=0;str[i]!='\0';i++)
    {
        if(isspace(str[i]))
        {
            if(!isspace(previous))
                wordCount++;

            previous=32;
        }
        else
            previous=str[i];
    }
    return wordCount;
}


void first()
{

    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    char str1[100],str2[100],str3[100],str4[100];
    char opcode[100],label[100],operand[100],str5[100];
    int a,b,c,d;
    int temp1,temp2,temp3,temp4;
    int address = 1000;
    int i,j,k;
    int spaces=0;
    int wordCount = 0;
    int LOCCTR = 0;
    int startAddr = 0;
    int len=0;

    fp1 = fopen("input.txt","r");
    fp2 = fopen("intermediate.txt","w");
    fp3 = fopen("symtab.txt","w");

    if(fp1 == NULL )
        printf("ERROR opening input file!");

    fgets (str1, 60, fp1);
    sscanf(str1,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        printf("Starting address is %X\n",LOCCTR = atoi(operand));
        startAddr=LOCCTR;                 //Starting address is stored;
    }
    else
    {
        LOCCTR=0;
    }

     //printf("%X\t%s\t%s\t%s\n",LOCCTR,label,opcode,operand);
    fprintf(fp2,"%X\t%s\t%s\t%s\n",LOCCTR,label,opcode,operand);
    fprintf(fp3,"%X\t%s\n",LOCCTR,label);

    while( fgets (str1, 60, fp1)!=NULL )
    {
        wordCount = findWords(str1);
        //printf("%d",wordCount);
        if (wordCount == 3)
        {
            sscanf(str1,"%s%s%s",label,opcode,operand);
            //printf("%X\t%s\t%s\t%s\n",LOCCTR,label,opcode,operand);
            fprintf(fp2,"%X\t%s\t%s\t%s\n",LOCCTR,label,opcode,operand);
            fprintf(fp3,"%X\t%s\n",LOCCTR,label);

            if(strcmp(opcode,"BYTE")==0)
            {
                if(operand[0]=='C')
                {
                     len=0;
                    for(i=2;operand[i]!='\0';i++)
                        len++;
                    LOCCTR+=(len-1);
                }
                else if(operand[0]=='X')
                {
                     len=0;
                    for(i=2;operand[i]!='\0';i++)
                        len++;
                    LOCCTR+=(len-1)/2;
                }
            }

            else if(strcmp(opcode,"RESB")==0)
            {
                len=0;
                len = atoi(operand);
                LOCCTR+=len;
            }

            else if(strcmp(opcode,"RESW")==0)
            {
                len=0;
                len = atoi(operand);
                LOCCTR+=len*3;
            }

             else if(strcmp(opcode,"WORD")==0)
            {
                len=0;
                len = atoi(operand);
                LOCCTR+=3;
            }
            else
                LOCCTR+=3;
        }
        else if(wordCount == 2)
        {
            sscanf(str1,"%s%s",opcode,operand);
            //printf("%X\t\t%s\t%s\n",LOCCTR,opcode,operand);
            fprintf(fp2,"%X\t\t%s\t%s\n",LOCCTR,opcode,operand);
            LOCCTR+=3;
        }
        else if(wordCount == 1)
        {
            sscanf(str1,"%s",opcode);
            //printf("%X\t\t%s\n",LOCCTR,opcode);
            fprintf(fp2,"%X\t\t%s\n",LOCCTR,opcode);
            LOCCTR+=3;
        }
        else
            printf("error here!");
    }
    printf("END of SIC pass 1!\n");
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

}


