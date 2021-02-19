#include "sic.h"

int pass1()
{
    FILE *fp,*fp1,*fp2,*fp3,*fp4;
    //fp=fopen("input2.txt","r");
    fp=fopen("input.txt","r");
    fp1=fopen("symtab.txt","w");
    fp2=fopen("optab.txt","r");
    fp3=fopen("intermediate.txt","w");
    fp4=fopen("literals.txt","w");
    char str[100],col1[100],col2[100],col3[100],opcode[100],str1[100],str2[100],temp1[50],temp2[50],label[50];
    char previous='~',operand;
    int LOCCTR1,LOCCTR2=1000,useflag,LOCCTR3=1000,LOCCTR4;
    int block=0,block1,length,length1,length2,length3;
    int x,LOCCTR,start_addr,last_addr,word_count,i,value,op,lit_flag=0,printflag,numflag,num,pos,fpos,numflag1,numflag2;
    fgets(str,30,fp);
    sscanf(str,"%s %s %d",col1,col2,&x);
    if(strcmp(col2,"START")==0)
    {
        printf("Starting address is %X\n",LOCCTR=x);
        start_addr=LOCCTR;
        fprintf(fp3,"%X\t%d\t",LOCCTR,block);
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
        //printf("%s %d\n",str,block);
        word_count=0;
        int flag=0;
        int flag1=0,flag2=0,value1,value2,result;
        numflag1=0;
        numflag2=0;
        pos=0;
        printflag=equsearch(str);
        useflag=usesearch(str);
        if(printflag==0)
        {
            if(useflag==0)
            {
                fprintf(fp3,"%X\t%d\t",LOCCTR,block);
                fprintf(fp3,"%s",str);
            }
        }
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
        //printf("%d is word_count\n",word_count);
        if(word_count==3)
        {
            sscanf(str,"%s %s %s",&col1,&col2,&col3);
            if(printflag==0)
            {
                fprintf(fp1,"%X\t%d\t%s\n",LOCCTR,block,col1);
            }
            rewind(fp2);
            while(!feof(fp2))
            {
                fgets(str1,30,fp2);
                sscanf(str1,"%s %d",&opcode,&value);
                if(strcmp(opcode,col2)==0)
                {
                    flag=1;
                    break;
                }
            }
            //printf("%c is col3[0]\n",col3[0]);
            if(col3[0]=='=')
            {
                lit_flag=1;                         ///literal is found, literal flag is set.
            }
            if(lit_flag==1)
            {
                int length=0;
                int no_char;
                fprintf(fp4,"%s\t",col3);
                lit_flag=0;
                for(i=0;col3[i]!='\0';i++)
                {
                    length++;                       ///length of the literal
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
                    else if(strcmp(col2,"EQU")==0)      ///if operand is EQU
                    {
                        //printf("helo\n");
                        //LOCCTR=LOCCTR;
                        int j;
                        if(strcmp(col3,"*")==0)         ///if *, write the current value of LOCCTR to intermediate file
                        {
                            fprintf(fp3,"%X\t%d\t",LOCCTR,block);
                            fprintf(fp3,"%s",str);
                            fprintf(fp1,"%X\t%d\t%s\n",LOCCTR,block,col1);       ///entry to symtab
                        }
                        else
                        {
                            numflag=isnum(col3);
                            if(numflag==1)
                            {
                                sscanf(col3,"%d",&num);         ///if col3 has only numbers
                                fprintf(fp3,"%X\t%d\t",num,block);        ///write its hex value as LOCCTR
                                fprintf(fp3,"%s",str);
                                fprintf(fp1,"%X\t%d\t%s\n",num,block,col1);   ///make an entry to symtab
                            }
                            else
                            {
                                for(i=0;i<50;i++)
                                {
                                    temp1[i]='\0';
                                    temp2[i]='\0';
                                }
                                pos=ischar(col3);
                                //printf("%s is col3\n",col3);
                                operand=col3[pos];
                                //printf("%c is operand\n",col3[pos]);
                                for(i=0;i<pos;i++)
                                {
                                    temp1[i]=col3[i];
                                }
                                j=0;
                                for(i=pos+1;col3[i]!='\0';i++)
                                {
                                    temp2[j]=col3[i];
                                    j++;
                                }
                                //printf("%s is temp1\n",temp1);
                                numflag1=isnum(temp1);
                                numflag2=isnum(temp2);
                                fpos=ftell(fp1);
                                fclose(fp1);
                                fp1=fopen("symtab.txt","r");
                                while(!feof(fp1))
                                {
                                    fgets(str1,30,fp1);
                                     //printf("%s is str\n",str);
                                    sscanf(str1,"%X %d %s",&value,&block1,&label);      ///search symtab for both the operands of expression
                                    //printf("%s is label\n",label);
                                    if(strcmp(temp1,label)==0)
                                    {
                                        if(flag1==1)
                                            continue;
                                        else
                                        {
                                            flag1=1;
                                            value1=value;           ///fetch the value and store in value1 for 1st operand
                                           //printf("%X is value1\n",value);
                                        }
                                    }
                                    if(strcmp(temp2,label)==0)
                                    {
                                        if(flag2==1)
                                        {
                                           // LOCCTR=LOCCTR;
                                            continue;
                                        }
                                        else
                                        {
                                            flag2=1;
                                            value2=value;           ///fetch the value and store in value2 for 2nd operand
                                           //printf("%X is value2\n",value);
                                        }
                                    }
                                    if((flag1==1&&flag2==1))
                                    {
                                        break;
                                    }
                                }
                                if(flag1==1&&flag2==1)              ///if both the operands are symbols
                                {
                                    result=getresult(operand,value1,value2);
                                }
                                if(numflag1==1&&flag2==1)           ///if one of the operand is symbol and the other is numerical constant
                                {
                                    sscanf(temp1,"%d",&value1);
                                    result=getresult(operand,value1,value2);
                                }
                                if(flag1==1&&numflag2==1)           ///if one of the operand is symbol and the other is numerical constant
                                {
                                    sscanf(temp2,"%d",&value2);
                                    result=getresult(operand,value1,value2);
                                }
                                fprintf(fp3,"%X\t%d\t",result,block);        ///write the result of expression as LOCCTR
                                fprintf(fp3,"%s",str);
                                //printf("%d is symtab file pointer position\n",ftell(fp1));
                                fclose(fp1);
                                fp1=fopen("symtab.txt","a");
                                fseek(fp1,fpos,SEEK_SET);           ///move the symtab file pointer to its initial position
                                fprintf(fp1,"%X\t%d\t%s\n",result,block,col1);    ///make an entry to symtab
                                //printf("%d is symtab file pointer position\n",ftell(fp1));
                            }
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
                    if(strcmp(col2,"USE")==0)
                    {
                        if(strcmp(col3,"CDATA")==0)         ///encountering CDATA block
                        {
                            LOCCTR1=LOCCTR;
                            LOCCTR=LOCCTR2;
                            block=1;
                            fprintf(fp3,"%X\t%d\t",LOCCTR,block);
                            fprintf(fp3,"%s",str);
                        }
                        if(strcmp(col3,"CBLKS")==0)             ///encountering CBLKS block
                        {
                            LOCCTR2=LOCCTR;
                            LOCCTR=LOCCTR3;
                            block=2;
                            fprintf(fp3,"%X\t\%d\t",LOCCTR,block);
                            fprintf(fp3,"%s",str);
                        }
                    }
                else
                {
                   printf("%s not found\n",col2);
                }
            }
        }
        if(word_count==1)
        {
            sscanf(str,"%s",col2);
            if(strcmp(col2,"LTORG")==0)         ///defining literals after LTORG keyword encountered
            {
                //LOCCTR=LOCCTR-3;
                ///no need for this input file as LTORG is at the starting address of the new block
                int length;
                fp4=fopen("literals.txt","r");
                FILE *fp5=fopen("literal_table.txt","w");
                while(fgets(str2,30,fp4))
                {
                    //printf("%d is fp4 position\n",ftell(fp4));
                    sscanf(str2,"%s %s %d",&col1,&col2,&length);
                    fprintf(fp5,"%s\t",col1);         ///writing the contents of first 3 columns from literals as it is
                    fprintf(fp5,"%s\t",col2);
                    fprintf(fp5,"%d\t",length);
                    fprintf(fp5,"%X\t",LOCCTR);       ///writing the LOCCTR to the literal table
                    fprintf(fp5,"%d\n",block);
                    fprintf(fp3,"%X\t%d\t",LOCCTR,block);
                    LOCCTR=LOCCTR+length;
                    fprintf(fp3,"*\t\t");
                    fprintf(fp3,"%s\n",col1);
                }
                fclose(fp5);
            }
            else if(strcmp(col2,"USE")==0)       ///encountering default block
            {
                LOCCTR4=LOCCTR;
                LOCCTR=LOCCTR1;
                block=0;
                fprintf(fp3,"%X\t%d\t",LOCCTR,block);
                fprintf(fp3,"%s",str);
            }
            else if(strcmp(col2,"END")==0)
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
    fp=fopen("symtab.txt","a");
    fprintf(fp,"2039\t0\tRDREC\n");
    fprintf(fp,"2061\t0\tWRREC\n");
    fclose(fp);
    fp=fopen("blocks.txt","w");
    length1=LOCCTR1-start_addr;         ///calculating length of default block
    length2=LOCCTR-start_addr;          ///calculating length of CDATA block
    length3=LOCCTR4-start_addr;         ///calculating length of CBLKS block
    length=length1+length2+length3;
    //printf("%X is the length of the program\n",length);
    fprintf(fp,"DEFAULT\t0\t%X\t%X\n",start_addr,length1);
    fprintf(fp,"CDATA\t1\t%X\t%X\n",LOCCTR1,length2);
    fprintf(fp,"CBLOCK\t2\t%X\t%X\n",LOCCTR,length3);
    fclose(fp);
    return length;
}
