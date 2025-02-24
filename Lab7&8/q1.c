
/* AFTER LEFT FACTORING IDENTIFIER_LIST
Program -> main(){ declarations statement-list } 
Declarations -> data-type identifier-list; declarations | E
data-type -> int | char
identifier-list -> id identifier-list1
identifier-list1 -> E | , identifier-list | [number]identifier-list2
identifier-list2 -> , identifier-list | E
statement_list -> statement statement_list | E
statement -> assign-stat; | decision_stat
assign_stat -> id = expn
expn -> simple-expn eprime 
eprime -> relop simple-expn | E 
simple-exp -> term seprime 
seprime -> addop term seprime | E
term -> factor tprime
tprime -> mulop factor tprime | E
factor -> id | num
decision-stat -> if (expn) {statement_list} dprime 
dprime -> else {statement_list) | E
relop -> ==|!=|<=|>=|>|< 
addop -> +|- 
mulop -> *|/|%
*/

#include "la.h"
#include <stdio.h>
#include <stdlib.h>

FILE * fp;


void invalid()
{
    printf("\n-----------------ERROR!----------------\n");
    exit(0);
}
void valid()
{
    printf("\n----------------SUCCESS!---------------\n");
    exit(0);
}

void mulop(token * tk)
{
    if(strcmp(tk->tokenName,"*")==0 || strcmp(tk->tokenName,"/")==0 || strcmp(tk->tokenName,"%%")==0)
    {
        return;
    }

    else
        invalid();
}

void addop(token * tk)
{
    if(strcmp(tk->tokenName,"+")==0 || strcmp(tk->tokenName,"-")==0)
    {
        return;
    }

    else
        invalid();
}

void relop(token * tk)
{
    if(strcmp(tk->tokenName,"==")==0 || strcmp(tk->tokenName,"!=")==0 || strcmp(tk->tokenName,"<=")==0 || strcmp(tk->tokenName,">=")==0 || strcmp(tk->tokenName,">")==0 || strcmp(tk->tokenName,"<")==0)
    {
        return;
    }

    else
        invalid();
}

void dprime(token * tk)
{
    if(strcmp(tk->tokenName,"}")==0)
        return;

    else if(strcmp(tk->tokenName,"else")==0)
    {
        if(strcmp(tk->tokenName,"{")==0)
        {
            *tk = getNextToken(fp);
            statement_list(tk);
            if(strcmp(tk->tokenName,"}")==0)
                return;
            else
                invalid();
        }
        else
            invalid();
    }

    else
        invalid();
}

void decision_stat(token * tk)
{
    if(strcmp(tk->tokenName,"if")==0)
    {
        if(strcmp(tk->tokenName,"(")==0)
        {
            *tk = getNextToken(fp);
            expn(tk);
            *tk = getNextToken(fp);
            if(strcmp(tk->tokenName,")")==0)
            {
                if(strcmp(tk->tokenName,"{")==0)
                {
                    *tk = getNextToken(fp);
                    statement_list(tk);
                    if(strcmp(tk->tokenName,"}")==0)
                    {
                        *tk = getNextToken(fp);
                        dprime(tk);
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
        else
            invalid();
    }
    else
        invalid();
}

void factor(token * tk)
{
    if(strcmp(tk->tokenName,"id")==0 || strcmp(tk->tokenName,"num")==0)
        return;

    else
        invalid();
}

void tprime(token * tk)
{
    if(strcmp(tk->tokenName,"+")==0 || strcmp(tk->tokenName,"-")==0 || strcmp(tk->tokenName,")")==0 || strcmp(tk->tokenName,";")==0)
        return;

    mulop(tk);
    *tk = getNextToken(fp);
    factor(tk);
    *tk = getNextToken(fp);
    tprime(tk);
    return;

}

void Program(token * tk)
{
    if(strcmp(tk->tokenName,"main")==0)
    {
        *tk = getNextToken(fp);
        if(strcmp(tk->tokenName,"(")==0)
        {
            *tk = getNextToken(fp);
            if(strcmp(tk->tokenName,")")==0)
            {
                *tk = getNextToken(fp);
                if(strcmp(tk->tokenName,"{")==0)
                {
                    *tk = getNextToken(fp);
                    declarations(tk);
                    *tk = getNextToken(fp);
                    statement_list(tk);
                    *tk = getNextToken(fp);
                    if(strcmp(tk->tokenName,"}")==0)
                        valid();
                    else
                        invalid();
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

    else
        invalid();
}

void declarations(token * tk)
{
    if(strcmp(tk->tokenName,"}")==0 || strcmp(tk->tokenName,"id")==0 || strcmp(tk->tokenName,"if")==0)
        return;

    data_type(tk);
   *tk = getNextToken(fp);
    identifier_list(tk);
    *tk = getNextToken(fp);
    if(strcmp(tk->tokenName,";")==0)
    {
        *tk = getNextToken(fp);
        declarations(tk);
        return;
    }
    else
        invalid();
}

void data_type(token * tk)
{
    if(strcmp(tk->tokenName,"int")==0 || strcmp(tk->tokenName,"char")==0)
        return;

    else
        invalid();
}

void id_list(token * tk)
{
    if(strcmp(tk->tokenName,"id")==0)
    {
        *tk = getNextToken(fp);
        id_list1(tk);
    }
    else
        invalid();
}

void id_list1(token * tk)
{
    if(strcmp(tk->tokenName,";")==0)
        return;

    else if(strcmp(tk->tokenName,",")==0)
    {
        *tk = getNextToken(fp);
        id_list(tk);
        return;
    }

    else if(strcmp(tk->tokenName,"[")==0)
    {
        *tk = getNextToken(fp);
        if(strcmp(tk->tokenName,"num")==0)
        {
            *tk = getNextToken(fp);
            if(strcmp(tk->tokenName,"]")==0)
            {
                *tk = getNextToken(fp);
                id_list2(tk);
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

void id_list2(token * tk)
{
    if(strcmp(tk->tokenName,";")==0)
        return;

    else if(strcmp(tk->tokenName,",")==0)
    {
        *tk = getNextToken(fp);
        id_list(tk);
        return;
    }

    else
        invalid();
}