#include <stdio.h>
#include <stdlib.h>

int word_count(char str[])
{
    int i,count=0;
    char previous='~';
    for(i=0;str[i]!='\0';i++)
    {
        if(isspace(str[i]) && previous=='~')
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


void process(FILE *fp1,FILE *fp2,FILE *fp3,FILE *fp4,FILE *fp5)
{
    char str[50], str1[50], str2[50];
    char label[50], opcode[50], operand[50];

    while(fgets(str,50,fp1))
    {
        if(str[0] == '.')
            continue;
        if(strcmp(str,"END")==0)
            break;

        int count = word_count(str);
        //printf("%d\t%s",count,str);
        if (count == 3)
        {
            sscanf(str,"%s %s %s", label, opcode, operand);
            printf("%s\t%s\t%\t%s\n", label, opcode, operand);
            if(strcmp(opcode,"MACRO")==0)
            {
                //printf("%s and %d into namtab\n",label,ftell(fp4));
                fprintf(fp2,"%s\t",label);              //Into the namtab
                fprintf(fp2,"%d\t",ftell(fp4));
                fprintf(fp4, "%s\t%s\t&?1\n", label, opcode);
                int j=0;

                 int i;
                printf("%s is the argument\n", operand);

                while(fgets(str,50,fp1))                //Definition
                {
                    if(str[0] == '.')
                        continue;
                    sscanf(str,"%s %s ",  opcode, operand);
                    //printf("%s",str);
                    if (strcmp(opcode,"MEND") == 0)
                    {
                        //printf("<-%s-> into deftab\n",str);
                        fprintf(fp4, "%s",str);
                        //printf(" %d into namtab\n",ftell(fp4));
                        fprintf(fp2,"%d\n",ftell(fp4));
                        break;
                    }
                    else
                    {
                        //printf("<-%s-> into deftab\n",str);
                        if(operand[1] != '&')
                            fprintf(fp4, "%s\t%s\n",opcode,operand);
                        else
                        {
                            int i=0;
                            fprintf(fp4,"%s\t",opcode);
                            for(i=0;operand[i]!='&';i++)
                                fprintf(fp4,"%c",operand[i]);
                            for(i=0;operand[i]!='>';i++)
                                continue;
                            fprintf(fp4,"?1");
                            i++;
                            for(;operand[i]!='\0';i++)
                                fprintf(fp4,"%c",operand[i]);
                            fprintf(fp4,"\n");

                        }
                    }
                }
            }
            //
            else
            {
                //printf("%s Into the output file:-",str);
                fprintf(fp5,"%s",str);              //Into the output file
            }
        }
        else if (count == 2)                //maybe definition or maybe invocation
        {
            sscanf(str,"%s %s",label,opcode);
            printf("\t%s\t%s\n",label,opcode);
            if(strcmp(opcode,"MACRO")==0)       //For definition
            {
                //printf("%s and %d into namtab\n",label,ftell(fp4));
                fprintf(fp2,"%s\t",label);              //Into the namtab
                fprintf(fp2,"%d\t",ftell(fp4));
                //
                fprintf(fp4, "%s",str);

                while(fgets(str,50,fp1))
                {
                    if(str[0] == '.')
                        continue;
                    sscanf(str,"%s %s ",  opcode, operand);
                    //printf("%s",str);
                    if (strcmp(opcode,"MEND") == 0)
                    {
                        //printf("<-%s-> into deftab\n",str);
                        fprintf(fp4, "%s",str);
                        //printf(" %d into namtab\n",ftell(fp4));
                        fprintf(fp2,"%d\n",ftell(fp4));
                        break;
                    }
                    else
                    {
                        //printf("<-%s-> into deftab\n",str);
                        fprintf(fp4, "%s\t%s\n",opcode,operand);
                    }
                }
                continue;
            }

            //printf("%s\t%\t %s\n",  opcode, operand);
            fclose(fp2);                        //For invocation
            fclose(fp4);
            FILE *fp6=fopen("namtab.txt","r");
            FILE *fp7=fopen("deftab.txt","r");
            if (fp6 == NULL ||fp7 == NULL )
                printf("Error reading files\n");
            int f=0;
            while(fgets(str2,50,fp6))
            {
                 //printf("%s--?--",str2);
                char macroName[50];
                char startAddr[50], endAddr[50];
                //int startAddr, endAddr;
                sscanf(str2,"%s %s %s",macroName,startAddr,endAddr);
                //printf("Comparing %s- with +%s\n",macroName,label);
                if(strcmp(macroName,label)==0)
                {
                    //printf("Found!\n");
                    fprintf(fp5,".\t%s\t%s\n",label,opcode);
                    fprintf(fp3,"%s",opcode);
                    f=1;
                    int start = atoi(startAddr);
                    int end = atoi(endAddr);
                    //printf("Reading file from %d to %d\n",start, end);
                    fseek(fp7,0, start);
                    while(fgets(str1, 50, fp7))
                    {
                        //printf("//%s",str1);
                        int count = word_count(str1);
                        if(count == 1 )
                            break;
                        if( ftell(fp7) >= end)
                        {
                            printf("Finished reading from file. Marked: %d",end);
                            break;
                        }
                        else
                        {
                            //printf("%d %s ---- Into output file\n",ftell(fp7) ,str1);
                            int i =0;
                            char s1[50],s2[50],s3[50],s4[50];
                            sscanf(str1,"%s%s",s1,s2);
                            if(s2[1]=='?')
                            {
                                fprintf(fp5,"\t%s\t",s1);
                                fclose(fp3);
                                FILE *fp8 = fopen("argtab.txt","r");
                                char temp = fgets(s3,50,fp8);

                                for(i=0;s2[i]!='?';i++)
                                    fprintf(fp5,"%c",s2[i]);
                                //printf("~%d",i);
                                fprintf(fp5,"%s",s3);
                                printf("%s",s3);
                                for (;s2[i]!='1';i++)
                                    continue;
                                i++;            //Skippin the '>' as well!
                                for(;s2[i]!='\0';i++)
                                    fprintf(fp5,"%c",s2[i]);
                                fprintf(fp5,"\n");
                            }
                            else
                            {
                                if(strcmp(s2,"MACRO")!=0)
                                    fprintf(fp5,"\t%s",str1);
                                //printf("\t%s----++\t%s\n",s1,s2);
                            }
                        }
                    }
                    break;
                }
            }
            if(f==0)
                fprintf(fp5,"\t%s\t%s\n",label,opcode);

            fclose(fp6);
            fclose(fp7);
            fp2=fopen("namtab.txt","a");
            fp4=fopen("deftab.txt","a");
            //printf("Here\n");

            if (fp2 == NULL ||fp4 == NULL )
                printf("Error reading files\n");
        }
        else if(count == 1)
        {

            if(strcmp(str,"MEND")==0)
                continue;
            sscanf(str,"%s",opcode);
            //printf("%s",opcode);
            fclose(fp2);                        //For invocation
            fclose(fp4);
            FILE *fp6=fopen("namtab.txt","r");
            FILE *fp7=fopen("deftab.txt","r");
            if (fp6 == NULL ||fp7 == NULL )
                printf("Error reading files\n");
            //rewind(fp6);
            int f=0;
            while(fgets(str2,50,fp6))
            {
                char macroName[50];
                char startAddr[50], endAddr[50];
                //int startAddr, endAddr;
                sscanf(str2,"%s %s %s",macroName,startAddr,endAddr);
                //printf("Comparing %s-- with --%s\n",macroName,opcode);
                if(strcmp(macroName,opcode)==0)
                {
                    //printf("Found!\n");
                    f=1;
                    int start = atoi(startAddr);
                    int end = atoi(endAddr);
                    //printf("Reading file from %d to %d\n",start, end);
                    fseek(fp7, start,0);
                    //printf("Current file position :%d\n",ftell(fp7));

                    while(fgets(str1, 50, fp7))
                    {
                        //printf("//%s",str1);
                        int count = word_count(str1);
                        if(count == 1 )
                            break;
                        if( ftell(fp7) >= end)
                        {
                            printf("Finished reading from file. Marked: ",end);
                            break;
                        }
                        else
                        {
                            //printf("%d %s ---- Into output file\n",ftell(fp7) ,str1);
                            char s2[100],s1[100];
                            sscanf(str1,"%s%s",s1,s2);
                            if(strcmp(s2,"MACRO")!=0)
                                    fprintf(fp5,"\t%s",str1);
                            //fprintf(fp5,"\t-%s",str1);
                        }
                    }
                }
                else
                {
                    fprintf(fp5,".%s",str);
                }
            }
            if(f==0)
                fprintf(fp5,"\t%s\n",opcode);
           // else if(f==1)
             //   fprintf(fp5,".\t%s\t%s\n",label,opcode);

            fclose(fp6);
            fclose(fp7);
            fp2=fopen("namtab.txt","a");
            fp4=fopen("deftab.txt","a");
        }
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    printf("\nAll files closed!");
}
void getFiles()
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1=fopen("input.txt","r");
    fp2=fopen("namtab.txt","w");
    fp3=fopen("argtab.txt","w");
    fp4=fopen("deftab.txt","w");
    fp5=fopen("op.txt","w");

    if(fp1 == NULL || fp2 == NULL ||fp3 == NULL ||fp4 == NULL ||fp5 == NULL )
        printf("Error opening file");
    else
        printf("All files intact.\n");

    process(fp1,fp2,fp3,fp4,fp5);
}
