#include "sic.h"
void pass2(int prog_len)
{
    FILE *fp,*fp1,*fp2,*fp3,*fp4,*fp5,*fp6;
    fp=fopen("intermediate.txt","r");
    fp1=fopen("optab.txt","r");
    fp2=fopen("symtab.txt","r");
    fp3=fopen("objectcode.txt","w");
    fp4=fopen("objectprogram.txt","w");
    fp5=fopen("literal_table.txt","r");
    char str[50],col1[50],col2[50],col3[50],start_addr[50],value[20],opcode[20],label[20],str1[20],str2[20],lcol1[20],lcol2[20],addr1[20];
    char str3[50],bname[10],str4[40],st_addr[10];
    int s_addr,block,i,count=0,wcount,flag,flag1,sblock,llen,lblock,bno,blen,bstart,laddr,addr,flag2;
    fgets(str,30,fp);       ///reading input from intermediate file
    sscanf(str,"%X %d %s %s %s",&s_addr,&block,col1,col2,st_addr);
    //printf("%d\n",s_addr);
     if(strcmp(col2,"START")==0)
    {
      /* fprintf(fp4,"H^");       ///initialising header record
       //printf("%s",col1);
       for(i=0;col1[i]!='\0';i++)       ///count the number of letters in name of the program
        {
            count++;
        }
        fprintf(fp4,"%s",col1);
        for(i=count;i<6;i++)        ///if count<6 append that much number of -
        {
            fprintf(fp4,"-");
        }
        fprintf(fp4,"^");*/
    }
    while(fgets(str,50,fp))
    {
        //printf("H^");
        flag=0,flag1=0,flag2=0;
        wcount=word_count(str);
        //printf("%d is word count\n",wcount);
        if(wcount==5)
        {
            //printf("H^");
            sscanf(str,"%s %d %s %s %s",&start_addr,&block,&col1,&col2,&col3);
            if((strcmp(col2,"RESW")==0)||(strcmp(col2,"RESB")==0)||(strcmp(col2,"EQU")==0))
            {
                 fprintf(fp3,"%s",str);
                continue;
            }
            else
            {
                fprintf(fp3,"%s\t",start_addr);
                fprintf(fp3,"%d\t",block);
                fprintf(fp3,"%s\t",col1);
                fprintf(fp3,"%s\t",col2);
                fprintf(fp3,"%s\t",col3);
                rewind(fp1);
                while(!feof(fp1))           ///search optab for opcode
                {
                    fgets(str1,30,fp1);
                    sscanf(str1,"%s %s",&opcode,&value);
                    if(strcmp(col2,opcode)==0)
                    {
                        flag=1;
                        break;
                    }
                }
                for(i=0;col3[i]!='\0';i++)      ///check whether ,X instruction exists
                {
                    //printf("%s",col2);
                    if((col3[i]==','))
                    {
                        flag2=1;
                        break;
                    }

                }
                if(flag==1)                     ///successful search in optab
                {
                    fprintf(fp3,"%s",value);
                    ///if opcode is found in optab, write the opcode value from optab to the objectcode file as first 1 byte
                    rewind(fp2);
                    while(!feof(fp2))
                    {
                        fgets(str2,30,fp2);
                        sscanf(str2,"%X %d %s",&addr,&sblock,&label);      ///search operands in symtab
                        if(strcmp(label,col3)==0)
                        {
                            flag1=1;
                            break;
                        }
                    }

                    rewind(fp5);
                    while(!feof(fp5))                                   ///search operands in literal_table
                    {
                        fgets(str3,40,fp5);
                        sscanf(str3,"%s %s %d %X %d",&lcol1,&lcol2,&llen,&laddr,&lblock);
                        if(strcmp(lcol1,col3)==0)
                        {
                            flag1=2;
                            break;
                        }
                    }
                    if(flag1==1)                    ///found in symtab
                    {
                        if(sblock==0)
                        {
                            fprintf(fp3,"%X\n",addr);

                        }
                        else if(sblock==1)
                        {
                            fp6=fopen("blocks.txt","r");        ///writing object code for CDATA instructions
                            while(!feof(fp6))
                            {
                                fgets(str4,40,fp6);
                                sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                if(bno==0)
                                {
                                    addr=addr+blen;           ///adding the length of previous block
                                    break;
                                }
                            }
                            fclose(fp6);
                            fprintf(fp3,"%X\n",addr);
                        }
                        else if(sblock==2)
                        {
                            fp6=fopen("blocks.txt","r");
                            while(!feof(fp6))
                            {
                                fgets(str4,40,fp6);
                                sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                if(bno==0)
                                {
                                    addr=addr+blen;           ///adding the length of default block
                                    continue;
                                }
                                if(bno==1)
                                {
                                    addr=addr+blen;           ///adding the length of CDATA block
                                    break;
                                }
                            }
                            fclose(fp6);
                            fprintf(fp3,"%X\n",addr);
                        }
                    }
                    else if(flag1==2)                   ///when found in literal table
                    {
                        if(lblock==0)
                        {
                            fprintf(fp3,"%X\n",laddr);
                        }
                        else if(lblock==1)
                        {
                            fp6=fopen("blocks.txt","r");        ///writing object code for CDATA instructions
                            while(!feof(fp6))
                            {
                                fgets(str4,40,fp6);
                                sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                if(bno==0)
                                {
                                    laddr=laddr+blen;           ///adding the length of previous block
                                    break;
                                }
                            }
                            fclose(fp6);
                            fprintf(fp3,"%X\n",laddr);
                        }
                        else if(lblock==2)                   ///writing object code for CBLKS instructions
                        {
                            fp6=fopen("blocks.txt","r");
                            while(!feof(fp6))
                            {
                                fgets(str4,40,fp6);
                                sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                if(bno==0)
                                {
                                    laddr=laddr+blen;           ///adding the length of default block
                                    continue;
                                }
                                if(bno==1)
                                {
                                    laddr=laddr+blen;           ///adding the length of CDATA block
                                    break;
                                }
                            }
                            fclose(fp6);
                            fprintf(fp3,"%X\n",laddr);
                        }
                    }
                    else
                    {
                        if(flag2==1)                            ///,X instruction
                        {
                            int x_c=0;
                            for(i=0;col3[i]!='\0';i++)
                            {
                                x_c++;
                            }
                            //printf("%d is x_c\n",x_c);
                            for(i=x_c;i>x_c-3;i--)
                                col3[i]='\0';
                            ///if ,X is the instruction fetch only the operand value
                            rewind(fp2);
                            while(!feof(fp2))
                            {
                                fgets(str2,30,fp2);
                                sscanf(str2,"%X %d %s",&addr,&block,&label);
                                ///search the operand in symtab
                                if(strcmp(label,col3)==0)
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                            if(flag1==1)
                            {
                                if(sblock==0)
                                {
                                    ///if found add 8000 to the operand value that is equivalent to adding 1 in X's field in the format.
                                    addr=addr+32768;           ///hex value of 8000 is 32768
                                    fprintf(fp3,"%X\n",addr);
                                }
                                else if(sblock==1)
                                {
                                    fp6=fopen("blocks.txt","r");        ///writing object code for CDATA instructions
                                    while(!feof(fp6))
                                    {
                                        fgets(str4,40,fp6);
                                        sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                        if(bno==0)
                                        {
                                            addr=addr+blen;           ///adding the length of previous block
                                            break;
                                        }
                                    }
                                    fclose(fp6);
                                    addr=addr+32768;
                                    fprintf(fp3,"%X\n",addr);
                                }
                                else if(sblock==2)
                                {
                                    fp6=fopen("blocks.txt","r");
                                    while(!feof(fp6))
                                    {
                                        fgets(str4,40,fp6);
                                        sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                        if(bno==0)
                                        {
                                            addr=addr+blen;           ///adding the length of default block
                                            continue;
                                        }
                                        if(bno==1)
                                        {
                                            addr=addr+blen;           ///adding the length of CDATA block
                                            break;
                                        }
                                    }
                                    fclose(fp6);
                                    addr=addr+32768;
                                    fprintf(fp3,"%X\n",addr);
                                }
                            }
                            else
                            {
                                printf("error\n");
                            }
                            flag1=0;
                            flag=0;
                        }
                        else
                            printf("error!!");
                    }
                }
            }
        }
        if(wcount==4)
        {
            sscanf(str,"%s %d %s %s",&start_addr,&block,&col2,&col3);
            if(strcmp(col2,"USE")==0)
            {
                fprintf(fp3,"%s",str);
                continue;
            }
            else
            {
                fprintf(fp3,"%s\t",start_addr);
                fprintf(fp3,"%d\t",block);
                //fprintf(fp3,"%s\t",col1);
                fprintf(fp3,"\t%s\t",col2);
                fprintf(fp3,"%s\t",col3);
                rewind(fp1);
                while(!feof(fp1))           ///search optab for opcode
                {
                    fgets(str1,30,fp1);
                    sscanf(str1,"%s %s",&opcode,&value);
                    if(strcmp(col2,opcode)==0)
                    {
                        flag=1;
                        break;
                    }
                }
                //printf("%d is flag for optab search\n",flag);
                for(i=0;col3[i]!='\0';i++)      ///check whether ,X instruction exists
                {
                    //printf("%s",col2);
                    if((col3[i]==','))
                    {
                        flag2=1;
                        break;
                    }

                }
                if(flag==1)
                {
                    fprintf(fp3,"%s",value);
                    ///if opcode is found in optab, write the opcode value from optab to the objectcode file as first 1 byte
                    rewind(fp2);
                    while(!feof(fp2))
                    {
                        fgets(str2,30,fp2);
                        sscanf(str2,"%X %d %s",&addr,&sblock,&label);      ///search operands in symtab
                        if(strcmp(label,col3)==0)
                        {
                            flag1=1;
                            break;
                        }
                    }
                    rewind(fp5);
                    while(!feof(fp5))                                   ///search operands in literal_table
                    {
                        fgets(str3,40,fp5);
                        sscanf(str3,"%s %s %d %X %d",&lcol1,&lcol2,&llen,&laddr,&lblock);
                        if(strcmp(lcol1,col3)==0)
                        {
                            flag1=2;
                            break;
                        }
                    }
                    if(flag1==1)
                    {
                        if(sblock==0)
                        {
                            fprintf(fp3,"%X\n",addr);
                        }
                        else if(sblock==1)
                        {
                            fp6=fopen("blocks.txt","r");        ///writing object code for CDATA instructions
                            while(!feof(fp6))
                            {
                                fgets(str4,40,fp6);
                                sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                if(bno==0)
                                {
                                    addr=addr+blen;           ///adding the length of previous block
                                    break;
                                }
                            }
                            fclose(fp6);
                            fprintf(fp3,"%X\n",addr);
                        }
                        else if(sblock==2)
                        {
                            fp6=fopen("blocks.txt","r");
                            while(!feof(fp6))
                            {
                                fgets(str4,40,fp6);
                                sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                if(bno==0)
                                {
                                    addr=addr+blen;           ///adding the length of default block
                                    continue;
                                }
                                if(bno==1)
                                {
                                    addr=addr+blen;           ///adding the length of CDATA block
                                    break;
                                }
                            }
                            fclose(fp6);
                            fprintf(fp3,"%X\n",addr);
                        }
                    }
                    else if(flag1==2)
                    {
                        if(lblock==0)
                        {
                            fprintf(fp3,"%X\n",laddr);
                        }
                        else if(lblock==1)
                        {
                            fp6=fopen("blocks.txt","r");        ///writing object code for CDATA instructions
                            while(!feof(fp6))
                            {
                                fgets(str4,40,fp6);
                                sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                if(bno==0)
                                {
                                    laddr=laddr+blen;           ///adding the length of previous block
                                    break;
                                }
                            }
                            fclose(fp6);
                            fprintf(fp3,"%X\n",laddr);
                        }
                        else if(lblock==2)                   ///writing object code for CBLKS instructions
                        {
                            fp6=fopen("blocks.txt","r");
                            while(!feof(fp6))
                            {
                                fgets(str4,40,fp6);
                                sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                if(bno==0)
                                {
                                    laddr=laddr+blen;           ///adding the length of default block
                                    continue;
                                }
                                if(bno==1)
                                {
                                    laddr=laddr+blen;           ///adding the length of CDATA block
                                    break;
                                }
                            }
                            fclose(fp6);
                            fprintf(fp3,"%X\n",laddr);
                        }
                    }
                    else
                    {
                        if(flag2==1)                            ///,X instruction
                        {
                            int x_c=0;
                            for(i=0;col3[i]!='\0';i++)
                            {
                                x_c++;
                            }
                            //printf("%d is x_c\n",x_c);
                            for(i=x_c;i>x_c-3;i--)
                                col3[i]='\0';
                            ///if ,X is the instruction fetch only the operand value
                            rewind(fp2);
                            while(!feof(fp2))
                            {
                                fgets(str2,30,fp2);
                                sscanf(str2,"%X %d %s",&addr,&block,&label);
                                ///search the operand in symtab
                                if(strcmp(label,col3)==0)
                                {
                                    flag1=1;
                                    break;
                                }
                            }
                            if(flag1==1)
                            {
                                if(sblock==0)
                                {
                                    ///if found add 8000 to the operand value that is equivalent to adding 1 in X's field in the format.
                                    addr=addr+32768;           ///hex value of 8000 is 32768
                                    fprintf(fp3,"%X\n",addr);
                                }
                                else if(sblock==1)
                                {
                                    fp6=fopen("blocks.txt","r");        ///writing object code for CDATA instructions
                                    while(!feof(fp6))
                                    {
                                        fgets(str4,40,fp6);
                                        sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                        if(bno==0)
                                        {
                                            addr=addr+blen;           ///adding the length of previous block
                                            break;
                                        }
                                    }
                                    fclose(fp6);
                                    addr=addr+0x8000;
                                    fprintf(fp3,"%X\n",addr);
                                }
                                else if(sblock==2)
                                {
                                    fp6=fopen("blocks.txt","r");
                                    while(!feof(fp6))
                                    {
                                        fgets(str4,40,fp6);
                                        sscanf(str4,"%s %d %X %X",&bname,&bno,&bstart,&blen);
                                        if(bno==0)
                                        {
                                            addr=addr+blen;           ///adding the length of default block
                                            continue;
                                        }
                                        if(bno==1)
                                        {
                                            addr=addr+blen;           ///adding the length of CDATA block
                                            break;
                                        }
                                    }
                                    fclose(fp6);
                                    addr=addr+32768;
                                    fprintf(fp3,"%X\n",addr);
                                }
                            }
                            else
                            {
                                printf("error\n");
                            }
                            flag1=0;
                            flag=0;
                        }
                    }
                }
                else                    ///not found in optab
                {
                    ///for the instruction that define literals.
                    rewind(fp5);
                    while(!feof(fp5))
                    {
                        fgets(str3,40,fp5);
                        sscanf(str3,"%s %s %d %X %d",&lcol1,&lcol2,&llen,&laddr,&lblock);
                        if(strcmp(lcol1,col3)==0)
                        {
                            break;
                        }
                    }
                    //printf("%s\n",lcol2);
                    fprintf(fp3,"%s\n",lcol2);
                }
            }
        }
        if(wcount==3)
        {
            sscanf(str,"%s %d %s ",&start_addr,&block,&col2);
            fprintf(fp3,"%s\t",start_addr);
            fprintf(fp3,"%d\t\t",block);
            fprintf(fp3,"%s\t\t",col2);
            if(strcmp(col2,"END")==0)
            {
                //sscanf(str,"%d %s",&l_addr,&col2);
                break;
            }
            else if((strcmp(col2,"USE")==0)||(strcmp(col2,"LTORG")==0))
            {
                fprintf(fp3,"\n");
                continue;
            }
            else
            {
                 rewind(fp1);
                while(!feof(fp1))
                {
                    fgets(str1,30,fp1);
                    sscanf(str1,"%s %s",&opcode,&value);
                    if(strcmp(col2,opcode)==0)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                {
                    fprintf(fp3,"%s",value);
                    flag=0;
                    for(i=0;i<4;i++)            ///1 byte will be occupied  by opcode value
                    {
                        fprintf(fp3,"0");
                    }
                    fprintf(fp3,"\n");
                }
                else
                {
                    //printf("%s\n",str);
                    printf("error");
                }
            }
        }
    }
    int c=0;
    for(i=0;st_addr[i]!='\0';i++)
    {
        c++;
    }
    //printf("%d is c\n",c);
    for(i=c;i<6;i++)
    {
        fprintf(fp4,"0");
    }
    fprintf(fp4,"%s^",st_addr);
    fprintf(fp4,"%X^",prog_len);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
}
