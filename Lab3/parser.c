#include <stdio.h>
#include "la.h"

int main() {
    FILE *fp = fopen("read.c", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    token tk;
    printf("Row\tCol\tTokenName\n");
    while (1) {
        tk = getNextToken(fp);
        if (strcmp(tk.tokenName, "EOF") == 0)
            break;
        printf("%d\t%d\t%s\n", tk.row, tk.col, tk.tokenName);
    }
    fclose(fp);
    return 0;
}
