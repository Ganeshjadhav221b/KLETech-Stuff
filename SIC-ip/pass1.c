#include "sic.h"
void pass1()
{
    FILE *fp,*fp1,*fp2,*fp3,*fp4;
    fp=fopen("input.txt","r");
    fp1=fopen("symtab.txt","w");
    fp2=fopen("optab.txt","r");
    fp3=fopen("intermediate.txt","w");
    fp4=fopen("literals.txt","w");
    char str[100],col1[100],col2[100],col3[100],opcode[100],str1[100],str2[100];
    char previous='~';
    int x,LOCCTR,start_addr,last_addr,word_count,i,value,op,lit_flag=0;
    fgets(str,30,fp);
    sscanf(str,"%s %s %d",col1,col2,&x);
    if(strcmp(col2,"START")==0)
    {
        printf("Starting address is %X\n",LOCCTR=x);
        start_addr=LOCCTR;                 ///Starting address is stored;
        fprintf(fp3,"%X\t",LOCCTR);        ///writing first line to intermediate file
        fprintf(fp3,"%s",str);
    }
    else
    {
        LOCCTR=0;
        printf("START opcode not found\n");
        printf("Starting address is %X",LOCCTR);
    }
    while(fgets(str,30,fp))
    {
        word_count=0;
         int flag=0;
        fprintf(fp3,"%X\t",LOCCTR);
        fprintf(fp3,"%s",str);
        for(i=0;str[i]!='\0';i++)               ///get the word count for each line
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
        //printf("%d is word_count\n",word_count);
        if(word_count==3)
        {
            sscanf(str,"%s %s %s",&col1,&col2,&col3);
            fprintf(fp1,"%X\t%s\n",LOCCTR,col1);        ///writing to the symtab
            rewind(fp2);
            while(!feof(fp2))
            {
                fgets(str1,30,fp2);
                sscanf(str1,"%s %d",&opcode,&value);
                if(strcmp(opcode,col2)==0)              ///serach optab for opcode
                {
                    flag=1;
                    break;
                }
            }
            //printf("%c is col3[0]\n",col3[0]);
            if(col3[0]=='=')
            {
                lit_flag=1;          ///literal is found, literal flag is set.
            }
            if(lit_flag==1)
            {
                int length=0;
                int no_char;
                fprintf(fp4,"%s\t",col3);
                lit_flag=0;
                for(i=0;col3[i]!='\0';i++)
                {
                    length++;               ///length of the literal
                }
                //fprintf(fp4,"%d\t",length);

                if(col3[1]=='C')
                {
                    for(i=3;i<length-1;i++)
                    {
                        int e=col3[i];              ///get the ascii equivalent value of character
                        fprintf(fp4,"%X",e);        ///write it to the literals file in hex
                    }
                fprintf(fp4,"\t");
                no_char=length-4;
                }
                else
                {
                    char temp[20];
                    int j=0;
                    for(i=3;i<length-1;i++)         ///if literal is of type X,
                    {
                        temp[j]=col3[i];
                        j++;
                    }
                    temp[j]='\0';
                    //printf("%s is temp",temp);
                    fprintf(fp4,"%s\t",temp);       ///write opcode as it is to literals file
                    no_char=(length-4)/2;
                }
                //printf("%d is length\n",no_char);
                fprintf(fp4,"%d\n",no_char);    ///write the number of characters in literal to the literals
                fclose(fp4);
            }
            //printf("%d is literal flag\n",lit_flag);
            if(flag==1)
            {
                LOCCTR=LOCCTR+3;
            }
            else
                {
                   if(strcmp(col2,"WORD")==0)
                    {
                        LOCCTR=LOCCTR+3;                ///if operand is WORD add 3 to location counter
                    }
                    else if(strcmp(col2,"RESW")==0)     ///if operand is RESW
                    {
                        sscanf(str,"%s %s %d",&col1,&col2,&op);
                        LOCCTR=LOCCTR+(op*3);                   ///add the number of bytes occupied by value present in opcode column
                    }
                    else if(strcmp(col2,"RESB")==0)             ///if operand is RESB
                    {
                        sscanf(str,"%s %s %d",&col1,&col2,&op);
                        LOCCTR=LOCCTR+op;                       ///add the opcode value to location counter
                    }
                    else if(strcmp(col2,"BYTE")==0)
                    {
                        //count=0;
                        //printf("%s",str);
                        sscanf(str,"%s %s %s",&col1,&col2,&col3);
                        //printf("%s",col3);
                        if(col3[0]=='C')            ///if the byte is of character type
                        {

                            for(i=2;col3[i]!='\0';i++)
                            {
                                continue;
                            }
                            int d=i-3;
                            //printf("%d is count\n",d);
                            LOCCTR=LOCCTR+d;        ///add the number of characters to location counter
                        }
                        if(col3[0]=='X')            ///if the byte is of type hex
                        {
                            for(i=2;col3[i]!='\0';i++)
                            {
                                continue;
                            }
                            int d=(i-3)/2;          ///add half of the number of characters to location counter
                            //printf("%d is count\n",d);
                            LOCCTR=LOCCTR+d;
                        }
                    }
                    else
                    {
                        printf("No such opcode %s found\n",col2);
                    }

                }
        }
        if(word_count==2)
        {
            sscanf(str,"%s %s",&col2,&col3);
            rewind(fp2);
            while(!feof(fp2))
            {
                fgets(str1,30,fp2);
                sscanf(str1,"%s %d",&opcode,&value);
                if(strcmp(col2,opcode)==0)
                {
                    flag=1;
                    break;
                }
            }
            if(col3[0]=='=')
            {
                lit_flag=1;             ///literal is found, literal flag is set.
            }
            if(lit_flag==1)
            {
                fp4=fopen("literals.txt","a");
                int length=0;
                int no_char;
                fprintf(fp4,"%s\t",col3);
                lit_flag=0;
                for(i=0;col3[i]!='\0';i++)
                {
                    length++;               ///length of the literal
                }
                //fprintf(fp4,"%d\t",length);
                //printf("%d is length",length);
                if(col3[1]=='C')
                {
                    for(i=3;i<length-1;i++)
                    {
                        int e=col3[i];              ///get the ascii equivalent value of character
                        fprintf(fp4,"%X",e);        ///write it to the file in hex
                    }
                fprintf(fp4,"\t");
                no_char=length-4;
                }
                else if(col3[1]=='X')
                {
                    //printf(":sfv");
                    char temp[20];
                    int j=0;
                    for(i=3;i<length-1;i++)         /// write as it is if the byte is of type 'X'
                    {
                        temp[j]=col3[i];
                        j++;
                    }
                    temp[j]='\0';
                    //printf("%s is temp",temp);
                    fprintf(fp4,"%s\t",temp);
                    no_char=(length-4)/2;
                }
                //printf("%d is length\n",no_char);
                fprintf(fp4,"%d\n",no_char);    ///write the number of characters in literal to the literal table
                fclose(fp4);
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
        //fclose(fp4);
        if(word_count==1)
        {
            sscanf(str,"%s",col2);
            if(strcmp(col2,"LTORG")==0)         ///defining literals after LTORG keyword encountered
            {
                LOCCTR=LOCCTR-6;
                int c4;
                fp4=fopen("literals.txt","r");
                FILE *fp5=fopen("literal_table.txt","w");
                while(fgets(str2,30,fp4))
                {
                    //printf("%d is fp4 position\n",ftell(fp4));
                    sscanf(str2,"%s %s %d",&col1,&col2,&c4);
                  fprintf(fp5,"%s\t",col1);         ///writing the contents of first 3 columns from literals as it is
                  fprintf(fp5,"%s\t",col2);
                  fprintf(fp5,"%d\t",c4);
                  fprintf(fp5,"%X\n",LOCCTR);       ///writing the LOCCTR to the literal table
                  LOCCTR=LOCCTR+3;
                  fprintf(fp3,"%X\t",LOCCTR);
                  fprintf(fp3,"\t*\t");
                  fprintf(fp3,"%s\n",col1);

                }
                //fprintf(fp3,"*\t");
                fclose(fp5);
            }
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
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    int l=last_addr-start_addr;
    printf("%X is the length of the program.\n",l);
    fp=fopen("symtab.txt","a");
    fprintf(fp,"2039\tRDREC\n");
    fprintf(fp,"2061\tWRREC\n");
    fclose(fp);
    //fclose(fp5);
}
