/ This is a errornous single line comment
// valid single comment
/* *****This is a
******Multiline Comment
**** */
#include <stdio.h>
#define a 9
void main()
{
FILE *fopen(), *fp;int c ;
fp = fopen( “prog.c”, “r” ); //Comment
c = getc( fp ) ;
while ( c
!=
EOF )
{
putchar( c );
c = getc ( fp );
}
/*multiline
comment */
fclose(
fp );
}