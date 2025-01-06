//NOTE: file ptr will never cross 0 or end offset. i.e. if end is 650 it will never be 651 even after  using fgetc(). and it will never be -1 even if you put offset=-1 in fseek.

#include <stdio.h>
#include <stdlib.h> // For exit()
int main()
{
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
	printf("Enter the filename to open for writing: \n");
	scanf("%s", filename);
	fptr2 = fopen(filename, "w+"); //w+ means read&write and erase the file or create new if doesn't exist
	fseek(fptr1,0,SEEK_END);
	size=ftell(fptr1);
	printf("File size: %d\n",size);
	c = fgetc(fptr1);
	pos=size-1;
	while(pos>=0)
	{
		fputc(c, fptr2);
		fseek(fptr1,pos,SEEK_SET); //can even do fseek(fptr1,-1,SEEK_CUR);
		pos--;
		c = fgetc(fptr1);
	}
	printf("Contents copied to %s\n", filename);
	fclose(fptr1);
	fclose(fptr2);
}
