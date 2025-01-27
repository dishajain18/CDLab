#include "la.h"

int main() {
    FILE *fp = fopen("read.c", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }
    for(int i=0;i<MAX_SYMBOLS;i++)
        symtable[i]=NULL;

    token tk;
    printf("Row\tCol\tTokenName\t\n");
    while (1) {
        tk = getNextToken(fp);
        if (strcmp(tk.tokenName, "EOF") == 0)
            break;
        printf("%d\t%d\t%s\t\n", tk.row, tk.col, tk.tokenName);
    }

    print_symtable();

    fclose(fp);
    return 0;
}