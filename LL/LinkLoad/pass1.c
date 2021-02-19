#include<stdio.h>
#include"header.h"
int pass1()
{
    int progrAddr=4096;
    int csAddr;

    //printf("Enter the starting address:");
    //scanf("%d", &progrAddr);

    csAddr = progrAddr;

    printf("\nProgram Adress: %d", progrAddr);
    printf("\nControl section 1's Adress: %d\n", csAddr);

    FILE *fp1 = fopen("input.txt", "r");
    if(fp1 == NULL)
        printf("\nError loading input file!");

    FILE *fp2 = fopen("ESTAB.txt", "w");
    if(fp2 == NULL)
        printf("\nError loading estab file!");

    char str1[100] , inp[100] , str2[100] , str3[100];
    int csLength;
    int d;
    while(fscanf(fp1,"%s",str1))
    {
        if(strcmp(str1,"END")==0)
            break;

        else if(strcmp(str1,"E")==0)
            csAddr=csAddr+csLength;

        else if(strcmp(str1,"H")==0)
        {
            fscanf(fp1,"%s",str2);
            fscanf(fp1,"%s",str1);
            fscanf(fp1,"%x",&csLength);
            fprintf(fp2,"%s\t\t%x\t%x\n",str2,csAddr,csLength);
        }
        else if(strcmp(str1,"D")==0)
        {
            while(1)
            {
                fscanf(fp1,"%s",str1);
                if((strcmp(str1,"R")==0)||strcmp(str1,"T")==0||strcmp(str1,"M")==0)
                    break;

                fprintf(fp2,"\t%s\t",str1);
                fscanf(fp1,"%x",&d);
               // printf("%x d",d);
                d=csAddr+d;
                fprintf(fp2,"%x\n",d);
            }
        }
    }
    fclose(fp1);
    fclose(fp2);

    return progrAddr;
}

