#include "header.h"
void first()
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1 = fopen("input.txt","r");
    fp2 = fopen("ESTAB.txt","w");
    char str1[50],str2[50],str3[50],str4[50];
    char type[50],progName[50],defName[50];
    int addr1=0,addr2=0,addr3=0,addr4=0;
    int progAddr=0,csAddr=0;
    if(fp1 == NULL || fp2 == NULL)
        printf("Error opening files\n");
    //printf("FIles intact\n");
    int temp;

    while(fscanf(fp1,"%s",str1)!= EOF)
    {
        if(strcmp(str1,"H")==0)
        {
            fscanf(fp1,"%s",progName);
            printf("%s\t\t",progName);
            fprintf(fp2,"%s\t\t",progName);
            fscanf(fp1,"%d",&temp);
            printf("%d\t",addr1);
            fprintf(fp2,"%d\t",addr1);
            fscanf(fp1,"%d",&addr2);
            printf("%d\n",addr2);
            fprintf(fp2,"%d\n",addr2);
            addr4 = addr1;
            addr1+=addr2;
        }
        else if(strcmp(str1,"D")==0)
        {
            while(fscanf(fp1,"%s",str4)!= EOF)
            {
                 if(strcmp(str4,"R")==0)
                    break;
                else
                {
                        printf("\t%s\t",str4);
                        fprintf(fp2,"\t%s\t",str4);
                        fscanf(fp1,"%d",&addr3);
                        addr3+=addr4;
                        printf("%d\n",addr3);
                        fprintf(fp2,"%d\n",addr3);
                }
            }
        }

    }
    fclose(fp1);
    fclose(fp2);
    printf("All files closed");
}
