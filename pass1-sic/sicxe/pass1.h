void check()
{
    FILE *fp1 = fopen("input.txt","r");
    FILE *fp2 = fopen("optab.txt","r");
    FILE *fp3 = fopen("register.txt","r");
    char str[100];
    char col1[50];
    char str1[50];
    char str2[50];
    char col2[50];
    char col3[50];
    char opcode[50];
    int flag=0;
    int start_addr;
    int last_addr;
    int value;
    int LOCCTR=1000;
    int i,j,k,l;
    int f=0;
    int op;
    char previous='~';

    while(fgets(str, 30,fp1))
    {
f=0;

    int word_count=0;
    printf("--%d\n",LOCCTR);
        //printf("%s",str);
         for(i=0;str[i]!='\0';i++)
        {
            if(isspace(str[i]))
            {
                if(!isspace(previous))
                {
                    word_count++;
                    //printf("%d",word_count);
                }
                previous=32;
            }
            else

                previous=str[i];
        }

         if(word_count==2)
         {
                sscanf(str,"%s %s",col2,col3);
                //fprintf(fp1,"%X\t%s\n",LOCCTR,col1);
                rewind(fp2);
                while(!feof(fp2))                  //search optab for opcode
                {
                    fgets(str1,30,fp2);
                    sscanf(str1,"%s",&opcode);
                    //printf("%s\n",opcode);
                    if(strcmp(col2,opcode)==0)
                    {
                        flag=1;
                        //printf("%s found in optab. Valid",opcode);
                        break;
                    }
                }
                    if(flag==1)
                    {
                        if(col3[0]=='A' || col3[0]=='X' || col3[0]=='B' || col3[0]=='S' || col3[0]=='T' || col3[0]=='F' || col3[0]=='L')
                        {
                                if(col3[1]=='\0'){
                                    //printf("A1 Valid register. Format 2");
                                    f=1;

                                    LOCCTR=LOCCTR+2;
                                    continue;
                                }
                                if (col3[2]=='A' || col3[2]=='X' ||col3[2]=='B' || col3[2]=='S' || col3[2]=='T' || col3[2]=='F'|| col3[2]=='L')
                                {
                                    //printf("A2 Valid register.\n");
                                    f=1;
                                }

                        }
                        //printf("Flag==%d\n",flag);
                        if(f==1){
                            LOCCTR=LOCCTR+2;
                            //continue;
                            printf("%d is locctr",LOCCTR);
                        }
                        else
                            printf("\nNot format 2");
                        printf("%s",col2);
                        if(col2[0]=='+')
                        {
                                    printf("%d",LOCCTR);
                                    LOCCTR=LOCCTR+4;
                                    printf("--%d\n",LOCCTR);
                        }

                    }
                    else
                        printf("%s not found in optab\n",col2);
            }
            if(word_count==1)
            {
                sscanf(str,"%s",col2);
                /*if(strcmp(col2,"END")==0)
                {
                    last_addr=LOCCTR;
                    break;
                }
                else*/
                    LOCCTR=LOCCTR+1;
            }
    }

}
