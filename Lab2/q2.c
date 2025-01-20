//doesnt work

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fptr1,*fptr2;
	char filename[100];
	char c;
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	printf("Enter the filename to open for writing: \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "w+");
	c=fgetc(fptr1);
	int notdir=0; //tells us if the string being read is a preprocessor directive or not
	while(c!=EOF)
	{
		int flag=0;
		if(c=='#')
		{
			char store[50];
			char buf1[]="include";
			char buf2[]="define";
			int i=0;
			c=fgetc(fptr1);
			printf("1%c\n",c);
			store[i]=c;
			if(c=='i') //check for include
			{
				while(c==buf1[i]&&buf1[i+1]!='\0')
				{
					c=fgetc(fptr1);
					printf("2%c\n",c);
					i++;
					store[i]=c;
				}
				if(i==strlen(buf1)-1)
				{
					c=fgetc(fptr1);
					printf("3%c\n",c);
					i++;
					store[i]=c;
					while(c==' ')
					{
						c=fgetc(fptr1);
						printf("3%c\n",c);
						i++;
						store[i]=c;
					}
					char brac=c;
					if(c=='"'||c=='<')
					{
						while(c!='\n')
						{
							printf("notdir:%d\n",notdir);
							c=fgetc(fptr1);
							printf("5%c\n",c);
							i++;
							store[i]=c;
							if((c=='>'&&brac=='<')||(c=='"' && brac=='"')) //check if it matches > or "
								{
									c=fgetc(fptr1); //so that > or " doesnt get written
									printf("breaking \n");
									flag=1;
									break;
								}
							else notdir=1;
						}

						if(c=='\n'&&flag==0)
						{
							printf("it is flagged\n");
							notdir=1;
						}
					}
					else notdir=1;
				}
				else notdir=1;
			}
			
			else if(c=='d') //check for define
			{
				while(c==buf2[i]&&buf2[i]!='\0')
				{
					c=fgetc(fptr1);
					i++;
					store[i]=c;
				}

				if(i==strlen(buf2))
				{
					c=fgetc(fptr1);
					i++;
					store[i]=c;
					if(c==' ')
					{
						c=fgetc(fptr1);
						i++;
						store[i]=c;
						while(c!='\n')
						{
							c=fgetc(fptr1);
							i++;
							store[i]=c;
							if(c==' ')
							{
								c=fgetc(fptr1);
								i++;
								store[i]=c;
								if(c!='\n') break;
							}
						}
						if(c=='\n')
							notdir=1;

					}
					else notdir=1;
				}
				else notdir=1;
			}
			
			else notdir=1;

			if(notdir==1)
			{
				fputc('#',fptr2);
				for(int j=0;j<=i;j++)
					fputc(store[j],fptr2);
			}
		}
		else
			{
				fputc(c,fptr2);
				c=fgetc(fptr1);
			}
	}
}
