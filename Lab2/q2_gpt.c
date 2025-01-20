//doesnt work for define
#include <stdio.h>

int is_valid_include(FILE *fptr1) {
    char ch;

    char include[] = "include";
    for (int i = 0; i < 7; i++) {
        ch = fgetc(fptr1);
        if (ch != include[i]) {
            return 0;
        }
    }

    while ((ch = fgetc(fptr1)) == ' ' || ch == '\t');

    if (ch == '<' || ch == '"') {
        char end_char = (ch == '<') ? '>' : '"';
        // Read until the matching end character
        while ((ch = fgetc(fptr1)) != end_char) {
            if (ch == EOF) return 0; // Improper include syntax
        }
        return 1;
    }

    return 0;
}

int is_valid_define(FILE *fptr1) {
    char ch;

    char define[] = "define";
    for (int i = 0; i < 6; i++) {
        ch = fgetc(fptr1);
        if (ch != define[i]) {
            return 0;
        }
    }

    while ((ch = fgetc(fptr1)) == ' ' || ch == '\t');

    // Check if the first character of the macro name is valid
    if (ch != EOF && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
        // The macro name is valid, now check if there's a value or expression after it

        // Skip over the macro name
        while ((ch = fgetc(fptr1)) != EOF && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ));

        // Skip spaces or tabs after the macro name
        while ((ch = fgetc(fptr1)) == ' ' || ch == '\t');

        // If the macro has no value (i.e., end of line), it's a valid define without a value
        if (ch == '\n' || ch == EOF) {
            return 1;
        }
        // Now we expect a valid expression or value after the macro name
        while (ch != EOF && (ch >= '0' && ch <= '9')&& ch!='\n') {
            ch = fgetc(fptr1);
        }
        if(ch=='\n'||ch == EOF)
          return 1;
    }

    return 0;  
}

int main() {
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

    char ch;
    while ((ch = fgetc(fptr1)) != EOF) {
        if (ch == '#') {
            // Check for valid #include or #define
            if (is_valid_include(fptr1) || is_valid_define(fptr1)) {
                continue;
            } else {
                fputc('#', fptr2);
                // Go back and write the directive to output
                fseek(fptr1, -1, SEEK_CUR);  
                while ((ch = fgetc(fptr1)) != EOF && ch != '\n') {
                    fputc(ch, fptr2);
                }
                fputc('\n', fptr2); 
                continue;
            }
        }

        fputc(ch, fptr2);
    }

    fclose(fptr1);
    fclose(fptr2);

    printf("Preprocessor directives discarded. Output written to %s.\n",filename);

    return 0;
