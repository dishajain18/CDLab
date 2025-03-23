#include <stdio.h>
#include <string.h>

#define MAX_IDENTIFIER_LEN 20

char *keyword[5] = {"main", "int", "char", "if", "else"};
char *relop[6] = {"==", "!=", "<=", ">=", "<", ">"};
char *reloptk[6] = {"EQ", "NE", "LE", "GE", "LT", "GT"};
char spesymbol[10] = {'#', ',', ';', '(', ')', '{', '}', '[', ']', '='};
char ariop[5] = {'+', '-', '*', '/', '%'};

typedef struct {
    int row, col;
    char tokenName[20];
} token;

int isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int isAlnum(char c) {
    return isAlpha(c) || isDigit(c);
}

int isKeyword(char *str) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(keyword[i], str) == 0) {
            return i;
        }
    }
    return -1;
}

void skipWhitespace(FILE *fp, long *pos) {
    char c;
    while ((c = fgetc(fp)) == ' ' || c == '\t') {
        (*pos)++;
    }
    fseek(fp, -1, SEEK_CUR);
    (*pos)--;
}

int readWord(FILE *fp, char *buffer, long *pos) {
    char c;
    int i = 0;

    while ((c = fgetc(fp)) != EOF && isAlpha(c)) {
        buffer[i++] = c;
        (*pos)++;
    }

    buffer[i] = '\0'; // Null-terminate the string

    // Move back one character since the last read wasn't part of the word
    fseek(fp, -1, SEEK_CUR);
    (*pos)--;

    return i;
}

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

int isValidDefine(FILE *fp, long *pos) {
    char c;
    c = fgetc(fp);
    (*pos)++;
    if(c != ' '|| c!= '\t')
	    return 0;
    skipWhitespace(fp, pos);

    c = fgetc(fp);
    (*pos)++;
    if (!(isAlpha(c) || c == '_')) {
        return 0; // Must start with a valid macro name
    }

    // Skip valid macro name
    while (isAlnum(c) || c == '_') {
        c = fgetc(fp);
        (*pos)++;
    }

    c = fgetc(fp);
    (*pos)++;
    if(c != ' '|| c!= '\t')
	    return 0;

    // Skip rest of the line
    while (c != '\n' && c != EOF) {
        c = fgetc(fp);
        (*pos)++;
    }

    return 1; // Valid #define directive
}

int skipDirective(FILE *fp, long *pos) {
    char buffer[MAX_IDENTIFIER_LEN];
    readWord(fp, buffer, pos);

    if (strcmp(buffer, "include") == 0) {
        return isValidInclude(fp, pos);
    } else if (strcmp(buffer, "define") == 0) {
        return isValidDefine(fp, pos);
    }

    return 0; // Not a valid directive
}

token getNextToken(FILE *fp) {
    static int row = 1, col = 0;
    char c;
    token tk;

    while ((c = fgetc(fp)) != EOF) {
        col++;
        if (c == '/')
        {
            char m = fgetc(fp);
            col++;
            if (m == '/')
            {
                // Handle single-line comment
                while ((m = fgetc(fp)) != '\n' && m != EOF)
                {
                    col++;
                }
                if (m == '\n')
                {
                    row++;
                    col = 0;
                }
                continue; // Skip the rest and move to the next character
            }
            else if (m == '*')
            {
                // Handle multi-line comment
                bool closed = false;
                while ((m = fgetc(fp)) != EOF)
                {
                    col++;
                    if (m == '\n')
                    {
                        row++;
                        col = 0;
                    }
                    else if (m == '*')
                    {
                        char next = fgetc(fp);
                        col++;
                        if (next == '/')
                        {
                            closed = true;
                            break;
                        }
                        else
                        {
                            fseek(fp, -1, SEEK_CUR);
                            col--;
                        }
                    }
                }
                if (!closed)
                {
                    // Reached EOF without closing the comment
                    strcpy(tk.tokenName, "EOF");
                    tk.row = -1;
                    tk.col = -1;
                    return tk;
                }
                continue; // Skip the rest and move to the next character
            }
            else
            {
                // Not a comment, rewind to process '/' as a normal character
                fseek(fp, -1, SEEK_CUR);
                col--;
            }
        }
        if(c=='"')
        {
            c = fgetc(fp);
            while(c!='"')
            {
                if(c==EOF)
                break;
                c = fgetc(fp);
            }
            c = fgetc(fp);
        }

        if (c == '\n') {
            row++;
            col = 0;
            continue;
        }

        if (c == ' ' || c == '\t') {
            continue;
        }

        if (c == '#') {
            long Pos = ftell(fp);
            long prev = Pos;

            if (skipDirective(fp, &Pos)) {
                continue; // Skip valid directive
            } else {
                fseek(fp, prev, SEEK_SET); // Rewind for invalid directive
            }
        }

        // Check for special symbols
        for (int i = 0; i < 10; i++) {
            if (c == spesymbol[i]) {
                tk.tokenName[0] = c;
                tk.tokenName[1] = '\0';
                tk.row = row;
                tk.col = col;               
                return tk;
            }
        }

        // Check for arithmetic operators
        for (int i = 0; i < 5; i++) {
            if (c == ariop[i]) {
                tk.tokenName[0] = c;
                tk.tokenName[1] = '\0';
                tk.row = row;
                tk.col = col;
                return tk;
            }
        }
        // Handle relational operators
        if (c == '=' || c == '<' || c == '>' || c == '!') {
            char next = fgetc(fp);
            col++;
            char buffer[3] = {c, '\0', '\0'};
            if (next == '=') {
                buffer[1] = next; // Create relational operator token (==, <=, >=, !=)
            } else {
                fseek(fp, -1, SEEK_CUR); // Rewind if next character is not '='
                col--;
            }

            for (int i = 0; i < 6; i++) {
                if (strcmp(buffer, relop[i]) == 0) {
                    strcpy(tk.tokenName, reloptk[i]);
                    tk.row = row;
                    tk.col = col - strlen(buffer) + 1;
                    return tk;
                }
            }
        }

        // Check for keywords or identifiers
        if (isAlpha(c)) {
            char buffer[MAX_IDENTIFIER_LEN];
            int i = 0;
            while (isAlnum(c) || c == '_') {
                buffer[i++] = c;
                c = fgetc(fp);
                col++;
            }
            printf("\n");
            buffer[i] = '\0';
            fseek(fp, -1, SEEK_CUR);
            col--;

            if (isKeyword(buffer) != -1) {
                strcpy(tk.tokenName, buffer);
            } else {
                strcpy(tk.tokenName, "id");
            }

            tk.row = row;
            tk.col = col - strlen(buffer) + 1;
            return tk;
        }

        // Check for numeric literals
        if (isDigit(c)) {
            char buffer[MAX_IDENTIFIER_LEN];
            int i = 0;
            while (isDigit(c)) {
                buffer[i++] = c;
                c = fgetc(fp);
                col++;
            }
            buffer[i] = '\0';
            fseek(fp, -1, SEEK_CUR);
            col--;

            strcpy(tk.tokenName, "num");
            tk.row = row;
            tk.col = col - strlen(buffer) + 1;
            return tk;
        }
    }

    tk.row = -1;
    tk.col = -1;
    strcpy(tk.tokenName, "EOF");
    return tk;
}
