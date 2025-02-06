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
void U();
void V();
void W();

void S()
{
    U();
    V();
    W();
}

void U()
{
    if(str[cur]=='(')
    {
        cur++;
        S();
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
        S();
        if(str[cur]=='b')
        {
            cur++;
            return;
        }
        else
            invalid();
    }

    else if(str[cur]=='d')
    {
        cur++;
        return;
    }

    else
        invalid();
}

void V()
{
    if(str[cur]=='a')
    {
        cur++;
        V();
    }

    return; //epsilon
}

void W()
{
    if(str[cur]=='c')
    {
        cur++;
        W();
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