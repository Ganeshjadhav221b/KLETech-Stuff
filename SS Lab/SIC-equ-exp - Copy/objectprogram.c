#include "sic.h"
void objectprogram()
{
    FILE *fp;
    FILE *fp1;
    fp=fopen("object_code.txt","r");
    fp1=fopen("objectprogram.txt","a");
    fprintf(fp1,"\n");
    char col1[20],col2[20],col3[20],a[100],b[100],c[100],str[50];
    int i,j,k,size=0,count,flag;
    while(fgets(str,40,fp))
    {
        //printf("%s",str);
        count=0;
        size=0,flag=0;
        for(k=0;a[k]!='\0';k++)
        {
            a[k]='\0';
            b[k]='\0';
        }
        sscanf(str,"%s %s %s",&col1,&col2,&col3);
        if(strcmp(col2,"0")==0)
        {
            fprintf(fp1,"T^");
            strcat(a,col3);
           // printf("%s is a\n",a);
        }
        for(i=0;col1[i]!='\0';i++)
        {
            count++;
        }
        //printf("%d\n",count);
        for(i=count;i<6;i++)
        {
            //printf("0");
            fprintf(fp1,"0");
        }
        fprintf(fp1,"%s^",col1);            ///prints the start address
        for(i=1;i<10;i++)
        {
            if(fgets(str,30,fp))
            {
                sscanf(str,"%s %s %s",col1,col2,col3);
                if(strcmp(col2,"0")==0)
                {
                   strcat(a,"^");
                   strcat(a,col3);
                   //printf(("%s is a\n",a));
                }
            }
            else
                break;
        }
        if(strcmp(col2,"0")==0)
        {
            for(j=0;a[j]!='\0';j++)
            {
                if(a[j]!='^')
                    size++;
            }
        }
         int size_field=size/2;
         fprintf(fp1,"%X^",size_field);
         //printf("%X^",size_field);
         if(strcmp(col2,"0")==0)
         {
             for(i=0;a[i]!='\0';i++)
            {
            //printf("%c",a[i]);
                fprintf(fp1,"%c",a[i]);
            }
         }
        //printf("\n");
        fprintf(fp1,"\n");
    }
}
