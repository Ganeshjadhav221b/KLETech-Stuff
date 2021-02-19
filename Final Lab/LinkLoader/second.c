#include "header.h"
void second()
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1 = fopen("input.txt","r");
    fp2 = fopen("ESTAB.txt","r");
    fp3 = fopen("output.txt","w");

    if(fp1 == NULL || fp2 == NULL || fp3 == NULL )
        printf("Error opening files\n");

    char str1[50],str2[50],str3[50],str4[50];
    char type[50],progName[50],defName[50];
    int addr1=0,addr2=0,addr3=0;
    int progAddr=0,csAddr=0;
    //printf("FIles intact\n");
    int temp;
    int col1,col2;
    int flag=0;

    while(fscanf(fp1,"%s",str1)!= EOF)
    {
        //printf("Comparing %s with H/T\n",str1);
        if(flag ==1)
        {
            col1 = atoi(str1);
            //printf("--Adding %d to %d---\n",addr1,col1);
            col1+=addr1;
            while(fscanf(fp1,"%s",str2)!=EOF)
            {
                flag=0;
               if(strcmp(str2,"M")==0 )
                    break;
                if(strcmp(str2,"T")==0)
                {
                    flag=1;
                    break;
                }
                printf("%d\t%s\n",col1,str2);
                col1+=3;
                //printf("%d\t%d\n",col1,col2);
            }
        }

        if(strcmp(str1,"H")==0)
        {
            fscanf(fp1,"%s",progName);
            printf("%s-",progName);

            while(fscanf(fp2,"%s",str2) != EOF )
            {
                //printf("Comparing %s with %s\n",str2,progName);
                if(strcmp(str2,progName) ==0)
                {
                    //printf("Found %s\n",str2);
                    break;
                }
            }
            fscanf(fp2,"%d",&addr1);
            printf("-%d\n",addr1);
        }

        else if(strcmp(str1,"T")==0 )
        {
            fscanf(fp1,"%d",&col1);
            //printf("Adding %d to %d\n",addr1,col1);
            col1+=addr1;
            while(fscanf(fp1,"%s",str2)!=EOF)
            {
               if(strcmp(str2,"M")==0 )
                    break;
                if(strcmp(str2,"T")==0)
                {
                    flag=1;
                    break;
                }
                printf("%d\t%s\n",col1,str2);
                col1+=3;
                //printf("%d\t%d\n",col1,col2);
            }
        }
    }
}
