#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 100

// Skip whitespace characters
void skipWhitespace(FILE *fp, long *pos) {
    char c;
    while ((c = fgetc(fp)) == ' ' || c == '\t') {
        (*pos)++;
    }
    fseek(fp, -1, SEEK_CUR);
    (*pos)--;
}

// Read a word after #
int readWord(FILE *fp, char *buffer, long *pos) {
    char c;
    int i = 0;

    while ((c = fgetc(fp)) != EOF && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
        buffer[i++] = c;
        (*pos)++;
    }

    buffer[i] = '\0'; // Null-terminate the string

    // Move back one character since the last read wasn't part of the word
    fseek(fp, -1, SEEK_CUR);
    (*pos)--;

    return i;
}

// Check and skip a valid #include directive
int isValidInclude(FILE *fp, long *pos) {
    char c;
    skipWhitespace(fp, pos);

    c = fgetc(fp);
    (*pos)++;
    if (c == '<' || c == '"') {
        char endChar = (c == '<') ? '>' : '"';
        while ((c = fgetc(fp)) != EOF) {
            (*pos)++;
            if (c == endChar) {
                return 1; // Valid #include directive
            }
            if (c == '\n') {
                break; // Invalid if newline before closing
            }
        }
    }
    return 0; // Invalid #include directive
}

// Check and skip a valid #define directive
int isValidDefine(FILE *fp, long *pos) {
    char c;
    skipWhitespace(fp, pos);

    c = fgetc(fp);
    (*pos)++;
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')) {
        return 0; // Must start with a valid macro name
    }

    // Skip valid macro name
    while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
        c = fgetc(fp);
        (*pos)++;
    }

    // Skip rest of the line
    while (c != '\n' && c != EOF) {
        c = fgetc(fp);
        (*pos)++;
    }

    return 1; // Valid #define directive
}

// Skip valid preprocessor directive
int skipDirective(FILE *fp, long *pos) {
    char buffer[MAX_BUFFER];
    readWord(fp, buffer, pos);

    if (strcmp(buffer, "include") == 0) {
        return isValidInclude(fp, pos);
    } else if (strcmp(buffer, "define") == 0) {
        return isValidDefine(fp, pos);
    }

    return 0; // Not a valid directive
}

// Process the file to remove valid preprocessor directives
void processFile(const char *inputFile, const char *outputFile) {
    FILE *inFile = fopen(inputFile, "r");
    FILE *outFile = fopen(outputFile, "w");

    if (!inFile || !outFile) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char c;
    long pos = 0;

    while ((c = fgetc(inFile)) != EOF) {
        pos++;

        if (c == '#') {
            long prevPos = ftell(inFile);
            if (skipDirective(inFile, &pos)) {
                continue; // Skip valid directive
            } else {
                fseek(inFile, prevPos, SEEK_SET); // Rewind for invalid directive
                pos = prevPos - 1;                // Adjust position tracking
            }
        }

        fputc(c, outFile); // Write non-directive content and invalid directives
    }

    fclose(inFile);
    fclose(outFile);
}

int main() {
    const char *inputFile = "input.c";
    const char *outputFile = "output.c";

    printf("Processing file: %s\n", inputFile);
    processFile(inputFile, outputFile);
    printf("Processed output written to: %s\n", outputFile);

    return 0;
}
