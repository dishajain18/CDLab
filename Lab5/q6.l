%{
#include <stdio.h>
%}

%%
"//".* { fprintf(yyout, "%s", yytext); }  
"/*"([^*]|[*]+[^*/])*[*]+"/"  { fprintf(yyout, "%s", yytext); }  /* I dont understand even "/*"([^*]|[*]+[^/])*[*]+"/" works but gpt says no */
[A-Z]  { fprintf(yyout, "%c", yytext[0]+32); }  
(.|\n) { fprintf(yyout, "%s", yytext); }  

%%
//instead of [*] you can do \* also
int main() {
    printf("Enter input filename: ");
    char filename[20];
    scanf("%s",filename);
    yyin = fopen(filename,"r");
    printf("Enter output filename: ");
    scanf("%s",filename);
    yyout = fopen(filename,"w+");
    yylex();
    fclose(yyin);
    fclose(yyout);
    return 0;
}

int yywrap()
{
    return 1;
}
