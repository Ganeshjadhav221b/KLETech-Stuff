#include"header.h"

void objectProgram(int len)
{
    //printf("Len = %x\n",len);
    FILE *fp1, *fp2,*fp3;
    fp1 = fopen("objectCode.txt","r");
    fp2 = fopen("objectProgram.txt","w");
    fp3 = fopen("symtab.txt","r");
    char str1[50],str2[50],str3[50],str4[50];
    int firstText = 0;
    int startAddr = 0;
    while(fgets(str1,50,fp1))
    {
        //printf("%d-\n",firstText);
        int count = word_count(str1);
        char operand[50],opcode[50],label[50],op[50], addr[50],objCode[50];
        int address;
        int opValue;
        int flag =0;
        int c=0;
        int i=0;
        if(count == 5)
        {
            sscanf(str1,"%s%s%s%s%s",addr,label,opcode,operand,objCode);
            //printf("B4: %d\n",firstText);
            if(++firstText == 1 )
                {
                    printf("T^00%s",addr);
                    strcat(str3,"^");
                    strcat(str3,objCode);
                    //printf("Concatenating %s with %s \n",str3,objCode);
                    //printf("not B4: %d\n",firstText);
                }
            else if(firstText == 11)
            {

                c=0;
                for(i =0 ;str3[i]!='\0';i++)
                {
                    if(str3[i] == '^')
                        c++;
                }
                printf("%x^%s",c,str3);
                printf("\n");
                firstText = 0;
                str3[0]='\0';
                strcat(str3,"^");
                strcat(str3,objCode);

                continue;
            }
            else
            {
                strcat(str3,"^");
                //printf("Concatenating %s with %s \n",str3,objCode);
                strcat(str3,objCode);
                //printf("%s-\n",str3);
            }
        }

        else if (count == 4)
        {
            sscanf(str1,"%s%s%s%s",addr,opcode,operand,objCode);
            //printf("%s\t%s\t%s\t%s\n",addr,opcode,operand,objCode);
            //printf("Comparing %s with START\n",opcode);
            if(strcmp(operand,"START")==0)
            {
                printf("H^COPY^%x^%x\n",atoi(objCode),len);
                startAddr = atoi(addr);
                continue;
            }

            if(strcmp(operand,"RESW")==0 || strcmp(operand,"RESB")==0)
                continue;

            else
            {
                firstText++;
                if(firstText == 1 )
                {
                     printf("T^00%s",addr);

                    strcat(str3,"^");
                    //printf("?Concatenating %s with -%s- \n",str3,objCode);
                    strcat(str3,objCode);
                    //printf("not B4: %d\n",firstText);
                }
                else if(firstText == 11)
                {
                    firstText = 0;
                    c=0;
                    //printf("--%s--\n",str3);
                    for(i =0 ;str3[i]!='\0';i++)
                    {
                        if(str3[i] == '^')
                            c++;
                    }
                    printf("^%x%s",c*3,str3);
                    printf("\n");
                   str3[0]='\0';
                    //printf("Concatenating -%s- with %s \n",str3,objCode);
                    strcat(str3,"^");
                    strcat(str3,objCode);
                    //printf("T^00%s^",addr,objCode);
                }
                else
                {
                    strcat(str3,"^");
                    strcat(str3,objCode);
                    //printf("%s+\n",str3);
                }
            }
        }
        else
        {

            firstText = 0;
            c=0;
            //printf("--%s--\n",str3);
            for(i =0 ;str3[i]!='\0';i++)
            {
                if(str3[i] == '^')
                    c++;
            }
            printf("^%x%s",c*3,str3);
            printf("\n");
        }
    }
    printf("END^%d",startAddr);
}
