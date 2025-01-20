#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100
#define NUM_KEYWORDS 10

void toUpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        // Convert lowercase to uppercase manually
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
}

int isKeyword(const char* word, char* keywords[], int num_keywords) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char c;
    char buffer[MAX_BUFFER_SIZE];
    int bufferIndex = 0;
    char *keywords[] = {"include", "define", "if", "else", "while", "for", "return","int","char","void"};

    FILE *fptr1, *fptr2;
    char filename[100];
    
    // Get input file name
    printf("Enter the input file name: ");
    scanf("%[^\n]c", filename);

    // Open the input file for reading
    fptr1 = fopen(filename, "r");
    if (fptr1 == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }
    printf("Enter the output file name: ");
    scanf(" %[^\n]c", filename);

    // Open the output file for writing
    fptr2 = fopen(filename, "w+");
    if (fptr2 == NULL) {
        printf("Error opening file for writing.\n");
        fclose(fptr1);
        return 1;
    }

    while ((c = getc(fptr1)) != EOF) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            buffer[bufferIndex++] = c;

            // Make sure the buffer doesn't overflow
            if (bufferIndex >= MAX_BUFFER_SIZE) {
                bufferIndex = MAX_BUFFER_SIZE - 1;
            }
        } 
        else {
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                if (isKeyword(buffer, keywords, NUM_KEYWORDS)) {
                    toUpperCase(buffer);
                }
                for (int i = 0; buffer[i] != '\0'; i++) {
                    putc(buffer[i], fptr2);
                }
                bufferIndex = 0;
            }
            putc(c, fptr2);
        }
    }

    // If there's any word left in the buffer ie file ends with word
    if (bufferIndex > 0) {
        buffer[bufferIndex] = '\0';
        if (isKeyword(buffer, keywords, NUM_KEYWORDS)) {
            toUpperCase(buffer);
        }
        for (int i = 0; buffer[i] != '\0'; i++) {
            putc(buffer[i], fptr2);
        }
    }

    fclose(fptr1);
    fclose(fptr2);
    printf("Keywords converted to uppercase and written to %s\n",filename);
}
