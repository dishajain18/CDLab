#include <stdio.h>
#include <stdlib.h> // For exit()
int main()
{
	FILE *fptr1, *fptr2, *fptr3;
	char filename[100], c;
	printf("Enter the first filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}	
	printf("Enter the second filename to open for reading: \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "r");
	if (fptr2 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	printf("Enter the filename to open for writing: \n");
	scanf("%s", filename);
	fptr3 = fopen(filename, "w+");
	int done1=0,done2=0;
	while(!done1||!done2)
	{
		c = fgetc(fptr1);
		while(!done1 && c!=EOF)
		{
			fputc(c,fptr3);
			if(c=='\n'){
				break;
			}
			c = fgetc(fptr1);
		}
		if(c==EOF)
			done1=1;
		c = fgetc(fptr2);
		while(!done2 && c!=EOF)
		{
			fputc(c,fptr3);
			if(c=='\n'){
				break;
			}
			c = fgetc(fptr2);
		}
		if(c==EOF)
			done2=1;
	}
	printf("Contents copied to %s\n", filename);
	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);
	return 0;
}