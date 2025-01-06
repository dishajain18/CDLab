//USE HAST TABLE TO STORE INDEX OF WORD IN A STRING ARRAY


#include <stdio.h>
#include <stdlib.h> // For exit()
#include <string.h>

char verb[8][20] = {
int hasht[8][8]={0}
}
   
int calc_hash(char*str)
{
	int len=strlen(str);
	int hval=0;
	for(int i=0;i<len;i++)
		hval+=str[i];
	hval=hval%8;
	return hval;
}

int search(char* str, int hval)
{
 	for(int i=0;i<8;i++)
	{
		if(strcmp(verb[hval][i],str)==0)
			return 1;
	}
	return 0;
}

void insert(char* str)
{
	int hval=calc_hash(str)
	if(search(str,hval))
		return;
	
	for(int i=0;i<8;i++)
	{
		if(strcmp(verb[hval][i],"")==0)
		{
			strcpy(verb[hval][i],str);
			break;
		}
	}
}

int isalpha(char c)
{
	if((c>=65 && c<=90) || (c>=97 && c<=122))
		return 1;
	return 0;
}


int main()
{
	verb
	FILE *fptr1, *fptr2;
	char filename[100], c;
	int size,pos;
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	c=fgetc(fptr1);
	char buf[15];
	while(c!=EOF)
	{
		int i=0;
		while(isalpha(c))
		{
			buf[i]=c;
			i++;
			c=fgetc(fptr1);
		}
		buf[i]='\0';
		insert(buf);

	}

