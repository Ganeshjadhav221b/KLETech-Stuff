#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct prog
{
    char label[10];
    char opcode[10];
    char operand[10];
};

struct adr
{
    unsigned int val;
};

struct label
{
    char label[10];
};

struct opcode
{
    char op[10];
    char code[5];
};

struct Pass2
{
	char label[10];
    char opcode[10];
    char operand[10];
    char obj[10];
    unsigned int val;
};

struct symtab
{
	char label[10];
	unsigned int addr;
};


void Length(int *length)
{
	FILE *fp1;
	char *token,ch1[20],buf[10];
	fp1=fopen("length.txt","r");
	while(fgets(ch1,5,fp1)!=NULL)
	{
		token=strtok(ch1," ");
		strcpy(buf,token);
		sscanf(buf,"%x",length);
	}
	fclose(fp1);
}

main()
{
	FILE *fp,*fp1,*fp2;
	const char s[2] ="\t";
    char *token,ch[100],ch1[20],buf[10],part1[5],part2[10],a[10],text[100],t[100];
    int count=0,i=0,j=0,k=0,opcount=0,symcount=0,st=0,line=0,opflag=0,symflag=0;
    struct Pass2 store[100];
    struct opcode opc[50];
    struct symtab symtab[50];
    unsigned int stt_adr=0x00,length=0x00,val=0x00,c=0x00;

	Length(&length);

	fp2=fopen("symtab.txt","r");
	while(fgets(ch1,20,fp2)!=NULL)
    {
    	sscanf(ch1,"%s %x",&buf,&val);
    	strcpy(symtab[symcount].label,buf);
    	symtab[symcount].addr=val;
        symcount++;
    }
	fclose(fp2);

	fp1=fopen("optab.txt","r");
	while(fgets(ch1,20,fp1)!=NULL)
    {
        sscanf(ch1,"%s %s",&opc[opcount].op,&opc[opcount].code);
        opcount++;
    }
	fclose(fp1);

    fp=fopen("intermediate.txt","r");
    while(fgets(ch,100,fp)!=NULL)
    {
    	ch[strlen(ch)-1]=0;
    	sscanf(ch,"%s %s %s %s",&buf,&store[i].label,&store[i].opcode,&store[i].operand);
    	if(strcmp(store[i].label,"-")==0)
    		strcpy(store[i].label," ");
    	if(strcmp(store[i].operand,"-")==0)
    		strcpy(store[i].operand," ");

    	sscanf(buf,"%x",&val);
    	store[i].val=val;
    	i++;
	}

	line=i;
	fclose(fp);

	fp=fopen("obj_prog.txt","w");
	if(strcmp(store[0].opcode,"START") == 0)
	{
		st=1;
		stt_adr=store[1].val;
		strcpy(store[0].obj,"");
		store[0].val=0x00;
	}

	for(i=st;i<line-1;i++)
	{
		for(j=0;j<opcount;j++)
		{
			if(strcmp(store[i].opcode,opc[j].op) ==0)
			{
				strcpy(part1,opc[j].code);
				if(strcmp(store[i].operand," ")!=0)
				{
					for(k=0;k<symcount;k++)
					{
						if(strcmp(store[i].operand,symtab[k].label)==0)
						{
							sprintf(part2,"%x",symtab[k].addr);
							symflag=1;
							strcat(part1,part2);
							strcpy(store[i].obj,part1);
							break;
						}else{
							symflag=0;
						}
					}
					if(symflag==0)
					{
						strcpy(a,store[i].operand);
						if(a[strlen(a)-2] == ',' && a[strlen(a)-1]=='X')
						{
							a[strlen(a)-2]=0;
							for(k=0;k<symcount;k++)
							{
								if(strcmp(a,symtab[k].label)==0)
								{
									val=symtab[k].addr;
									val+=0x8000;
									sprintf(part2,"%x",val);
									strcat(part1,part2);
									strcpy(store[i].obj,part1);
									symflag=1;
									break;
								}else{
									symflag=0;
								}
							}
						}
						if(symflag==0)
						{
							strcpy(part2,"err");
							strcat(part1,part2);
							strcpy(store[i].obj,part1);
							break;
						}
					}
				}
				else
				{
					strcpy(part2,"0000");
					strcat(part1,part2);
					strcpy(store[i].obj,part1);
				}
				opflag=1;
				break;
			}
			else
			{
				opflag=0;
			}
		}
		if(opflag==0)
		{
			if(strcmp(store[i].opcode,"BYTE")==0)
			{
				char sub[2];
				strcpy(a,store[i].operand);
				if(store[i].operand[0]=='C')
				{
					token=strtok(a,"'");
					token=strtok(NULL,"'");
					strcpy(a,token);
					strcpy(buf,"");
					for(k=0;k<strlen(a);k++){
					  sprintf(sub,"%x", a[k]);
					  strcat(buf,sub);
					}
					strcpy(store[i].obj,buf);
				}
				else if(store[i].operand[0]=='X')
				{
					token=strtok(a,"'");
					token=strtok(NULL,"'");
					strcpy(buf,token);
					strcpy(store[i].obj,buf);
				}
				else
				{
					strcpy(buf,"Error");
					strcpy(store[i].obj,buf);
				}
			}
			else if(strcmp(store[i].opcode,"WORD")==0)
			{
				sscanf(store[i].operand,"%ux",&val);
				sprintf(buf,"%6.6x",val);
				strcpy(store[i].obj,buf);
			}
			else if(strcmp(store[i].opcode,"RESW")==0 || strcmp(store[i].opcode,"RESB")==0)
			{
				strcpy(buf,"");
				strcpy(store[i].obj,buf);
			}
			else{
				strcpy(buf,"ERROR");
				strcpy(store[i].obj,buf);
			}
		}
	}

	for(i=0;i<line;i++)
	{
		printf("%4.4x\t%s\t%s\t%s\t%s\n",store[i].val,store[i].label,store[i].opcode,store[i].operand,store[i].obj);
	}
	printf("\n");
	if(st==1)
	{
		printf("H^%6.6s^%6.6x^%6.6x\n",store[0].label,stt_adr,length);
		fprintf(fp,"H^%6.6s^%6.6x^%6.6x\n",store[0].label,stt_adr,length);
	}

	i=st;
	while(i<line-1)
	{
		c=0;
		strcpy(text,"T^");
		sprintf(buf,"%6.6x",store[i].val);
		strcat(text,buf);
		strcpy(t,"");
		while((c<=0x1d) && (i<line-1))
		{
			if(strlen(store[i].obj)!= 0)
			{
				strcat(t,"^");
				strcat(t,store[i].obj);
			}
			c+=0x03;
			i++;
		}
		sprintf(buf,"^%x",c);
		strcat(text,buf);
		strcat(text,t);
		printf("%s\n",text);
		fprintf(fp,"%s\n",text);
	}
	printf("E^%6.6x",stt_adr);
	fprintf(fp,"E^%6.6x",stt_adr);

	fclose(fp);
	printf("\n\n");
	printf("Program Length\t:%4.4x",length);
}
