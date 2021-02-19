#include "header.h"

void pass2(int a)
{
    FILE *fp1 = fopen("input.txt","r");
    FILE *fp2 = fopen("ESTAB.txt","r");
    FILE *fp3 = fopen("output.txt","w");
    char b[50],str[50];
    char prgname[50],c[50];
    char ipn[50],extref[50];
    char straddr[50],def[50];
    int b_int,addr=0,straddr_i,b_h,address,opcode=0,i,j=0,extref_i;
    while(fscanf(fp1,"%s",b))
    {
        if(strcmp(b,"END")==0)
        {
            break;
        }
        if(strcmp(b,"H")==0)
        {
            fscanf(fp1,"%s",ipn);
            while(fscanf(fp2,"%s",prgname))
            {
                if(strcmp(prgname,ipn)==0)
                {
                    fscanf(fp2,"%s",straddr);
                    //printf("\n%s %s\n",prgname,straddr);
                    break;
                }
            }
        }

        if(strcmp(b,"T")==0)
        {
            while(1)
            {
                fscanf(fp1,"%s",b);
                printf("a %s\n",b);
                if((strcmp(b,"R")==0)||strcmp(b,"D")==0||strcmp(b,"M")==0||strcmp(b,"H")==0||strcmp(b,"E")==0||strcmp(b,"END")==0)
                {
                    break;
                }
                else
                {
                b_int=atoi(b);                      ///first address of the text record.
                straddr_i=atoi(straddr);            ///starting addr of that program
                addr=b_int+straddr_i;
                while(1)
                {
                    fscanf(fp1,"%s",b);
                    if((strcmp(b,"R")==0)||strcmp(b,"D")==0||strcmp(b,"M")==0||strcmp(b,"H")==0||strcmp(b,"E")==0||strcmp(b,"END")==0||strcmp(b,"T")==0)
                    {
                        break;
                    }
                    fprintf(fp3,"%d\t%s\n",addr,b);
                    addr=addr+3;
                }
                }
                if((strcmp(b,"M")==0))
                    break;
            }
        }
    }
    fclose(fp3);
    rewind(fp1);
    rewind(fp2);
    fp3 = fopen("mem.txt","r");
    FILE *fp4 = fopen("mem_str.txt","w");
    while(fscanf(fp1,"%s",b))
    {
        //printf("%s is b\n",b);
         for(j=0;c[j]!='\0';j++)
        {
                c[j]='\0';
        }
        if(strcmp(b,"END")==0)
        {
            break;
        }
        if(strcmp(b,"H")==0)
        {
            fscanf(fp1,"%s",ipn);
            rewind(fp2);
            while(fscanf(fp2,"%s",prgname))
            {
                if(strcmp(prgname,ipn)==0)
                {
                    fscanf(fp2,"%s",straddr);
                    printf("\n%s %s\n",prgname,straddr);
                    break;
                }
            }
        }
        if(strcmp(b,"M")==0)
        {
            while(strcmp(b,"E")!=0)
            {
                fscanf(fp1,"%s",b);
                if((strcmp(b,"R")==0)||strcmp(b,"D")==0||strcmp(b,"M")==0||strcmp(b,"H")==0||strcmp(b,"E")==0||strcmp(b,"END")==0||strcmp(b,"T")==0)
                {
                    break;
                }

                b_int=atoi(b);
                straddr_i=atoi(straddr);            ///starting addr of that program
                addr=b_int+straddr_i;
                rewind(fp3);
                while(fgets(str,30,fp3))
                {
                    sscanf(str,"%d %d",&address,&opcode);
                    //printf("%d is address\n",address);
                    //printf("%d is addr\n",addr);
                    if(addr==address)
                    {
                        printf("matched\n");
                        //rewind(fp3);
                         fscanf(fp1,"%s",b);
                         fscanf(fp1,"%s",b);
                        j=0;
                         for(i=1;b[i]!='\0';i++)
                         {
                             c[j]=b[i];
                             j++;
                         }
                         c[j]='\0';
                         printf("%s is c\n",c);
                        // fflush(fp2);
                         while(fscanf(fp2,"%s",def))
                         {
                              if(strcmp(c,def)==0)
                              {
                                  //fflush(fp2);
                                  fscanf(fp2,"%s",extref);
                                  printf("%s is extref\n",extref);
                                  break;
                              }
                         }
                         extref_i=atoi(extref);
                         opcode=opcode+extref_i;
                        // printf("%d is inner opcode\n",opcode);
                         //rewind(fp3);
                         break;
                    }
                    //printf("%d is outer opcode\n",opcode);
                    fprintf(fp4,"%d\t%d\n",address,opcode);

                }
            }

        }

    }

}
