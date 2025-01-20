#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr1, *fptr2;
    char filename[100];
    char cur, prev = 0;

    printf("Enter the input file name: ");
    scanf("%[^\n]c", filename);
    
    fptr1 = fopen(filename, "r");
    if (fptr1 == NULL) {
        perror("Error opening input file");
        return -1;
    }

    printf("Enter the output file name: ");
    scanf(" %[^\n]c", filename);

    fptr2 = fopen(filename, "w+");
    if (fptr2 == NULL) {
        perror("Error opening output file");
        fclose(fptr1);
        return -1;
    }

    while ((cur = fgetc(fptr1)) != EOF) {
        if (cur == ' ' || cur == '\t') {
            if (prev != ' ') {
                fputc(' ', fptr2);
            }
        } else {
            fputc(cur, fptr2);
        }
        prev = cur;
    }

    // Close the files
    fclose(fptr1);
    fclose(fptr2);

    printf("Output written to: %s\n", filename);

    return 0;
}
