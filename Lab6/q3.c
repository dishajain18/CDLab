/* remove left recursion
S → aAcBe 
A → bA'
A' → bA' | 𝜖
B → d
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
void A();
void Adash();
void B();

void S()
{
    if(str[cur]=='a')
    {
        cur++;
        A();
        if(str[cur]=='c')
        {
            cur++;
            B();
            if(str[cur]=='e')
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
    else
        invalid();
}

void A()
{
    if(str[cur]=='b')
    {
        cur++;
        Adash();
    }

    else
        invalid();
}

void Adash()
{
    if(str[cur]=='b')
    {
        cur++;
        Adash();
    }

    return; //epsilon
}

void B()
{
    if(str[cur]=='d')
    {
        cur++;
        return;
    }
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