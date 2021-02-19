#include "pass1.h"
void pass2()
{
    FILE *fp,*fp1,*fp2,*fp3,*fp4;

    fp=fopen("intermediate.txt","r");
    fp1=fopen("optab.txt","r");
    fp2=fopen("symtab.txt","r");
    fp3=fopen("objectcode.txt","w");
    fp4=fopen("objectprogram.txt","w");
    char str[100];
    int i;
    int flag2=0;
    int c=0;
    int i_count=0;
    int flag1=0;
    char previous='~';
    int count=0;
    int sp;
    int flag=0;
    int word_count;
    int s_addr;
    int l_addr;
    char col1[50],col2[50],col3[50],str1[50],opcode[50],str2[50],label[50],addr[30],str3[50],col4[50],start_addr[50];
    char value[50];
    fgets(str,30,fp);       ///reading input from intermediate file
    sscanf(str,"%d %s %s %s",&s_addr,&col1,&col2,&col3);
    //printf("%d is start",s_addr);
    if(strcmp(col2,"START")==0)
    {
       //printf("H^");
       fprintf(fp4,"H^");
       //printf("%s",col1);
       for(i=0;col1[i]!='\0';i++)
        {
            count++;
        }
        //printf("%d is length\n",count);
        //printf("%s",col1);
        fprintf(fp4,"%s",col1);
        for(i=count;i<6;i++)
        {
            //printf("-");
            fprintf(fp4,"-");
        }
        //printf("^");
        fprintf(fp4,"^");
        //printf("\n");
    }
    while(fgets(str,30,fp))
    {
        //fprintf(fp3,"%s",str);
        word_count=0;
        flag2=0;
        for(i=0;str[i]!='\0';i++)
        {
            if(isspace(str[i]))
            {
                if(!isspace(previous))
                {
                    word_count++;           ///to keep the count of words in each line
                }
                previous=32;
            }
            else{
                previous=str[i];
            }
        }
        //printf("%d is word count\n",word_count);
        if(word_count==4)
        {
            sscanf(str,"%s %s %s %s",&start_addr,&col1,&col2,&col3);
            if((strcmp(col2,"RESW")==0)||(strcmp(col2,"RESB")==0))
            {
                ///if RESW or RESB found, write the record as it is, no need of objectcode
                fprintf(fp3,"%s",str);
            }
            else
            {
                fprintf(fp3,"%s\t",start_addr);
                fprintf(fp3,"%s\t",col1);
                fprintf(fp3,"%s\t",col2);
                fprintf(fp3,"%s\t",col3);
            }

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
                    //printf("%s",value);
                    fprintf(fp3,"%s",value);
                    rewind(fp2);
                    while(!feof(fp2))
                    {
                        fgets(str2,30,fp2);
                        sscanf(str2,"%s %s",&addr,&label);
                        if(strcmp(label,col3)==0)
                        {
                            flag1=1;
                            break;
                        }
                    }
                    if(flag1==1)
                    {
                        //printf("%s",label);
                        //printf("%s\t",addr);
                        fprintf(fp3,"%s\n",addr);
                    }
                    else
                    {
                        printf("error!!");
                    }
                    flag1=0;
                    flag=0;
                }
                else
                {
                    i_count=0;
                    if((strcmp(col2,"WORD")==0))
                    {
                        //printf("%s",col3);
                        for(i=0;col3[i]!='\0';i++)
                        {
                            i_count++;
                        }
                        for(i=i_count;i<6;i++)
                        {
                        // printf("0");
                            fprintf(fp3,"0");
                        }
                    //printf("%s\t",col3);
                        fprintf(fp3,"%s\n",col3);
                    }
                    else if((strcmp(col2,"RESW")==0)||(strcmp(col2,"RESB")==0))
                    {
                        continue;
                    }
                    else if(strcmp(col2,"BYTE")==0)
                    {
                        if(col3[0]=='C')
                        {
                            for(i=2;col3[i]!='\0';i++)
                        {
                            int e=col3[i];
                        //printf("%X",e);
                            c++;
                            if(c>3)
                                break;
                            fprintf(fp3,"%X",e);
                        }
                            //printf("\t");
                            fprintf(fp3,"\n");
                        }
                        if(col3[0]=='X')
                        {
                            //printf("%s",col3);
                            int hex_c=0;
                            int j;
                            char hex[2];
                            for(i=2;col3[i]!='\0';i++)
                            {
                                continue;
                            }
                            //printf("%d",i-2);
                            int ch_c=i-2;
                            i=2;
                            for(j=0;j<ch_c-1;j++)
                            {
                                hex[j]=col3[i++];
                            }
                            for(i=0;i<2;i++)
                            {
                                //printf("%c",hex[i]);
                                fprintf(fp3,"%c",hex[i]);
                            }
                            fprintf(fp3,"\n");

                        }

                    }
                    else
                    {
                    printf("error1");
                    }
                }
        }
        if(word_count==3)
        {
            //fprintf(fp3,"\t");
            flag2=0;
             sscanf(str,"%s %s %s",&start_addr,&col2,&col3);
             fprintf(fp3,"%s\t",start_addr);
            fprintf(fp3,"\t%s\t",col2);
            fprintf(fp3,"%s\t",col3);
            //printf("%s",str1);
            //printf("Hello");
            //printf("%s\t%s\n",opcode,value);
             for(i=0;col3[i]!='\0';i++)
            {
                 //printf("%s",col2);
                if((col3[i]==','))
                {
                    flag2=1;
                    break;
                }

            }
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
                //printf("%s",value);
                fprintf(fp3,"%s",value);
                rewind(fp2);
                while(!feof(fp2))
                {
                    fgets(str2,30,fp2);
                    sscanf(str2,"%s %s",&addr,&label);
                    if(strcmp(label,col3)==0)
                    {
                        flag1=1;
                        break;
                    }
                }
                if(flag1==1)
                {
                    //printf("%s\t",addr);
                    fprintf(fp3,"%s\n",addr);
                }
                else
                {
                    if(flag2==1)
                    {
                        int x_c=0;
                        printf(",X instruction\n");
                        //printf("%s\n",col3);
                        for(i=0;col3[i]!='\0';i++)
                        {
                            x_c++;
                        }
                        printf("%d is x_c\n",x_c);
                        for(i=x_c;i>x_c-3;i--)
                            col3[i]='\0';
                        //printf("%s\n",col3);
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
                            printf("%s",value);
                            flag=0;
                        }
                        rewind(fp2);
                    while(!feof(fp2))
                    {
                        fgets(str2,30,fp2);
                        sscanf(str2,"%s %s",&addr,&label);
                        if(strcmp(label,col3)==0)
                        {
                            flag1=1;
                            break;
                        }
                    }
                    if(flag1==1)
                    {
                        //printf("%s",label);
                        //printf("%s\t",addr);
                        fprintf(fp3,"%s\n",addr);
                    }
                    else
                    {
                        printf("error!!!");
                    }
                    flag1=0;
                    flag=0;
                    }
                    else
                        printf("error1111");
                }
                flag1=0;
                flag=0;
            }
            else
            {
                printf("error");
            }
        }
        if(word_count==2)
        {
            //fprintf(fp3,"\t");
             sscanf(str,"%s %s",&start_addr,&col2);
             fprintf(fp3,"%s\t\t",start_addr);
             fprintf(fp3,"%s\t\t",col2);
            if(strcmp(col2,"END")==0)
            {
                sscanf(str,"%d %s",&l_addr,&col2);
                break;
            }

            //printf("%s",str1);
            //printf("Hello");
            //printf("%s\t%s\n",opcode,value);
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
                //printf("%s",value);
                fprintf(fp3,"%s",value);
                flag=0;
                for(i=0;i<4;i++)
                {
                    //printf("0");
                    fprintf(fp3,"0");
                }
                //printf("\t");
                fprintf(fp3,"\n");
            }
            else
            {
                printf("error");
            }
            }

        }
    }
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    //int cc=0;
    //int i;
    //int len=l_addr-s_addr;
    //printf("%d",s_addr);
    int place=0;
    int n=s_addr;
    while(n!=0)
    {
        n=n/10;
        place++;
    }
    for(i=place;i<6;i++)
    {
        //printf("0");
        fprintf(fp4,"0");
    }
    //printf("%d^",s_addr);
    fprintf(fp4,"%d^",s_addr);
    fp=fopen("length.txt","r");
    int adr_count=0;
    fgets(str,10,fp);
    for(i=0;str[i]!='\0';i++)
    {
        adr_count++;
    }
    for(i=adr_count;i<6;i++)
    {
        //printf("0");
        fprintf(fp4,"0");
    }
    //printf("%s\n",str);
    fprintf(fp4,"%s\n",str);
    //cc=0;
    //printf("%d\n",len);
    fclose(fp4);
}
void objectprogram()
{
    FILE *fp,*fp1,*fp2;
    char str[50],c1[50],c2[50],c3[50],c4[50],c5[50];
    int word_count;
    int i;
    fp=fopen("objectcode.txt","r");
    fp1=fopen("record.txt","w");
    fp2=fopen("objectprogram.txt","a");
    char previous='~';
    while(fgets(str,30,fp))
    {
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
        if(word_count==5)
        {
            sscanf(str,"%s %s %s %s %s",&c1,&c2,&c3,&c4,&c5);
            fprintf(fp1,"%s\t%s\n",c1,c5);
        }
        if(word_count==4)
        {
            sscanf(str,"%s %s %s %s",&c1,&c2,&c3,&c4);
            if((strcmp(c3,"RESW")==0)||(strcmp(c3,"RESB")==0))
                continue;
            else
                fprintf(fp1,"%s\t%s\n",c1,c4);
        }
        if(word_count==3)
        {
            sscanf(str,"%s %s %s",&c1,&c2,&c3);
            fprintf(fp1,"%s\t%s\n",c1,c3);
        }
    }
    fclose(fp);
    fclose(fp1);
    fp=fopen("record.txt","r");
    FILE *fp4=fopen("objectprogram.txt","a");
    char a[50];
    int j,k,size;
    //int start_addr;
    while(fgets(str,30,fp))
    {
        int count=0;
        size=0;
        //printf("\n");
        //printf("T");
        fprintf(fp4,"T^");
        for(k=0;a[k]!='\0';k++)
        {
            a[k]='\0';
        }
        sscanf(str,"%s %s",c1,c2);
        strcat(a,c2);
        for(i=0;c1[i]!='\0';i++)
        {
            count++;
        }
        //printf("%d\n",count);
        for(i=count;i<6;i++)
        {
            //printf("0");
            fprintf(fp4,"0");
        }
        //printf("%s^",c1);
        fprintf(fp4,"%s^",c1);
        //rewind(fp);
        for(i=1;i<10;i++)
        {
            if(fgets(str,30,fp))
            {
                sscanf(str,"%s %s",c1,c2);
            strcat(a,"^");
            strcat(a,c2);
            }
            else
                break;
        }
        for(j=0;a[j]!='\0';j++)
        {
            if(a[j]!='^')
                size++;
        }
        //printf("\n%d is size",size);
        int size_field=size/2;
        //printf("%X^",size_field);
        fprintf(fp4,"%X^",size_field);
        for(i=0;a[i]!='\0';i++)
        {
            //printf("%c",a[i]);
            fprintf(fp4,"%c",a[i]);
        }
        //printf("\n");
        fprintf(fp4,"\n");
    }
    fclose(fp);
    fp=fopen("objectcode.txt","r");
    fgets(str,30,fp);
    int c=0;
    sscanf(str,"%s %s",&c1,&c2);
    //printf("E^");
    fprintf(fp4,"E^");
    for(i=0;c1[i]!='\0';i++)
    {
        c++;
    }
    for(i=c;i<6;i++)
    {
        //printf("0");
        fprintf(fp4,"0");
    }
    //printf("%s\n",c1);
    fprintf(fp4,"%s\n",c1);
    fclose(fp);
}
