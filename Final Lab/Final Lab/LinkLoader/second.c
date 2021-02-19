#include "header.h"
void second()
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1 = fopen("input.txt","r");
    fp2 = fopen("ESTAB.txt","r");
    fp3 = fopen("ESTAB.txt","w");

    if(fp1 == NULL || fp2 == NULL || fp3 == NULL )
        printf("Error opening files\n");

    char str1[50],str2[50],str3[50],str4[50];
    char type[50],progName[50],defName[50];
    int addr1=0,addr2=0,addr3=0;
    int progAddr=0,csAddr=0;
    //printf("FIles intact\n");
    int temp;

    while(fscanf(fp1,"%s",str1)!= EOF)
    {
        if(strcmp(str1,"T")==0)
        {


        }
        else if(strcmp(str1,"M")==0)
        {


        }
    }
