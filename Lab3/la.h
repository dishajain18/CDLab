#include <string.h>

char* keyword[5]={"main","int","char","if","else"};
char* relop[6]={"==","!=","<=",">=","<",">"};
char* reloptk[6]={"EQ","NE","LE","GE","LT","GT"};
char spesymbol[10]={'#',',',';','(',')','{','}','[',']','='};
char ariop[5]={'+','-','*','/','%'};
char identifier[100][20];
id_len=0;

typdef struct{
	int row,col;
	char tokenName[10];
}token;

int isalpha(char c)
{
	if((c>=65 && c<=90) || (c>=97 && c<=122))
		return 1;
}

int iskeyword(char * str)
{
	for(int i=0;i<5;i++)
	{
		if(strcmp(keyword[i],str)==0)
			return i;
	}
	return -1;
}

int isrelop(char * str)
{
	for(int i=0;i<6;i++)
	{
		if(strcmp(relop[i],str)==0)
			return i;
	}
	return -1;
}

int 

token getnexttoken(FILE* fp)
{
	char c;
	int lines=0;
	int col=0;
	long int pos = ftell(fp);
	c=fgetc(fp);
	col++;
	if(c=='\n') 
		{
			lines++;
			col=0;
		}
	if(c=='#')
	{
		int isdir=removepredir(fp,lines,col);
		if(!isdir)
			fseek(fp,pos,SEEK_SET);
	}
	if(c=='"')
	{
		c=fgetc(fp);
		col++;
		if(c=='\n') 
			{
				lines++;
				col=0;
			}
		while(c!='"'||c!=EOF)
		{
			c=fgetc(fp);
			col++;
			if(c=='\n') 
				{
					lines++;
					col=0;
				}
		}
		if(c==EOF) return NULL;
	}

	c=fgetc(fp);
	col++;
	if(c=='\n') 
		{
			lines++;
			col=0;
		}			
	if(isalpha(c))
	{
		char buf[20];
		int j=0;
		while(isalpha(c))
		{
			buf[j++]=c;
			c=fgetc(fp);
		}
		buf[j]='\0';
		flag = iskeyword(buf);
		if(flag!=-1)
		{
			token tk;
			tk.row = lines;
			tk.col = col;
			strcpy(tk.tokenName,keyword[flag]);
			return tk;

		}
		else
		{
			token tk;
			tk.row = lines;
			tk.col = col;
			strcpy(tk.tokenName,"id");
			return tk;
		}
		if(c=='\n') 
			{
				lines++;
				col
			}
	}



}
