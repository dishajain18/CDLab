%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

[0-9]+  {
            int decimal = atoi(yytext);  
            printf("Hexadecimal: %X\n", decimal);  
        }

(.|\n)  { }

%%

int main() {
    printf("Enter decimal number: ");
    yylex();  // Call the lexer
    return 0;
}

int yywrap()
{
    return 1;
}
