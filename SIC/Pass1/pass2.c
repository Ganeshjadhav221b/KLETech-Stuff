#include"pass1.h"
#include<string.h>
void second()
{

    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    char str1[100],str2[100],str3[100],str4[100],str5[100];
    char str[100];
    char opcode[100],label[100],operand[100],objcode[100],opc[100],ope[100],address[100];
    int temp1,temp2,temp3,temp4;
    int i,j,k;
    int spaces=0;
    int wordCount = 0;
    int LOCCTR = 0;
    int startAddr = 0;
    int len=0;
    int a,b,c=0;
    char cvalue[100];
    char evalue[100];

    fp1 = fopen("intermediate.txt","r");
    fp2 = fopen("optab.txt","r");
    fp3 = fopen("symtab.txt","r");
    fp4 = fopen("objectCode.txt","w");
    fp5 = fopen("objectProgram.txt","w");


    if(fp1 == NULL )
        printf("ERROR opening input file!");
    if(fp2 == NULL )
        printf("ERROR opening optab file!");
    if(fp3 == NULL )
        printf("ERROR opening symtab file!");
    if(fp4 == NULL )
        printf("ERROR opening objcode file!");
    if(fp5 == NULL )
        printf("ERROR opening objprogram file!");

    fgets(str,60,fp1);
    sscanf(str,"%s%s%s%s",address,label,opcode,operand);
    fprintf(fp4,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        //printf("\nStarting address is %X\n",LOCCTR = atoi(operand));
        fprintf(fp5,"H^");
        for (i=0; label[i]!='\0';i++)
            len++;
        fprintf(fp5,"%s",label);
        for(i = len; i<6;i++)
            fprintf(fp5,"-");
        a=LOCCTR;
        len=0;
        while(a!=0)
        {
            a=a/10;
            len++;
        }
        for(i = len; i<5;i++)
            fprintf(fp5,"0");
            fprintf(fp5,"%X",LOCCTR);
            fprintf(fp5,"\n");
    }

    while(fgets(str,60,fp1)!=NULL)
    {
        wordCount = findWords(str);
        if (wordCount == 4)
        {
            rewind(fp2);
            rewind(fp3);
            sscanf(str,"%s%s%s%s",address,label,opcode,operand);
                if(strcmp(opcode,"BYTE")==0)
                {
                    if(operand[0]=='C')
                    {
                            fprintf(fp4,"%s\t%s\t%s\t%s\t",address,label,opcode,operand);
                            for(i=2,c=0;operand[i]!='\0'&&c<3;i++,c++)
                            {
                                fprintf(fp4,"%X",operand[i]);
                            }
                            fprintf(fp4,"\n");
                            continue;

                        }
                        if(operand[0]=='X')
                        {
                            fprintf(fp4,"%s\t%s\t%s\t%s\t",address,label,opcode,operand);
                            for(i=2;i,i<strlen(operand)-1;i++)
                                fprintf(fp4,"%c",operand[i]);
                            fprintf(fp4,"\n");
                            goto SKIP;
                        }

                }
                if(strcmp(opcode,"RESB")==0)
                {
                    strcpy(cvalue,"");
                    strcpy(ope,"");
                    goto PRINT;
                }
                if(strcmp(opcode,"RESW")==0)
                {
                    strcpy(cvalue,"");
                    strcpy(ope,"");
                    goto PRINT;
                }

            while( fgets (str1, 60, fp2)!=NULL )
            {
                sscanf(str1,"%s%s",opc,cvalue);
                if(strcmp(opcode,"WORD")==0)
                {
                    strcpy(ope,operand);
                    strcpy(cvalue,"00000");
                    goto PRINT;
                }

                if(strcmp(opc,opcode)==0)
                {
                    break;
                }
            }

            while( fgets (str3, 60, fp3)!=NULL )
            {
                sscanf(str3,"%s%s",ope,evalue);
                if(strcmp(evalue,operand)==0)
                {
                    break;
                }
            }
            PRINT: fprintf(fp4,"%s\t%s\t%s\t%s\t%s%s\n",address,label,opcode,operand,cvalue,ope);
            SKIP: ;
        }
        if (wordCount == 3)
        {
            sscanf(str,"%s%s%s%s",address,opcode,operand);
            rewind(fp2);
            rewind(fp3);
            while( fgets (str1, 60, fp2)!=NULL )
            {
                sscanf(str1,"%s%s",opc,cvalue);
                if(strcmp(opc,opcode)==0)
                {
                    break;
                }
            }

            while( fgets (str3, 60, fp3)!=NULL )
            {
                sscanf(str3,"%s%s",ope,evalue);
                if(strcmp(evalue,operand)==0)
                {
                    break;
                }
            }
            fprintf(fp4,"%s\t\t%s\t%s\t%s%s\n",address,opcode,operand,cvalue,ope);
        }
        if (wordCount == 2)
        {
            sscanf(str,"%s%s%s",address,opcode);
            rewind(fp2);
            rewind(fp3);
            while( fgets (str1, 60, fp2)!=NULL )
            {
                sscanf(str1,"%s%s",opc,cvalue);
                if(strcmp(opc,opcode)==0)
                {
                    strcpy(ope,"0000");
                    break;
                }
            }
            if(strcmp(opcode,"END")==0)
            {
                strcpy(cvalue,"");
                strcpy(ope,"");
            }
            fprintf(fp4,"%s\t\t%s\t\t%s%s\n",address,opcode,cvalue,ope);
        }
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    printf("END of Pass2- SIC!");

}

/*
void objectProgram()
{
    FILE *fp,*fp1,*fp2;
    char str[50],c1[50],c2[50],c3[50],c4[50],c5[50];
    int word_count;
    int i;
    fp=fopen("objectCode.txt","r");
    fp1=fopen("record.txt","w");
    fp2=fopen("objectProgram.txt","a");
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
    FILE *fp4=fopen("objectProgram.txt","a");
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
    fp=fopen("objectCode.txt","r");
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

*/

void objectProgram()
{
    FILE *fp,*fp1,*fp2;
    char str[50],c1[50],c2[50],c3[50],c4[50],c5[50];
    int word_count;
    int i;
    fp=fopen("objectCode.txt","r");
    fp1=fopen("record.txt","w");
  //  fp2=fopen("objectProgram.txt","a");
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
    FILE *fp4=fopen("objectProgram.txt","a");
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
    fp=fopen("objectCode.txt","r");
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

