%{

#include <stdio.h>
int scan=0;
int print=0;

%}

%%

"scanf" {scan++; fprintf(yyout,"READ");}
"printf" {print++; fprintf(yyout,"WRITE");}
(.|\n) {fprintf(yyout,"%s",yytext);}


%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter input filename: ");
    char filename[20];
    scanf("%s",filename);
    yyin = fopen(filename,"r");
    printf("Enter output filename: ");
    scanf("%s",filename);
    yyout = fopen(filename,"w+");
    yylex();
    printf("\nScanf: %d\n",scan);
    printf("Printf: %d\n",print);
}