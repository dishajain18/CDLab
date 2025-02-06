/* remove left recursion
S → (L) | a
L → SL'
L' → ,SL' | 𝜖
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
void L();
void Ldash();

void S()
{
    if(str[cur]=='(')
    {
        cur++;
        L();
        if(str[cur]==')')
        {
            cur++;
            return;
        }
        else
            invalid();
    }
    else if(str[cur]=='a')
    {
        cur++;
        return;
    }
    else
        invalid();
}

void L()
{
    S();
    Ldash();
}

void Ldash()
{
    if(str[cur]==',')
    {
        cur++;
        S();
        Ldash();
    }

    return; //epsilon

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