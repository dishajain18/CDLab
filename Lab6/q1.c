/* remove left recursion
S → a | > | ( T )
T → ST'
T' → ,ST' | 𝜖 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cur = 0;
char str[100];

void invalid()
{
    printf("-----------------ERROR!----------------\n");
    exit(0);
}
void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}

void S();
void T();
void Tdash();

void S()
{
    if(str[cur]=='a' || str[cur]=='>')
    {
        cur++;
        return;
    }

    else if(str[cur]=='(')
    {
        cur++;
        T();
        if(str[cur]==')')
        {
            cur++;
            return;
        }
        else
            invalid();
    }

    else
        invalid();
}

void T()
{
    S();
    Tdash();
}

void Tdash()
{
    if(str[cur]==',')
    {
        cur++;
        S();
        Tdash();
    }

    return; //this because of epsilon no need to compare any char it is accepted

}

int main()
{
    printf("Enter String: ");
    scanf("%s", str);
    S();
    if(str[cur] == '$')
        valid();
    else
        // printf("%c\n", str[curr]);
        invalid();
}