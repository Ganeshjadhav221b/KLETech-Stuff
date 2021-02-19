#include "sic.h"
int isnum(char str[50])         ///function to check whether all are digits in column3
{
    int i;
    char temp[10];
    int flag=0;
    for(i=0;str[i]!='\0';i++)
    {
        temp[i]=str[i];
        if(isdigit(temp[i]))
        {
            flag=1;
        }
        else
        {
            flag=0;
            break;
        }
    }
    return flag;
}
int getresult(char operand,int value1,int value2)
{
    int result,result1,result2;
    switch(operand)                 ///switch case to evaluate the expression
    {
    case '+':
        result=value1+value2;
        break;
    case '-':
        result1=value1-value2;
        result2=value2-value1;
        if(result1>result2)
            result=result1;
        else
            result=result2;
        break;
    default:
        break;
    }
    return result;
}
int ischar(char str[50])            ///function for deriving two operands from expression
{
    int i,pos;
    char temp[50];
    for(i=0;str[i]!='\0';i++)
    {
        temp[i]=str[i];
        if(isalpha(temp[i]))
        {
            continue;
        }
        else
        {
            pos=i;
            break;
        }
    }
    //printf("%d is position\n",pos);
    return pos;
}

int usesearch(char str[100])        ///function to check whether EQU is present in fetched string or not
{
   char search[]="USE";
   int count1=0,count2=3,i,j,flag;
   while (str[count1]!='\0')
   {
       count1++;
   }
    for(i=0;i<=count1-count2;i++)
    {
        for(j=i;j<i+count2;j++)
        {
            flag=1;
            if (str[j]!=search[j-i])
            {
                flag=0;
                break;
            }
        }
        if (flag==1)
        break;
    }
    return flag;
}

int equsearch(char str[100])        ///function to check whether EQU is present in fetched string or not
{
   char search[]="EQU";
   int count1=0,count2=3,i,j,flag;
   while (str[count1]!='\0')
   {
       count1++;
   }
    for(i=0;i<=count1-count2;i++)
    {
        for(j=i;j<i+count2;j++)
        {
            flag=1;
            if (str[j]!=search[j-i])
            {
                flag=0;
                break;
            }
        }
        if (flag==1)
        break;
    }
    return flag;
}
int word_count(char str[])
{
    int i,count=0;
    char previous='~';
    for(i=0;str[i]!='\0';i++)
    {
        if(isspace(str[i]))
        {
            if(!isspace(previous))
            {
                count++;           ///to keep the count of words in each line
            }
            previous=32;
        }
        else{
                previous=str[i];
            }
    }
    //printf("%d is word_count\n",count);
    return count;
}

void objectcode()
{
    FILE *fp,*fp1;
    fp=fopen("objectcode.txt","r");
    fp1=fopen("object_code.txt","w");
    int i,block,wcount,c,c1;
    char str[50],col1[50],col2[50],col3[50],code[50],locctr[20];
    while(fgets(str,50,fp))
    {
        c=0,c1=0;
        wcount=word_count(str);
        if(wcount==6)
        {
            sscanf(str,"%s %d %s %s %s %s",&locctr,&block,&col1,&col2,&col3,&code);
            fprintf(fp1,"%s\t%d\t",locctr,block);
            for(i=2;code[i]!='\0';i++)
            {
                c++;
            }
            fprintf(fp1,"%c",code[0]);
            fprintf(fp1,"%c",code[1]);
            for(i=c;i<4;i++)
            {
                fprintf(fp1,"0");               ///if less than 4 append zeroes
            }
            for(i=2;i<2+c;i++)
            {
                fprintf(fp1,"%c",code[i]);
            }
            fprintf(fp1,"\n");
        }
        if(wcount==5)
        {
            sscanf(str,"%s %d %s %s %s",&locctr,&block,&col1,&col2,&code);
            {
                if((strcmp(col2,"EQU")==0)||(strcmp(col2,"RESW")==0)||(strcmp(col2,"RESB")==0))
                    continue;
                else if(strcmp(col1,"*")==0)
                {
                    fprintf(fp1,"%s\t%d\t%s\n",locctr,block,code);          ///if * write as it is
                }
                else
                {
                    fprintf(fp1,"%s\t%d\t",locctr,block);
                    for(i=2;code[i]!='\0';i++)
                    {
                        c++;
                    }
                    fprintf(fp1,"%c",code[0]);
                    fprintf(fp1,"%c",code[1]);
                    for(i=c;i<4;i++)
                    {
                        fprintf(fp1,"0");
                    }
                    for(i=2;i<2+c;i++)
                    {
                        fprintf(fp1,"%c",code[i]);
                    }
                    fprintf(fp1,"\n");
                }
            }
        }
        else if(wcount==4)
        {
            sscanf(str,"%s %d %s %s",&locctr,&block,&col1,&code);
            if(strcmp(col1,"USE")==0)
            {
                continue;
            }
            else
            {
                fprintf(fp1,"%s\t%d\t%s\n",locctr,block,code);
            }
        }
        else if(wcount==3)
            continue;
    }
    fclose(fp);
    fclose(fp1);
}
