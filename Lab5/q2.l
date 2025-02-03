%{
#include <stdio.h>
int words = 0;
int chars = 0;
int blks = 0;
int lines = 0;
%}

%%

\n {chars++; lines++;}
[^ \t\n]+ {words++; chars+=yyleng;}
[ \t] {blks++; chars++;}

%%

int main()
{
    printf("Enter input:\n");
    yylex();
    printf("Words: %d\n",words);
    printf("Chars: %d\n",chars);
    printf("Blanks: %d\n",blks);
    printf("Lines: %d\n",lines);
}

int yywrap()
{
    return 1;
}