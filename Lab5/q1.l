%{
#include <stdio.h>
int vows = 0;
int cons = 0;
%}

%%

[aeiouAEIOU] vows++;
[A-Za-z] cons++;
(.|\n) {}

%%
//last rule in above section for any other character and /n don't do anything. This is imp or else it will print these characters if not dealt with.
int main()
{   
    printf("Enter a string: ");
    yylex(); //either give file input using < like we used to in OS or type directly in terminal and do ctrl+D when input over
    printf("Vowels: %d\n",vows);
    printf("Consonants: %d\n",cons);
}

int yywrap()
{
    return 1;
}