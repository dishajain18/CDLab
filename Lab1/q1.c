#include <stdio.h>
#include <stdlib.h> // For exit()
int main()
{
	FILE* fptr;
	char filename[100];
	char c;
	int countl=0;
	int countc=0;
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	c = fgetc(fptr);
	while(c!=EOF)
	{
		countc++;
		if(c=='\n')
			countl++;
		c = fgetc(fptr);
	}
	countl++;
	printf("Characters: %d\n",countc);
	printf("Lines: %d\n",countl);
	fclose(fptr);
	return 0;
}