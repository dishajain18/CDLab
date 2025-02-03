%{
#include <stdio.h>
int pos = 0;
int neg = 0;
int posf = 0;
int negf = 0;
%}

%%

"-0" {printf("-0 is wrong\n");}
[+]?[0-9]+ pos++;
[-][1-9]+ neg++;
[+]?[0-9]+[.][0-9]+ posf++;
[-][0-9]+[.][0-9]+ negf++;
. {}
\n {}

%%

//instead of [.] you can do \. also
int main()
{
    printf("Enter input:\n");
    yylex();
    printf("Positive Integers: %d\n",pos);
    printf("Negative Integers: %d\n",neg);
    printf("Positive Float: %d\n",posf);
    printf("Negative Float: %d\n",negf);
}

int yywrap()
{
    return 1;
}