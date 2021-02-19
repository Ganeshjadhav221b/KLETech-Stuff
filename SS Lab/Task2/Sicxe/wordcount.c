#include "sicxe.h"
void call()
{
    FILE *fp;
    char str[100];
    char previous='~';
    int wc=0,i;
    fp=fopen("input2.txt","r");
    if(fp==NULL)
    {
        printf("Error opening file");
        exit(0);
    }
    while(fgets(str,30,fp))
    {
        wc=0;
        for(i=0;str[i]!='\0';i++)
        {
            if(isspace(str[i]))
            {
                if(!isspace(previous))
                {
                    wc++;
                }
                previous=32;
            }
            else
            {
                previous=str[i];
            }
        }
        printf("%d is word count\n",wc);
    }
}
int call1(char str[100])
{
    int wc=0,i;
    char previous='~';
    for(i=0;str[i]!='\0';i++)
    {
        printf("%c str[i]\n",str[i]);
        if(isspace(str[i]))
        {
            printf("%c is prev\n",previous);
            if(!isspace(previous))
            {
                wc++;
            }
            previous=32;
        }
        else
            previous=str[i];
    }
    return wc;
}
